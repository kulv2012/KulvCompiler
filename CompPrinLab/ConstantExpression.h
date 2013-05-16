#pragma once 
#include "BasicObject.h"
#include "ConditionalExpression.h"

class ConstantExpression : public BasicObject
{
public:
	ConstantExpression( ) {
		name = "constant-expression" ;
	}

	ConditionalExpression * pCndtExpn ;
protected:
private:
};

/*

constant-expression:
conditional-expression  

*/