#pragma once 
#include "BasicObject.h"
#include "ShiftExpression.h"


class RalationalExpression : public BasicObject
{
public:
	RalationalExpression( ) {
		name = "relational-expression" ;
		pShftExpn = NULL ;
		pRltnExpn = NULL ;
	}
	virtual ~RalationalExpression() {
		SAFE_DELETE(pShftExpn) ;
		SAFE_DELETE(pRltnExpn) ;
	}
	string tmpentry ;
	ShiftExpression *pShftExpn ;
	RalationalExpression *pRltnExpn ;
protected:
private:
};

/*

relational-expression:
shift-expression 
relational-expression < shift-expression 
relational-expression > shift-expression 
relational-expression <= shift-expression 
relational-expression >= shift-expression  

*/