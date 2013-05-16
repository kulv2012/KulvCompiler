#pragma once 
#include "BasicObject.h"
#include "Expression.h"

class ExpressionStatement : public BasicObject
{
public:
	ExpressionStatement( ) {
		name = "expression-statement" ;
	}

	Expression * pExpn ;
protected:
private:
};

/*

expression-statement:
	; 
	expression ; */