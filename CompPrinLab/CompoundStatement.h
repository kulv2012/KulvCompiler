#pragma once 
#include "BasicObject.h"
#include "StatementList.h"
#include "DeclarationList.h"


class CompoundStatement : public BasicObject
{
public:
	CompoundStatement( ) {
		name = "compound-statement" ;
		pStmtList = NULL ;
		pDeclList = NULL ;
	}
	virtual ~CompoundStatement(){
		SAFE_DELETE( pStmtList) ;
		SAFE_DELETE(pDeclList) ;
	}

	StatementList * pStmtList ;
	DeclarationList * pDeclList ;

protected:
private:
};


/*

compound-statement:
{ } 
{ statement-list } 
{ declaration-list } 
{ declaration-list statement-list } 
*/