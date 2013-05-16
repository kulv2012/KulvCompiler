
#pragma once 
#include "BasicObject.h"
#include "CastExpression.h"

class MultiplicativeExpression : public BasicObject
{
public:
	MultiplicativeExpression( ) {
		name = "multiplicative-expression" ;
		pCastExpn =NULL ;
		pMultpExpn =NULL ;
	}
	virtual ~MultiplicativeExpression() {
		SAFE_DELETE(pMultpExpn) ;
		SAFE_DELETE(pCastExpn) ;
	}
	string tmpentry ;
	CastExpression *pCastExpn ;
	MultiplicativeExpression *pMultpExpn ;

protected:
private:
};

/*

multiplicative-expression:
cast-expression 
multiplicative-expression * cast-expression 
multiplicative-expression / cast-expression 
multiplicative-expression % cast-expression  


*/