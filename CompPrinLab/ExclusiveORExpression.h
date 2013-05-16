#pragma once 
#include "BasicObject.h"
#include "ANDExpression.h"

class ExclusiveORExpression : public BasicObject
{
public:
	ExclusiveORExpression( ) {
		name = "exclusive-OR-expression" ;
		pANDExpn = NULL ;
		pExcsORExpn = NULL;
	}
	virtual ~ExclusiveORExpression(){
		SAFE_DELETE(pANDExpn) ;
		SAFE_DELETE(pExcsORExpn) ;
	}
	string tmpentry ;
	ANDExpression *pANDExpn ;
	ExclusiveORExpression *pExcsORExpn ;
protected:
private:
};

/*

exclusive-OR-expression:
AND-expression 
exclusive-OR-expression ^ AND-expression  

*/