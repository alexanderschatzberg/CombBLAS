#include "../CombBLAS.h"
#include <mpi.h>
#include <sys/time.h>
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

#define NO_INIT 0
#define GREEDY 1
#define KARP_SIPSER 2
#define DMD 3
using namespace std;
MTRand GlobalMT(123); // for reproducable result


struct VertexType1
{
public:
    VertexType1(int64_t p=-1, int64_t com=0){parent=p; comp = com; };
    
    friend bool operator<(const VertexType1 & vtx1, const VertexType1 & vtx2 )
    {
        return vtx1.comp<vtx2.comp;
    };
    friend bool operator==(const VertexType1 & vtx1, const VertexType1 & vtx2 ){return vtx1.comp==vtx2.comp;};
    friend ostream& operator<<(ostream& os, const VertexType1 & vertex ){os << "(" << vertex.parent << "," << vertex.comp << ")"; return os;};
    int64_t parent;
    int64_t comp; // can be index, probability or degree
};


template <typename T1, typename T2>
struct SelectPlusSR
{
    static T2 id(){ return 1; };
    static bool returnedSAID() { return false; }
    static MPI_Op mpi_op() { return MPI_SUM; };
    
    static T2 add(const T2 & arg1, const T2 & arg2)
    {
        return std::plus<T2>()(arg1, arg2);
    }
    
    static T2 multiply(const T1 & arg1, const T2 & arg2)
    {
        return static_cast<T2> (1); // note: it is not called on a Boolean matrix
    }
    
    static void axpy(const T1 a, const T2 & x, T2 & y)
    {
        y = add(y, multiply(a, x));
    }
};







template <typename T1, typename T2>
struct Select2ndMinSR
{
    static T2 id(){ return T2(); };
    static bool returnedSAID() { return false; }
    static MPI_Op mpi_op() { return MPI_MIN; };
    
    static T2 add(const T2 & arg1, const T2 & arg2)
    {
        return std::min(arg1, arg2);
    }
    
    static T2 multiply(const T1 & arg1, const T2 & arg2)
    {
        return arg2;
    }
    
    static void axpy(const T1 a, const T2 & x, T2 & y)
    {
        y = add(y, multiply(a, x));
    }
};







typedef SpParMat < int64_t, bool, SpDCCols<int64_t,bool> > PSpMat_Bool;
typedef SpParMat < int64_t, int64_t, SpDCCols<int64_t,int64_t> > PSpMat_Int64;
typedef SpParMat < int64_t, bool, SpDCCols<int32_t,bool> > PSpMat_s32p64;

void MaximalMatching(PSpMat_s32p64 & A, PSpMat_s32p64 & AT, FullyDistVec<int64_t, int64_t>& mateRow2Col,
            FullyDistVec<int64_t, int64_t>& mateCol2Row, FullyDistVec<int64_t, int64_t> degCol, int type, bool rand=true)
{
    
    int nprocs, myrank;
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    
    
    
    
    //unmatched row and column vertices
    FullyDistSpVec<int64_t, int64_t> unmatchedRow(mateRow2Col, [](int64_t mate){return mate==-1;});
    FullyDistSpVec<int64_t, int64_t> degColSG(A.getcommgrid(), A.getncol());
    //FullyDistVec<int64_t, int64_t> degCol(A.getcommgrid());
    //A.Reduce(degCol, Column, plus<int64_t>(), static_cast<int64_t>(0)); // Reduce is not multithreaded
    
    
    FullyDistSpVec<int64_t, VertexType1> unmatchedCol(A.getcommgrid(), A.getncol());
    unmatchedCol  = EWiseApply<VertexType1>(unmatchedCol, mateCol2Row, [](VertexType1 vtx, int64_t mate){return VertexType1();},
                                            [](VertexType1 vtx, int64_t mate){return mate==-1;}, true, VertexType1());
    unmatchedCol.Select(degCol, [](int64_t deg){return deg>0;});
    unmatchedCol.ApplyInd([](VertexType1 vtx, int64_t idx){return VertexType1(idx,idx);}); //  parent equals to index
    
        
    if(type==DMD)
        unmatchedCol.SelectApply(degCol, [](int64_t deg){return deg>0;},
                             [](VertexType1 vtx, int64_t deg){return VertexType1(vtx.parent,deg);});
    
    //fringe vector (sparse)
    FullyDistSpVec<int64_t, VertexType1> fringeRow(A.getcommgrid(), A.getnrow());
    
   
    
    int64_t curUnmatchedCol = unmatchedCol.getnnz();
    int64_t curUnmatchedRow = unmatchedRow.getnnz();
    int64_t newlyMatched = 1; // ensure the first pass of the while loop
    int iteration = 0;
    double tStart = MPI_Wtime();
    vector<vector<double> > timing;
    
    if(myrank == 0)
    {
        cout << "=======================================================\n";
        cout << "@@@@@@ Number of processes: " << nprocs << endl;
        cout << "=======================================================\n";
        cout  << "It   |  UMRow   |  UMCol   |  newlyMatched   |  Time "<< endl;
        cout << "=======================================================\n";
    }
    MPI_Barrier(MPI_COMM_WORLD);

    
    while(curUnmatchedCol !=0 && curUnmatchedRow!=0 && newlyMatched != 0 )
    {
        
        // ======================== step1: One step of BFS =========================
        vector<double> times;
        double t1 = MPI_Wtime();
        if(type==GREEDY)
        {
            if(rand)
                unmatchedCol.Apply([](VertexType1 vtx){return VertexType1(vtx.parent, static_cast<int64_t>((GlobalMT.rand() * 9999999)+1));});
            SpMV<Select2ndMinSR<bool, VertexType1>>(A, unmatchedCol, fringeRow, false);
        }
        else if(type==DMD)
        {
            SpMV<Select2ndMinSR<bool, VertexType1>>(A, unmatchedCol, fringeRow, false);
        }
        else //(type==KARP_SIPSER)
        {
            FullyDistSpVec<int64_t, VertexType1> deg1Col = unmatchedCol;
            deg1Col.Select(degCol, [](int64_t deg){return deg==1;});
            
            if(deg1Col.getnnz()>9)
                SpMV<Select2ndMinSR<bool, VertexType1>>(A, deg1Col, fringeRow, false);
            else
            {
                if(rand)
                    unmatchedCol.Apply([](VertexType1 vtx){return VertexType1(vtx.parent, static_cast<int64_t>((GlobalMT.rand() * 9999999)+1));});
                SpMV<Select2ndMinSR<bool, VertexType1>>(A, unmatchedCol, fringeRow, false);
            }
            
        }
        // Remove matched row vertices
        fringeRow.Select(mateRow2Col, [](int64_t mate){return mate==-1;});
        if(myrank == 0){times.push_back(MPI_Wtime()-t1); t1 = MPI_Wtime();}
        // ===========================================================================
        
        
        // ======================== step2: Update matching  =========================
        FullyDistSpVec<int64_t, int64_t> fringeRow2(A.getcommgrid(), A.getnrow());
        
        fringeRow2  = EWiseApply<int64_t>(fringeRow, mateRow2Col, [](VertexType1 vtx, int64_t mate){return vtx.parent;},
                                          [](VertexType1 vtx, int64_t mate){return true;}, false, VertexType1());
        
        FullyDistSpVec<int64_t, int64_t> newMatchedCols = fringeRow2.Invert(A.getncol());
        FullyDistSpVec<int64_t, int64_t> newMatchedRows = newMatchedCols.Invert(A.getnrow());
        mateCol2Row.Set(newMatchedCols);
        mateRow2Col.Set(newMatchedRows);
        if(myrank == 0){times.push_back(MPI_Wtime()-t1); t1 = MPI_Wtime();}
        // ===========================================================================
        
        
        // =============== step3: Update degree of unmatched columns =================
        unmatchedRow.Select(mateRow2Col, [](int64_t mate){return mate==-1;});
        unmatchedCol.Select(mateCol2Row, [](int64_t mate){return mate==-1;});
        
        if(type!=GREEDY)
        {
            // update degree
            newMatchedRows.Apply([](int64_t val){return 1;}); // needed if the matrix is Boolean since the SR::multiply isn't called
            SpMV< SelectPlusSR<bool, int64_t>>(AT, newMatchedRows, degColSG, false);  // degree of column vertices to matched rows
            // subtract degree of column vertices
            degCol.EWiseApply(degColSG,
                              [](int64_t old_deg, int64_t new_deg, bool a, bool b){return old_deg-new_deg;},
                              [](int64_t old_deg, int64_t new_deg, bool a, bool b){return true;},
                              false, static_cast<int64_t>(0), false);
            unmatchedCol.SelectApply(degCol, [](int64_t deg){return deg>0;},
                                     [](VertexType1 vtx, int64_t deg){return VertexType1(vtx.parent,deg);});
        }
        if(myrank == 0){times.push_back(MPI_Wtime()-t1); t1 = MPI_Wtime();}
        // ===========================================================================
        
        
        ++iteration;
        newlyMatched = newMatchedCols.getnnz();
        if(myrank == 0)
        {
            times.push_back(std::accumulate(times.begin(), times.end(), 0.0));
            timing.push_back(times);
            printf("%3d %10lld %10lld %10lld %18lf\n", iteration , curUnmatchedRow, curUnmatchedCol, newlyMatched, times.back());
        }
        
        curUnmatchedCol = unmatchedCol.getnnz();
        curUnmatchedRow = unmatchedRow.getnnz();
        MPI_Barrier(MPI_COMM_WORLD);
        
    }
    
    
    if(myrank == 0)
    {
        cout << "==========================================================\n";
        cout << "\n================individual timings =======================\n";
        cout  << "     SpMV      Update-Match   Update-UMC    Total "<< endl;
        cout << "==========================================================\n";
        
        vector<double> totalTimes(timing[0].size(),0);
        for(int i=0; i<timing.size(); i++)
        {
            for(int j=0; j<timing[i].size(); j++)
            {
                totalTimes[j] += timing[i][j];
                printf("%12.5lf ", timing[i][j]);
            }
            cout << endl;
        }
        
        cout << "-------------------------------------------------------\n";
        for(int i=0; i<totalTimes.size(); i++)
            printf("%12.5lf ", totalTimes[i]);
        cout << endl;
        
        printf("%lld %lf\n",curUnmatchedRow, totalTimes.back());
    }
}






template <class IT, class NT>
bool isMaximalmatching(PSpMat_Bool & A, FullyDistVec<IT,NT> & mateRow2Col, FullyDistVec<IT,NT> & mateCol2Row)
{
    int myrank;
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    FullyDistSpVec<int64_t, int64_t> fringeRow(A.getcommgrid(), A.getnrow());
    FullyDistSpVec<int64_t, int64_t> fringeCol(A.getcommgrid(), A.getncol());
    FullyDistSpVec<int64_t, int64_t> unmatchedRow(mateRow2Col, [](int64_t mate){return mate==-1;});
    FullyDistSpVec<int64_t, int64_t> unmatchedCol(mateCol2Row, [](int64_t mate){return mate==-1;});
    unmatchedRow.setNumToInd();
    unmatchedCol.setNumToInd();
    
    
    SpMV<Select2ndMinSR<bool, VertexType1>>(A, unmatchedCol, fringeRow, false);
    fringeRow = EWiseMult(fringeRow, mateRow2Col, true, (int64_t) -1);
    if(fringeRow.getnnz() != 0)
    {
        if(myrank == 0)
            cout << "Not maximal matching!!\n";
        return false;
    }
    
    PSpMat_Int64 tA = A;
    tA.Transpose();
    SpMV<Select2ndMinSR<bool, VertexType1>>(tA, unmatchedRow, fringeCol, false);
    fringeCol = EWiseMult(fringeCol, mateCol2Row, true, (int64_t) -1);
    if(fringeCol.getnnz() != 0)
    {
        if(myrank == 0)
            cout << "Not maximal matching**!!\n";
        return false;
    }
    return true;
}


