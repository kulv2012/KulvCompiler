#pragma once 
#include "BasicObject.h"
//#include "ConditionalExpression.h"
#include "UnaryExpression.h"
#include "AssignmentOperator.h"
#include "AssignmentExpression.h"

class ConditionalExpression;
class AssignmentExpression : public BasicObject
{
public:
	AssignmentExpression( ) {
		name = "assignment-expression" ;
	}
	string tmpentry ;
	ConditionalExpression * pCndtExpn ;
	UnaryExpression * pUnryExpn ;
	AssignmentOperator * pAsgmOptr ;
	AssignmentExpression * pAsgmExpn ;

protected:
private:
};

/*

assignment-expression:
conditional-expression 
unary-expression assignment-operator assignment-expression  


*/