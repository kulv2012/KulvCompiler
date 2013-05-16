#include "stdafx.h"
#include "DeclarationHeaders.h"


Statement::Statement( ) {
	name = "statement" ;
	pLabdStmt = NULL ;
	pExpnStmt = NULL ;
	pCmpdStmt = NULL ;
	pSelctStmt = NULL ;
	pItertStmt = NULL ;
	pJumpStmt = NULL ;
}
Statement::~Statement()  {
	SAFE_DELETE( pLabdStmt ) ;
	SAFE_DELETE( pExpnStmt ) ;
	SAFE_DELETE( pCmpdStmt ) ;
	SAFE_DELETE( pSelctStmt ) ;
	SAFE_DELETE( pItertStmt ) ;
	SAFE_DELETE( pJumpStmt ) ;
}