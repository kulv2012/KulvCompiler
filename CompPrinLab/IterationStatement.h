#pragma once 
#include "BasicObject.h"
#include "Expression.h"
#include "Statement.h"


class IterationStatement : public BasicObject
{
public:
	IterationStatement( ) {
		name = "iteration-statement" ;
	}

	Expression pExpnFrist ;
	Expression pExpnSecond ;
	Expression pExpnThrid ;

	Statement * pStmt ;
protected:
private:
};


/*

iteration-statement:
while  ( expression ) statement 
do  statement while  ( expression ) ;
for  ( ; ; )  statement 
for  ( ; ; expression )  statement 
for  ( ; expression ; )  statement 
for  ( ; expression ; expression )  statement 
for  ( expression ; ; )  statement 
for  ( expression ; ; expression )  statement 
for  ( expression ; expression ; )  statement 
for  ( expression ; expression ; expression )  statement 


*/