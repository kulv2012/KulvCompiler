#pragma once 
#include "BasicObject.h"
//#include "LogicalORExpression.h"

class LogicalORExpression ;
class LogicalANDExpression : public BasicObject
{
public:
	LogicalANDExpression( );/* {
		name = "logical-AND-expression" ;
		pLoglANDExpn = NULL ;
		pLoglORExpn = NULL ;
	}*/
	virtual ~LogicalANDExpression();/* {
		SAFE_DELETE( pLoglORExpn) ;
		SAFE_DELETE(pLoglANDExpn) ;
	}*/
	string tmpentry ;
	LogicalANDExpression *pLoglANDExpn ;
	LogicalORExpression *pLoglORExpn ;

protected:
private:
};


/*

logical-AND-expression:
inclusive-OR-expression
logical-AND-expression && inclusive-OR-expression 

*/