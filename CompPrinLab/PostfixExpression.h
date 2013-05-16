#pragma once 
#include "BasicObject.h"
#include "PrimaryExpression.h"
#include "Expression.h"
#include "ArgumentExpressionList.h"


class PostfixExpression : public BasicObject
{
public:
	PostfixExpression( ) {
		name = "postfix-expression" ;
	}
	string tmpentry;
	PrimaryExpression *pPrmyExpn ;
	PostfixExpression *pPostExpn ;
	Expression *pExpn ;
	ArgumentExpressionList *pArgmtExpn ;
	string identify ;
protected:
private:
};

/*

postfix-expression:
primary-expression 
postfix-expression [ expression ] 
postfix-expression ( ) 
postfix-expression ( argument-expression-list ) 
##postfix-expression . identifier   
postfix-expression -> identifier    
postfix-expression ++ 
postfix-expression -- 
*/