#pragma once 
#include "BasicObject.h"
#include "LogicalORExpression.h"
#include "Expression.h"

class ConditionalExpression : public BasicObject
{
public:
	ConditionalExpression( ) {
		name = "conditional-expression" ;
	}
	string tmpentry ;
	LogicalORExpression * pLoglORExpn ;
	Expression * pExpn ;
	ConditionalExpression * pCndtExpn ;
protected:
private:
};

/*

conditional-expression:
logical-OR-expression 
logical-OR-expression ? expression : conditional-expression  


*/