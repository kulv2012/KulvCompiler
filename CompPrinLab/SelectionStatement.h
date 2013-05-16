#pragma once 
#include "BasicObject.h"
#include "Statement.h"
#include "Expression.h"

class SelectionStatement : public BasicObject
{
public:
	SelectionStatement( ) {
		name = "selection-statement" ;
	}

	Expression * pExpn ;
	Statement * pStmtFrist ;
	Statement * pStmtSecond ;
protected:
private:
};

/*

selection-statement: 
if  ( expression ) statement 
if  ( expression ) statement else  statement 
switch  ( expression ) statement 

*/