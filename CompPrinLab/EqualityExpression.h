#pragma once 
#include "BasicObject.h"
#include "RelationalExpression.h"



class EqualityExpression : public BasicObject
{
public:
	EqualityExpression( ) {
		name = "equality-expression" ;
		pRetnExpn = NULL ;
		pEqtyExpn = NULL ;
	}
	virtual ~EqualityExpression () {
		SAFE_DELETE( pEqtyExpn) ;
		SAFE_DELETE( pRetnExpn) ;
	}
	string tmpentry ;
	EqualityExpression * pRetnExpn ;
	EqualityExpression * pEqtyExpn ;
protected:
private:
};

/*

equality-expression:
relational-expression 
equality-expression == relational-expression 
equality-expression != relational-expression  */