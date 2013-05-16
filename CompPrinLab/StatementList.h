#pragma once 
#include "BasicObject.h"
#include "Statement.h"


class StatementList : public BasicObject
{
public:
	StatementList( ) {
		name = "statement-list" ;
		pStmt = NULL ;
		pStmtList = NULL ;
	}
	virtual ~StatementList(){
		SAFE_DELETE( pStmtList ) ;
		SAFE_DELETE( pStmt ) ;
	}

	Statement * pStmt ;
	StatementList *pStmtList ;
protected:
private:
};


/*

statement-list:
statement 
statement-list statement

*/