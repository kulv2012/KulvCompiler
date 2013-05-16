
#pragma once 
#include "BasicObject.h"
#include "UnaryExpression.h"
#include "TypeName.h"

class UnaryExpression;
class CastExpression : public BasicObject
{
public:
	CastExpression( ) {
		name = "cast-expression" ;
	}
	string tmpentry ;
	UnaryExpression *pUnryExpn ;
	CastExpression * pCastExpn ;
	TypeName *pTypeName ;
protected:
private:
};

/*

cast-expression:
unary-expression 
( type-name ) cast-expression  

*/