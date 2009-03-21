/****************************************************************/
/* Sequential and Parallel Sparse Matrix Multiplication Library */
/* version 2.3 --------------------------------------------------/
/* date: 01/18/2009 ---------------------------------------------/
/* author: Aydin Buluc (aydin@cs.ucsb.edu) ----------------------/
/****************************************************************/


#include "SpDCCols.h"
#include "MMmul.h"
#include "Deleter.h"
#include <algorithm>
#include <functional>
#include <vector>
#include <climits>


template <class IT, class NT>
SpDCCols<IT,NT>::SpDCCols():dcsc(NULL), m(0), n(0), nnz(0), localpool(NULL) {}


// Allocate all the space necessary
template <class IT, class NT>
SpDCCols<IT,NT>::SpDCCols(IT size, IT nRow, IT nCol, IT nzc)
:m(nRow), n(nCol), nnz(size), localpool(NULL)
{
	if(size > 0)
		dcsc = new Dcsc<IT,NT>(size,nzc);
	else
		dcsc = NULL; 
}

//! Private constructor, used for indexing only
template <class IT, class NT>
SpDCCols<IT,NT>::SpDCCols (IT size, IT nRow, IT nCol, const vector<IT> & indices, bool isRow)
:m(0), n(0), nnz(0), localpool(NULL)
{
	if(size > 0)
		dcsc = new Dcsc<IT,NT>(size,indices,isRow);
	else
		dcsc = NULL; 
}

//! Construct SparseDColumn from Dcsc
template <class IT, class NT>
SpDCCols<IT,NT>::SpDCCols(IT size, IT nRow, IT nCol, Dcsc<IT,NT> * mydcsc)
:m(nRow), n(nCol), nnz(size), localpool(NULL)
{
	if(size > 0)
		dcsc = mydcsc;
	else
		dcsc = NULL;
}

template <class IT, class NT>
template <typename NNT>
SpDCCols<IT,NNT> SpDCCols<IT,NT>::ConvertNumericType ()
{
	Dcsc<IT,NNT> * convert = new Dcsc<IT,NNT>(dcsc->ConvertNumericType<NNT>());
	return SpDCCols<IT,NNT>(nnz, m, n, convert);
}


// Copy constructor (constructs a new object. i.e. this is NEVER called on an existing object)
// Derived's copy constructor can safely call Base's default constructor as base has no data members 
template <class IT, class NT>
SpDCCols<IT,NT>::SpDCCols(const SpDCCols<IT,NT> & rhs)
: m(rhs.m), n(rhs.n), nnz(rhs.nnz), localpool(rhs.localpool)
{
	CopyDcsc(rhs.dcsc);
}

// No need to call base's assigment operator as it has not data members
template <class IT, class NT>
SpDCCols<IT,NT>::SpDCCols(const MMmul< SpDCCols<IT,NT> > & mmmul)
{
	dcsc = new Dcsc<IT,NT>(*(mmmul.sm1.dcsc));
	*this = OrdOutProdMult(mmmul.sm2);	// this = this->OrdOutProdMult(B)
};

/** 
 * Constructor for converting SpTuples matrix -> SpDCCols
 * /attention AUX array is not generated by default.
 * @param[in] 	rhs if transpose=true, 
 *	\n		then rhs is assumed to be a row sorted SpTuples object 
 *	\n		else rhs is assumed to be a column sorted SpTuples object
 * @param[in, out] mpool default parameter value is a null pointer, which means no special memory pool is used
 *	\n	if the parameter is supplied, then memory for MAS, JC, IR, NUMX are served from the given memory pool
 *	\n	also modifies the memory pool so that the used portions are no longer listed as free
 */
template <class IT, class NT>
SparseDColumn<T>::SparseDColumn(const SparseTriplets<T> & rhs, bool transpose, MemoryPool * mpool)
: m(rhs.m), n(rhs.n), nnz(rhs.nnz), localpool(mpool)
{	
	if(nnz == 0)	// m by n matrix of complete zeros
	{
		dcsc = NULL;	
	}
	else
	{
		if(transpose)
		{
			swap(m,n);
			IT localnzc = 1;
			for(IT i=1; i< rhs.getnnz(); ++i)
			{
				if(rhs.rowindex(i) != rhs.rowindex(i-1))
				{
					++localnzc;
				}
			}

			if(localpool == NULL)	// no special memory pool used
			{
				dcsc = new Dcsc<IT,NT>(rhs.getnnz(),localnzc);	
			}
			else
			{
				dcsc = new Dcsc<IT,NT>(rhs.getnnz(), localnzc, localpool);
			}		

			dcsc->jc[zero]  = rhs.rowindex(zero); 
			dcsc->mas[zero] = zero;

			for(IT i=0; i<rhs.getnnz(); ++i)
			{
				dcsc->ir[i]  = rhs.colindex(i);		// copy rhs.jc to ir since this transpose=true
				dcsc->numx[i] = rhs.numvalue(i);
			}

			IT jspos  = 1;		
			for(IT i=1; i<rhs.getnnz(); ++i)
			{
				if(rhs.rowindex(i) != dcsc->jc[jspos-1])
				{
					dcsc->jc[jspos] = rhs.rowindex(i);	// copy rhs.ir to jc since this transpose=true
					dcsc->mas[jspos++] = i;
				}
			}		
			dcsc->mas[jspos] = rhs.getnnz();
		}
		else
		{
			IT localnzc = 1;
			for(IT i=1; i<rhs.getnnz(); ++i)
			{
				if(rhs.colindex(i) != rhs.colindex(i-1))
				{
					++localnzc;
				}
			}
			if(localpool == NULL)	// no special memory pool used
			{
				dcsc = new Dcsc<IT,NT>(rhs.getnnz(),localnzc);	
			}
			else
			{
				dcsc = new Dcsc<IT,NT>(rhs.getnnz(),localnzc, localpool);
			}

			dcsc->jc[zero]  = rhs.colindex(zero); 
			dcsc->mas[zero] = zero;

			for(IT i=0; i<rhs.getnnz(); ++i)
			{
				dcsc->ir[i]  = rhs.rowindex(i);		// copy rhs.ir to ir since this transpose=false
				dcsc->numx[i] = rhs.numvalues(i);
			}

			IT jspos = 1;		
			for(IT i=1; i<rhs.getnnz(); ++i)
			{
				if(rhs.colindex(i) != dcsc->jc[jspos-1])
				{
					dcsc->jc[jspos] = rhs.colindex(i);	// copy rhs.jc to jc since this transpose=true
					dcsc->mas[jspos++] = i;
				}
			}		
			dcsc->mas[jspos] = rhs.getnnz();
		}
	}
}

// The assignment operator operates on an existing object
// The assignment operator is the only operator that is not inherited.
// But there is no need to call base's assigment operator as it has not data members
template <class IT, class NT>
SpDCCols<IT,NT> & SpDCCols<IT,NT>::operator=(const SpDCCols<IT,NT> & rhs)
{
	// this pointer stores the address of the class instance
	// check for self assignment using address comparison
	if(this != &rhs)		
	{
		m = rhs.m; 
		n = rhs.n;
		nnz = rhs.nnz; 
		if(dcsc != NULL && dcsc->nz > 0)
		{
			delete dcsc;
		}
		if(rhs.dcsc != NULL)	
		{
			dcsc = new Dcsc<IT,NT>(*(rhs.dcsc));
		}
	}
	return *this;
}

template<class IU, class NU1, class NU2, class SR>
StackEntry<promote_trait<NU1,NU2>::T_promote, IU> MultiplyReturnStack 
					(const SpDCCols<IU, NU1> & A, 
					 const SpDCCols<IU, NU2> & B, 
					 const SR & sring)
{
		
}

/** 
  * \remarks Assumes the second input has NOT been transposed, this function calls either:
  * \remarks - OrdOutProdMult which transposes the second input itself
  * \remarks - OrdColByCol which doesn't need transposition at all.
  */
template <class IT, class NT>
SparseDColumn<T> & SparseDColumn<T>::operator=(const MMmul< SparseDColumn<T> > & mmmul)
{
	if(mmmul.sm1.n == mmmul.sm2.m)
       	{
		SparseMatrix<T, SparseDColumn<T> >::operator=(mmmul.sm1);
		if(dcsc != NULL && dcsc->nz > 0)
		{
			delete dcsc;
		}

	
		dcsc = new Dcsc<T>(*(mmmul.sm1.dcsc));	// calls Dcsc's copy constructor !

#ifdef ALG1
		*this = OrdOutProdMult(mmmul.sm2);	// this will transpose sm2 first and then multiply
#else
		*this = OrdColByCol(mmmul.sm2);
#endif
		return *this;
	}
	else
	{
		cerr <<"Not multipliable: " << mmmul.sm1.n << "!=" << mmmul.sm2.m << endl;
	}
}

/**
  * \remarks Always uses the hard-coded outer product based multiplication
  * \remarks Assumes the second input has ALREADY been transposed !
  * \todo Those assumptions are dangerous, fix this interface !!!
  * \remarks This allows every block of matrix B to be transposed only once at the beginning
  */
template <class IT, class NT>
SparseDColumn<T> & SparseDColumn<T>::operator+=(const MMmul< SparseDColumn<T> > & mmmul)
{
	if(m == mmmul.sm1.m && n == mmmul.sm2.n)		// since sm2 is already transposed
	{
		if(mmmul.sm1.n == mmmul.sm2.m)
		{	
			if( PlusEq_AnXBt(mmmul.sm1,mmmul.sm2) < 0)
			{
				// Don't check anything, nothing was added !
				// C matrix can still be completely empty (meaning dcsc being null)
			}
			else
			{
				nzmax = dcsc->nz;
			}
		}
		else
		{
			cerr <<"Not multipliable: " << mmmul.sm1.n << "!=" << mmmul.sm2.m << endl;
		}
	}
	else
	{
		cerr<< "Not addable: "<< m << "!=" << mmmul.sm1.m << " or " << n << "!=" << mmmul.sm2.n << endl;		
	}
	return *this;
}

template <class IT, class NT>
void SparseDColumn<T>::Finalize()
{
	dcsc->ConstructAux(n);	
	// if Aux exists, delete it and reconstruct
	// if not, construct it from stratch
} 

/**
  * \attention As the aux array needs to be recontructed after this add-and-assign operation,
  * We delete the aux array (if it exists). 
  * It is automatically reconstructed during splitting, col-indexing or algorithm-2
  */
template <class IT, class NT>
SparseDColumn<T> & SparseDColumn<T>::operator+=(const SparseDColumn<T> & rhs)
{
	// this pointer stores the address of the class instance
	// check for self assignment using address comparison
	if(this != &rhs)		
	{
		if(m == rhs.m && n == rhs.n)
		{
			if(rhs.nzmax == 0)
			{
				return *this;
			}
			else if(nzmax == 0)
			{
				dcsc = new Dcsc<T>(*(rhs.dcsc));
				nzmax = dcsc->nz;
			}
			else
			{
				(*dcsc).DeleteAux();
				(*dcsc) += (*(rhs.dcsc));
				nzmax = dcsc->nz;
			}		
		}
		else
		{
			cout<< "Not addable !"<<endl;		
		}
	}
	else
	{
		cout<< "Missing feauture (A+A): Use multiply with 2 instead !"<<endl;	
	}
	return *this;
}

template <class IT, class NT>
SpDCCols<T>::~SpDCCols()
{
	if(nnz > 0)
	{
		if(dcsc != NULL) delete dcsc;	// call Dcsc's destructor
	}
}


/** O(nz log(nz)) time Transpose function
  * \remarks basically a lexicographical sort
  * \remarks replaces the calling object with its transpose. 
  * \remarks respects the memory pool
  */
template <class IT, class NT>
void SpDCCCols<IT,NT>::Transpose()
{
	SpTuples<IT,NT> Atuples(*this);
	Atuples.SortRowBased();

	// destruction of (*this) is handled by the assignment operator
	*this = SpDCCols<T>(Atuples,true, localpool);
}

/** O(nz log(nz)) time Transpose function
  * \remarks basically a lexicographical sort
  * \remarks const function, doesn't mutate the calling object
  * \remarks respects the memory pool
  */
template <class IT, class NT>
SpDCCCols<IT,NT> SpDCCCols<IT,NT>::TransposeConst() const
{
	SpTuples<IT,NT> Atuples(*this);
	Atuples.SortRowBased();

	return SpDCCols<IT,NT>(Atuples,true, localpool);
}

/** 
  * Splits the matrix into two parts, simply by cutting along the columns
  * Simple algorithm that doesn't intend to split perfectly, but it should do a pretty good job
  * Practically destructs the calling object also (frees most of its memory)
  */
template <class IT, class NT>
void SparseDColumn<T>::Split(SparseDColumn<T> & partA, SparseDColumn<T> & partB) 
{
	IT cut = n/2;
	if(cut == zero)
	{
		cout<< "matrix is too small to be splitted" << endl;
		return;
	}

	Dcsc<IT,NT> *Adcsc, *Bdcsc;
	dcsc->Split(Adcsc, Bdcsc, cut);

	partA = SpDCCols (Adcsc->nz, m, cut, Adcsc);
	partB = SpDCCols (Bdcsc->nz, m, n-cut, Bdcsc);
	
	// handle destruction through assignment operator
	*this = SpDCCols<IT, NT>();		
}

/** 
  * Merges two matrices (cut along the columns) into 1 piece
  * Split method should have been executed on the object beforehand
 **/
template <class IT, class NT>
void SpDCCols<IT,NT>::Merge(SpDCCols<IT,NT> & A, SpDCCols<IT,NT> & B) 
{
	assert(A.m == B.m);

	Dcsc * Cdcsc = new Dcsc<IT,NT>();
	Cdcsc->Merge(A.dcsc, B.dcsc, A.n);
	
	*this = SpDCCols (dcsc->nz, A.m, A.n + B.n, Cdcsc);

	A = SpDCCols<IT, NT>();	
	B = SpDCCols<IT, NT>();	
}


/**
 * \return An indexed SparseDColumn object without using multiplication 
 * \pre ci is sorted and is not completely empty.
 * \remarks it is OK for some indices ci[i] to be empty in the indexed SparseDColumn matrix [i.e. in the end nzc does not need to be equal to n]
 */
template <class IT, class NT>
SparseMatrix<T, SparseDColumn<T> > * SparseDColumn<T>::ColIndex(const vector<ITYPE> & ci)
{
	ITYPE zero = static_cast<ITYPE>(0);
	ITYPE csize = ci.size();

	if(nzmax == 0)	// nothing to index
	{
		return new  SparseDColumn<T>(zero, m, csize, zero);	
	}
	else if(ci.empty())
	{
		return new SparseDColumn<T>(zero, m,zero, zero);
	}

	// Pass 1 for estimation
	ITYPE estsize = zero;
	ITYPE estnzc = zero;
	for(ITYPE i=0, j =0;  i< dcsc->nzc && j < csize ;)
	{
		if((dcsc->jc)[i] < ci[j])
			i++;
		else if ((dcsc->jc)[i] > ci [j] )
			j++;
		else
		{
			estsize +=  (dcsc->mas)[i+1] - (dcsc->mas)[i];
			++estnzc;
			++i;
			++j;
		}
	}
	
	SparseDColumn<T> * colindexed = new  SparseDColumn<T>();	// dcsc = null
	colindexed->m = m;
	colindexed->n = csize;
	colindexed->nzmax = estsize;

	if(estnzc == zero)
	{
		return colindexed;		// no need to run the second pass
	}
	colindexed->dcsc = new Dcsc<T>(estsize, estnzc, csize);
	colindexed->dcsc->mas[0] = 0;
	colindexed->dcsc->colchunks = 0;
	colindexed->dcsc->aux = NULL;

	ITYPE cnzc = 0;
	ITYPE cnz =0;
	for(ITYPE i =0, j =0;  i< dcsc->nzc & j < csize ;)
	{
		if((dcsc->jc)[i] < ci[j])
			i++;
		else if ((dcsc->jc)[i] > ci[j])
			j++;
		else
		{
			colindexed->dcsc->jc[cnzc] = cnzc++;
			colindexed->dcsc->mas[cnzc] = colindexed->dcsc->mas[cnzc-1] + ( (dcsc->mas)[i+1] - (dcsc->mas)[i] );

			for(ITYPE k= (dcsc->mas)[i]; k< (dcsc->mas)[i+1] ; ++k)
			{
				colindexed->dcsc->ir[cnz] =  dcsc->ir[k];
				colindexed->dcsc->numx[cnz++] =  dcsc->numx[k];
			}
			++i;
			++j;
		}
	}
	return colindexed;
}

// \todo Compare performance with ColIndex above
template <class IT, class NT>
SparseDColumn<T> SparseDColumn<T>::SubsRefCol(const vector<ITYPE> & ci) const
{
	ITYPE csize = ci.size();
	SparseDColumn<T> RightMatrix(csize, this->n, csize, ci, false);
	return OrdColByCol(RightMatrix);
}


/** 
 * Indexing using Multiplication 
 */
template <class IT, class NT>
SparseMatrix<T, SparseDColumn<T> > * SparseDColumn<T>::operator() (const vector<ITYPE> & ri, const vector<ITYPE> & ci) const
{
	ITYPE rsize = ri.size();
	ITYPE csize = ci.size();

	if(rsize == 0 && csize == 0)
	{
		// return an m x n matrix of complete zeros
		// since we don't know whether columns or rows are indexed

		ITYPE zero = static_cast<ITYPE>(0);
		return new SparseDColumn(zero, m, n, zero);		
	}
	else if(rsize == 1 && csize == 1)
	{
		cout<<"Please use element-wise indexing for a single element!"<<endl;
		return NULL;
	}
	else if(rsize == 0)
	{
		SparseDColumn<T> RightMatrix(csize, this->n, csize, ci, false);
		return new SparseDColumn(OrdOutProdMult(RightMatrix));
	}
	else if(csize == 0)
	{
		SparseDColumn<T> LeftMatrix(rsize, rsize, this->m, ri, true);
		return new SparseDColumn(LeftMatrix.OrdOutProdMult(*this));
	}
	else
	{
		SparseDColumn<T> LeftMatrix(rsize, rsize, this->m, ri, true);
		SparseDColumn<T> RightMatrix(csize, this->n, csize, ci, false);
		return new SparseDColumn(((LeftMatrix.OrdOutProdMult(*this)).OrdOutProdMult(RightMatrix)));
	}
}


/** 
  * Friend of both SparseColumn<T> and SparseColumn<bool>
  * Executes [C = A*B] 
  * Partial template specialization on the second Matrix 
  */
template <class IT, class NT>
template <typename T2>
SparseDColumn<T> SparseDColumn<T>::Multiply (const SparseDColumn<T> & A,const SparseDColumn<T2> & B, bool isAT, bool isBT )
{
	ITYPE A_m, A_n, B_m, B_n;
 
	if(isAT)
	{
		A_m = A.n;
		A_n = A.m;
	}
	else
	{
		A_m = A.m;
		A_n = A.n;
	}
	if(isBT)
	{
		B_m = B.n;
		B_n = B.m;
	}
	else
	{
		B_m = B.m;
		B_n = B.n;
	}
		
	if(A_n == B_m)
        {
		SparseMatrix<T, SparseDColumn<T> >::operator=(A);
		if(dcsc != NULL && dcsc->nz > 0)
		{
			delete dcsc;
		}

	
		dcsc = new Dcsc<T>(*(A.dcsc));	// calls Dcsc's copy constructor !

		ITYPE cnz;
		Dcsc<T> * mydcsc = NULL;

		ITYPE zero = static_cast<ITYPE>(0);
		if(A.nzmax == 0 || B.nzmax == 0)
		{
			return SparseDColumn(zero, A.m, B.n, zero);		// result is an m by n matrix of complete zeros
		}
		else
		{
			if(!isBT)
			{
				SparseDColumn<T2> Btrans = B.TransposeConst();
				//! /todo there seems to be a bug here about m and n
				Btrans.TransposeInPlace();	// calls SparseMatrix's Transpose in place which is swap(m,n);
				if(MultAlg1(Btrans, cnz, mydcsc) < 0)
					return SparseDColumn(zero, A.m, B.n, zero);	// result is an m by n matrix of complete zeros
				else
					return SparseDColumn (cnz, A.m, B.n, mydcsc);
			}
			else
			{
				if(MultAlg1(B, cnz, mydcsc) < 0)
					return SparseDColumn(zero, A.m, B.n, zero);	// result is an m by n matrix of complete zeros
				else
					return SparseDColumn (cnz, A.m, B.n, mydcsc);

			}			
		}	
	}
        else
        {
                cerr <<"Not multipliable: " << A_n << "!=" << B_m << endl;
        	return *this;
	} 
}


/*************************************************************/
/********************* PRIVATE FUNCTIONS *********************/
/*************************************************************/


template <class IT, class NT>
inline void SparseDColumn<T>::CopyDcsc(Dcsc<T> * source)
{
	// source dcsc will be NULL if number of nonzeros = 0 
	if(source != NULL)	
		dcsc = new Dcsc<T>(*source);
	else
		dcsc = NULL;
}

//! \remarks Can multiply matrices of size up to ITYPEMAX times ITYPEMAX 
template <class IT, class NT>
SparseDColumn<T> SparseDColumn<T>::OrdOutProdMult(const SparseDColumn<T> & rhs) const
{
	ITYPE cnz;
	Dcsc<T> * mydcsc = NULL;

	ITYPE zero = static_cast<ITYPE>(0);
	if(nzmax == 0 || rhs.nzmax == 0)
	{
		return SparseDColumn(zero, m, rhs.n, zero);		// result is an m by n matrix of complete zeros
	}
	else
	{
#ifdef MPITIMER
		timer t = timer();
#endif
		SparseDColumn<T> Btrans = rhs.TransposeConst();
		Btrans.TransposeInPlace();	// calls SparseMatrix's Transpose in place which is swap(m,n);
#ifdef MPITIMER
		double fin = t.elapsed();
		cout<<fin<<",";
#endif

		if(MultAlg1(Btrans, cnz, mydcsc) < 0)
		{
			return SparseDColumn(zero, m, rhs.n, zero);	// result is an m by n matrix of complete zeros
		}
		else
		{
			return SparseDColumn (cnz, m,rhs.n, mydcsc);
		}
	}
}


template <class IT, class NT>
SparseDColumn<T> SparseDColumn<T>::OrdColByCol(const SparseDColumn<T> & rhs) const
{
	ITYPE cnz;
	Dcsc<T> * mydcsc = NULL;

	ITYPE zero = static_cast<ITYPE>(0);
	if(nzmax == 0 || rhs.nzmax == 0)
	{
		return SparseDColumn(zero, m, rhs.n, zero);		// result is an m by n matrix of complete zeros
	}
	else
	{
		if(MultAlg2(rhs, cnz, mydcsc) < 0)	// change this to change algorithms
		{
			return SparseDColumn(zero, m, rhs.n, zero);	// result is an m by n matrix of complete zeros
		}
		else
		{
			return SparseDColumn (cnz, m,rhs.n, mydcsc);
		}
	}
}

/**
 * C += A*B' (Using OuterProduct Algorithm)
 * This version is limited to single precision (i.e. it can't multiply double-precision matrices with booleans)
 * The multiplication is on the standard (+,*) semiring
 */
template <class IT, class NT>
int SpDCCols<IT,NT>::PlusEq_AnXBt(const SpDCCols<IT,NT> & A, const SpDCCols<IT,NT> & B)
{
	if(A.isZero() || B.isZero())
	{
		return -1;	// no need to do anything
	}

	Isect *isect1, *isect2;
	Isect *itr1, *itr2;
	Isect *cols, *rows;

	SpHelper::SpIntersect(A->dcsc, B->dcsc, cols, rows, isect1, isect2, itr1, itr2);
	
	IT kisect = static_cast<IT>(itr1-isect1);		// size of the intersection ((itr1-isect1) == (itr2-isect2))
	if(kisect == zero)
	{
		DeleteAll(isect1, isect2, cols, rows);
		return -1;
	}
	
	StackEntry<NT, pair<IT,IT> > * multstack;
	PlusTimesSRing ptsr;
	IT cnz = SpHelper::SpCartesian (A.dcsc, B.dcsc, ptsr, kisect, isect1, isect2, multstack);  

	IT mdim = A.m;	
	IT ndim = B.m;		// since B has already been transposed
	if(isZero())
	{
		dcsc = new Dcsc<IT,NT>(multstack, mdim, ndim, cnz);
	}
	else
	{
		dcsc->AddAndAssign(multstack, mdim, ndim, cnz);
	}

	DeleteAll(isect1, isect2, cols, rows, multstack);
	return 1;	
}

/**
 * C += A*B (Using ColByCol Algorithm)
 * \todo Not yet implemented but it will be very similar to SparseDColumn<T>::MultAlg2
 */
template <class IT, class NT>
int SparseDColumn<T>::PlusEq_AnXBn(const SparseDColumn<T> & A, const SparseDColumn<T> & B)
{
	cout << "PlusEq_AnXBn function has not been implemented yet !" << endl;
	return 0;
}


template <class IT, class NT>
int SparseDColumn<T>::PlusEq_AtXBn(const SparseDColumn<T> & A, const SparseDColumn<T> & B)
{
	cout << "PlusEq_AtXBn function has not been implemented yet !" << endl;
	return 0;
}

template <class IT, class NT>
int SparseDColumn<T>::PlusEq_AtXBt(const SparseDColumn<T> & A, const SparseDColumn<T> & B)
{
	cout << "PlusEq_AtXBt function has not been implemented yet !" << endl;
	return 0;
}



/**
 * this = this * rhs (using Alg 1)
 */
template <class IT, class NT>
template <typename T2>
int SparseDColumn<T>::MultAlg1(const SparseDColumn<T2> & rhs, ITYPE & cnz, Dcsc<T> * & mydcsc) const
{
	// Take the outer product of this.dcsc and rhs.dcsc [which is tranposed]
	RowColumn *isect1, *isect2;
	RowColumn *itr1, *itr2;
	RowColumn *cols, *rows;
	MultPreprocess(rhs, cols, rows, isect1, isect2, itr1, itr2);
	
	ITYPE kisect = static_cast<ITYPE>(itr1-isect1);		// size of the intersection (== itr2-isect2)
	if(kisect == 0)
	{
		delete [] isect1;
		delete [] isect2;
		delete [] cols;
		delete [] rows;
		return -1;
	}
	
	StackEntry<T, IPAIR > * multstack;
	MultPhase(rhs, kisect, cnz, isect1, isect2, multstack);

	ITYPE mdim = m;	
	ITYPE ndim = rhs.m;	// since rhs has already been transposed

	if(mydcsc != NULL) 
		delete mydcsc;
	mydcsc = new Dcsc<T>(multstack, mdim, ndim, cnz);

	delete [] isect1;
	delete [] isect2;
	delete [] cols;
	delete [] rows; 
	delete [] multstack;
	return 1;
}

/**
 * First needs to construct AUX if does not already exist, then performs this = this * rhs (using Alg-2)
 * \pre If AUX is not NULL, then it is an up-to-date correct version.
 *  i.e. any modification on a matrix does either update AUX correctly before returning
 *  or deletes the aux (and sets it to NULL) after the operation 
 */
template <class IT, class NT>
int SparseDColumn<T>::MultAlg2(const SparseDColumn<T> & rhs, ITYPE & cnz, Dcsc<T> * & mydcsc) const
{	
	if(dcsc->aux == NULL)
		dcsc->ConstructAux(n);

	cnz = 0;						
	ITYPE cnzmax = rhs.nzmax + nzmax;	// estimate on the size of resulting matrix C
	StackEntry<T, IPAIR > * multstack = new StackEntry<T, IPAIR >[cnzmax];	// the stack that holds the results 

	for(ITYPE i=0; i< (rhs.dcsc)->nzc; ++i)		// for all the columns of B
	{	

		// keys of the heap are row indices only
		// heap of size ((rhs.dcsc)->mas[i+1]-(rhs.dcsc)->mas[i])
		KNHeap< ITYPE , HeapEntry<T> > workingset(ITYPEMAX, ITYPEMIN);
	
		// colnums vector keeps requested column numbers
		vector<ITYPE> colnums((rhs.dcsc)->mas[i+1] - (rhs.dcsc)->mas[i]);

		// colinds.first vector keeps indices to the mas array of "this", i.e. it dereferences "colnums" vector (above),
		// colinds.second vector keeps the end indices (i.e. it gives the index to the last valid element of the mas array)
		vector<IPAIR> colinds((rhs.dcsc)->mas[i+1] - (rhs.dcsc)->mas[i]);		

		ITYPE k =0;
		for(ITYPE j=(rhs.dcsc)->mas[i]; j<(rhs.dcsc)->mas[i+1]; ++j)	
		{
			// for all the rows inside the ith nonzero-column, i.e the column (rhs.dcsc)->jc[i]
			colnums[k] = (rhs.dcsc)->ir[j];
			k++;
		}
		assert(k == colnums.size());

		FillColInds(colnums, colinds);
		ITYPE maxnnz = 0;	// max number of nonzeros in C(:,i)	
		ITYPE heapsize = 0;
		
		// create the initial heap
		for(ITYPE j =0; j< k; ++j)		// k = colnums.size()
		{
			if(colinds[j].first != colinds[j].second)	// current != end
			{
				workingset.insert(dcsc->ir[colinds[j].first], HeapEntry<T>(dcsc->numx[colinds[j].first],j));	// insert(key,value)
				maxnnz += colinds[j].second - colinds[j].first;
				heapsize++;
			} 
		}	

		if (cnz + maxnnz > cnzmax)		// double the size of multstack
		{
			SpHelper::DoubleStack(multstack, cnzmax, maxnnz);
		} 

		while(heapsize > 0)
		{
			ITYPE key;	
			HeapEntry<T> hentry;
			workingset.deleteMin(&key, &hentry);

			if(cnz != 0 && multstack[cnz-1].key.second == key)
			{
				multstack[cnz-1].value += hentry.value * (rhs.dcsc)->numx[(rhs.dcsc)->mas[i]+hentry.runrank];
			}
			else
			{
				multstack[cnz].value = hentry.value * (rhs.dcsc)->numx[(rhs.dcsc)->mas[i]+hentry.runrank];
				multstack[cnz++].key = IPAIR((rhs.dcsc)->jc[i], key);	// first entry is the column index since this will be in column-major order
			}

			colinds[hentry.runrank].first++;
			if(colinds[hentry.runrank].first != colinds[hentry.runrank].second)	// current != end
				workingset.insert(dcsc->ir[colinds[hentry.runrank].first], HeapEntry<T>(dcsc->numx[colinds[hentry.runrank].first],hentry.runrank));
			else
				--heapsize;
		}
	}

	ITYPE mdim = m;	
	ITYPE ndim = rhs.n;	// rhs has NOT been transposed

	if(mydcsc != NULL) 
		delete mydcsc;
	mydcsc = new Dcsc<T>(multstack, mdim, ndim, cnz);

	delete [] multstack;
	return 0;
}

template <class IT, class NT>
void SparseDColumn<T>::FillColInds(const vector<ITYPE> & colnums, vector<IPAIR> & colinds) const
{
	ITYPE nind = colnums.size();
	if ( (dcsc->nzc / nind) < THRESHOLD) 			// use scanning indexing
	{
		ITYPE mink = min(dcsc->nzc, nind);
		IPAIR * isect = new IPAIR[mink];
		IPAIR * range1 = new IPAIR[dcsc->nzc];
		IPAIR * range2 = new IPAIR[nind];
		
		for(ITYPE i=0; i < dcsc->nzc; ++i)
		{
			range1[i] = make_pair(dcsc->jc[i], i);	// get the actual nonzero value and the index to the ith nonzero
		}
		for(ITYPE i=0; i < nind; ++i)
		{
			range2[i] = make_pair(colnums[i], 0);	// second element doesn't matter since all the intersecting elements are copied from the first range
		}

		IPAIR * itr = set_intersection(range1, range1 + dcsc->nzc, range2, range2+nind, isect, SpHelper::first_compare);
		// isect now can iterate on a subset of the elements of range1
		// meaning that the intersection can be accessed directly by isect[i] instead of range1[isect[i]]
		// this is because the intersecting elements are COPIED to the output range "isect"

		ITYPE kisect = static_cast<ITYPE>(itr-isect);		// size of the intersection 
		
		for(ITYPE j=0, i =0; j< nind; ++j)
		{
			// the elements represented by dcsc->jc[isect[i] are a subset of the elements represented by colnums[j]
			if( i == kisect || isect[i].first != colnums[j])
			{
				// not found, signal by setting first = second
				colinds[j].first = 0;
				colinds[j].second = 0;	
			}
			else	// i < kisect && dcsc->jc[isect[i]] == colnums[j]
			{
				ITYPE p = isect[i++].second;
				colinds[j].first = dcsc->mas[p];
				colinds[j].second = dcsc->mas[p+1];
			}
		}
		delete [] isect;
		delete [] range1;
		delete [] range2;
	}
	else	 	// use aux based indexing
	{
		bool found;
		for(ITYPE j =0; j< nind; ++j)
		{
			IT pos = dcsc->AuxIndex(colnums[i], found);
			if(found)
			{
				colinds[j].first = dcsc->mas[pos];
				colinds[j].second = dcsc->mas[pos+1];
			}
			else 	// not found, signal by setting first = second
			{
				colinds[j].first = 0;
				colinds[j].second = 0;
			}
		}
	}
}

template <class IT, class NT>
ofstream& SparseDColumn<T>::put(ofstream& outfile) const 
{
	if(nzmax == 0)
	{
		outfile << "Matrix Doesn't have any nonzeros" <<endl;
		return outfile;
	}

	// Print the columnwise storage
	if(dcsc != NULL)
	{
		outfile << "DCSC:"<<endl;
		if(dcsc->aux != NULL)
		{
			outfile << "aux = [";
			for(ITYPE i =0; i< dcsc->colchunks; i++)
			{
				outfile << dcsc->aux[i] << ", ";
			}
			outfile << dcsc->aux[dcsc->colchunks] <<"]" << endl;
		}
		else
		{
			outfile << "aux is empty !" <<endl;
		}

		outfile << "mas = [";
		for(ITYPE i =0; i< dcsc->nzc; i++)
		{
			outfile << dcsc->mas[i] << ", ";
		}
		outfile << dcsc->mas[dcsc->nzc] <<"]" << endl;

		outfile << "jc = [";
		for(ITYPE i =0; i< dcsc->nzc-1; i++)
		{
			outfile << dcsc->jc[i] << ", ";
		}
		outfile << dcsc->jc[ dcsc->nzc-1] <<"]" << endl;

		outfile << "ir = [";
		for(ITYPE i =0; i< dcsc->nz-1; i++)
		{
			outfile << dcsc->ir[i] << ", ";
		}
		outfile << dcsc->ir[dcsc->nz-1] <<"]" << endl;

		outfile << "numx = [";
		for(ITYPE i =0; i< dcsc->nz-1; i++)
		{
			outfile << dcsc->numx[i] << ", ";
		}
		outfile << dcsc->numx[dcsc->nz-1] <<"]" << endl;
	}
	else
	{
		outfile << "DCSC doesn't exist !" <<endl;
	}
	return outfile;
}


template<class IT, class NT>
inline ITYPE * SparseDColumn<T>::GetJC()
{
	if(dcsc != NULL)
		return dcsc->jc;
	else
		return NULL;
}
template<class IT, class NT>
inline ITYPE * SparseDColumn<T>::GetMAS()
{
	if(dcsc != NULL)
		return dcsc->mas;
	else
		return NULL;
}
template<class IT, class NT>
inline ITYPE * SparseDColumn<T>::GetIR()
{
	if(dcsc != NULL)
		return dcsc->ir;
	else
		return NULL;
}
template<class IT, class NT>
inline T * SparseDColumn<T>::GetNUM()
{
	if(dcsc != NULL)
		return dcsc->numx;
	else
		return NULL;
}

template<class IT, class NT>
inline ITYPE SparseDColumn<T>::GetJCSize()
{
	if(dcsc != NULL)
		return dcsc->nzc;
	else
		return 0;
}
template<class IT, class NT>
inline ITYPE SparseDColumn<T>::GetSize()
{
	if(dcsc != NULL)
		return dcsc->nz;
	else
		return 0;
}

template<class IT, class NT>
inline void SparseDColumn<T>::ReserveJCSpace(int mynzc)
{
	dcsc->nzc = mynzc; 
	if (dcsc->jc == NULL)
		dcsc->jc = new ITYPE[dcsc->nzc];
}

template<class IT, class NT>
inline void SparseDColumn<T>::SaveJC(vector<ITYPE> & my_jc)
{
	if (dcsc->jc == NULL)
		cout<<"JC doesn't have space, you should have called ReserveJCSpace before calling SaveJC"<<endl;
	else
	{
		for(ITYPE i =0; i< dcsc->nzc; i++)
		{
			dcsc->jc[i] = my_jc[i];
		}
	}
}	

template<class IT, class NT>
inline void SparseDColumn<T>::DeleteDcsc()
{
	if(dcsc != NULL)
		delete dcsc;
	dcsc = NULL;
	return;
}

template<class IT, class NT>
Dcsc<T> * SparseDColumn<T>::GetDcsc()
{
	return dcsc;
}

template<class IT, class NT>
void SparseDColumn<T>::printInfo()
{
	cout<<"m: "<<m<<",n: "<<n<<",nzmax: "<<nzmax;
	if(dcsc != NULL)
	{
		cout<<", nzc: "<< dcsc->nzc;
		cout<<", nz: "<< dcsc->nz;
	}
	cout << endl;
}

