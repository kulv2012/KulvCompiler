#pragma once 
#include "BasicObject.h"
//#include "AssignmentExpression.h"

class AssignmentExpression ;

class ArgumentExpressionList : public BasicObject
{
public:
	ArgumentExpressionList( ) {
		name = "argument-expression-list" ;
	}
	AssignmentExpression *pAsgmExpn ;
	ArgumentExpressionList *pArgmExpn ;

protected:
private:
};

/*

argument-expression-list:
assignment-expression 
argument-expression-list , assignment-expression 

*/