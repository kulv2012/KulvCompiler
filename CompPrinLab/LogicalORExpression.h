#pragma once 
#include "BasicObject.h"
#include "LogicalANDExpression.h"

class LogicalORExpression : public BasicObject
{
public:
	LogicalORExpression( ) {
		name = "logical-OR-expression" ;
		pLoglANDExpn = NULL ;
		pLoglORExpn = NULL ;
	}
	virtual ~LogicalORExpression(){
		SAFE_DELETE(pLoglORExpn) ;
		SAFE_DELETE(pLoglANDExpn) ;
	}
	string tmpentry ;
	LogicalANDExpression * pLoglANDExpn ;
		LogicalORExpression * pLoglORExpn ;

protected:
private:
};

/*

logical-OR-expression:
logical-AND-expression 
logical-OR-expression || logical-AND-expression  

*/