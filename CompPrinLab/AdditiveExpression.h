
#pragma once 
#include "BasicObject.h"
#include "MultiplicativeExpression.h"

class AdditiveExpression : public BasicObject
{
public:
	AdditiveExpression( ) {
		name = "additive-expression" ;
		pMultpExpn= NULL ;
		pAddtExpn =NULL  ;
	}
	virtual ~AdditiveExpression() {
		SAFE_DELETE(pAddtExpn)  ;
		SAFE_DELETE(pMultpExpn)  ;
	}
	string tmpentry ;
	MultiplicativeExpression *pMultpExpn ;
	AdditiveExpression *pAddtExpn ;
protected:
private:
};

/*

additive-expression:
multiplicative-expression 
additive-expression + multiplicative-expression 
additive-expression - multiplicative-expression  

*/