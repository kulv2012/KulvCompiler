#pragma once 
#include "BasicObject.h"
//#include "Statement.h"
#include "ConstantExpression.h"

class Statement ;
class LabeledStatement : public BasicObject
{
public:
	LabeledStatement( ) {
		name = "labeled-statement" ;
	}

	string identify ;
	Statement * pStmt ;
	ConstantExpression * pConstExpn ;
protected:
private:
};

/*

labeled-statement:
identifier    : statement
case  constant-expression : statement 


default  : statement */