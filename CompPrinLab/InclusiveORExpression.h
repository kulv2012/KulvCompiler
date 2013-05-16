#pragma once 
#include "BasicObject.h"
#include "ExclusiveORExpression.h"


class InclusiveORExpression : public BasicObject
{
public:
	InclusiveORExpression( ) {
		name = "inclusive-OR-expression" ;
		pExcsORExpn = NULL ;
		pIncsORExpn = NULL ;
	}
	virtual ~InclusiveORExpression() {
		SAFE_DELETE(pExcsORExpn) ;
		SAFE_DELETE(pIncsORExpn) ;
	}
	string tmpentry ;
	ExclusiveORExpression *pExcsORExpn ;
	InclusiveORExpression *pIncsORExpn ;
protected:
private:
};


/*

inclusive-OR-expression:
exclusive-OR-expression 
inclusive-OR-expression | exclusive-OR-expression 

*/