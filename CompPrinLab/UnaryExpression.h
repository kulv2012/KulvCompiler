

#pragma once 
#include "BasicObject.h"
#include "PostfixExpression.h"
#include "UnaryOperator.h"
#include "CastExpression.h"
#include "TypeName.h"

class UnaryExpression : public BasicObject
{
public:
	UnaryExpression( ) {
		name = "unary-expression" ;
	}
	string tmpentry ;
	PostfixExpression *pPostExpn ;
	UnaryExpression  *pUnryExpn ;
	UnaryOperator *pUnryOpertr ;
	TypeName *pTypeName ;
protected:
private:
};

/*
unary-expression:
postfix-expression 
++ unary-expression 
-- unary-expression 
unary-operator cast-expression 
sizeof  unary-expression 
sizeof  ( type-name ) 

*/