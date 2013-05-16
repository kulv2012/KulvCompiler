

#pragma once 
#include "BasicObject.h"
#include "Constant.h"
//#include "Expression.h"

class Expression ;
class PrimaryExpression : public BasicObject
{
public:
	PrimaryExpression( ) ;/*{
		name = "primary-expression" ;
	}*/
	virtual ~PrimaryExpression();/*{
		SAFE_DELETE ( pConst) ;
		SAFE_DELETE( pExpn ) ;
	}*/
	string identify ;
	Constant *pConst ;
	Expression *pExpn ;

protected:
private:
};

/*

primary-expression:
identifier   
constant 
( expression ) 


*/