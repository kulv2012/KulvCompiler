#pragma once 
#include "BasicObject.h"
#include "AdditiveExpression.h"

class ShiftExpression : public BasicObject
{
public:
	ShiftExpression( ) {
		name = "shift-expression" ;
		pAddtExpn= NULL ;
		pShftExpn = NULL ;
	}
	virtual ~ShiftExpression() {
		SAFE_DELETE(pAddtExpn) ;
		SAFE_DELETE(pShftExpn) ;
	}
	string tmpentry ;
	AdditiveExpression *pAddtExpn ;
	ShiftExpression *pShftExpn ;

protected:
private:
};

/*

shift-expression:
additive-expression 
shift-expression << additive-expression 
shift-expression >> additive-expression  

*/