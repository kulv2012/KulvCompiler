#pragma once 
#include "BasicObject.h"
#include "AssignmentExpression.h"


class Expression : public BasicObject
{
public:
	Expression( ) {
		name = "expression" ;
	}
	string tmpentry ;
	Expression * pExpn ;
	AssignmentExpression * pAsgnExpn ;

protected:
private:
};

/*

expression:
assignment-expression 
expression , assignment-expression 

*/