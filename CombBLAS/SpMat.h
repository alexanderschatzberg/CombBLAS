/****************************************************************/
/* Sequential and Parallel Sparse Matrix Multiplication Library */
/* version 2.3 --------------------------------------------------/
/* date: 01/18/2009 ---------------------------------------------/
/* author: Aydin Buluc (aydin@cs.ucsb.edu) ----------------------/
/****************************************************************/

#ifndef _SP_MAT_H
#define _SP_MAT_H

#include <iostream>
#include <vector>
#include <utility>
#include "SequenceHeaps/knheap.C"
#include "SpDefs.h"
#include "LocArr.h"

using namespace std;


/**
 ** The abstract base class for all derived sequential sparse matrix classes
 ** Contains no data members, hence no copy constructor/assignment operator
 ** Uses both static (curiously recurring templates) and dynamic polymorphism (virtual functions) 
 ** Template parameters: IT (index type), NT (numerical type), DER (derived class type)
 **/
template <class IT, class NT, class DER>
class SpMat
{
public:
	virtual ~SpMat(){};	// Virtual destructor

	SpMat<IT, NT, DER> * operator() (const vector<IT> & ri, const vector<IT> & ci) const = 0;
	
	void MultiplyAddAssign(SpMat<IT, NT, DER> & A, SpMat<IT, NT, DER> & B, bool isAT, bool isBT);

	void printInfo() = 0;
	vector< LocArr<IT> > getarrays() const = 0;
		
	ofstream& put(ofstream& outfile) const 
	{ 
		return static_cast<DER*>(this)->put(outfile);
	}
	ifstream& get(ifstream& infile)
	{
		return static_cast<DER*>(this)->get(infile);
	}
	
	/** Do I really need any of this functions?
	virtual bool isZero() = 0;
	void setnnz (IT nz) = 0;
	void setrows(IT rows) = 0;
	void setcols(IT cols) = 0;
	virtual IT getrows() const = 0;
	virtual IT getcols() const = 0;
	virtual IT getnnz() const = 0;
	**/
protected:

	template <typename UIT, typename UNT, typename UDER>
	friend ofstream& operator<< (ofstream& outfile, const SpMat<UIT, UNT, UDER> & s);	

	template <typename UIT, typename UNT, typename UDER>
	friend ifstream& operator>> (ifstream& infile, SpMat<UIT, UNT, UDER> & s);	
};

#include "SpMat.cpp"	
#endif

