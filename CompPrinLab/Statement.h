#pragma once 
#include "BasicObject.h"
#include "LabeledStatement.h"
#include "ExpressionStatement.h"
//#include "CompoundStatement.h"
#include "SelectionStatement.h"
#include "IterationStatement.h"
#include "JumpStatement.h"

class CompoundStatement ;
class Statement : public BasicObject
{
public:
	Statement( ) ;/*{
		name = "statement" ;
		pLabdStmt = NULL ;
		pExpnStmt = NULL ;
		pCmpdStmt = NULL ;
		pSelctStmt = NULL ;
		pItertStmt = NULL ;
		pJumpStmt = NULL ;
	}*/
	virtual ~Statement() ;/*{
		SAFE_DELETE( pLabdStmt ) ;
		SAFE_DELETE( pExpnStmt ) ;
		SAFE_DELETE( pCmpdStmt ) ;
		SAFE_DELETE( pSelctStmt ) ;
		SAFE_DELETE( pItertStmt ) ;
		SAFE_DELETE( pJumpStmt ) ;
	}*/

	LabeledStatement * pLabdStmt ;
	ExpressionStatement * pExpnStmt ;
	CompoundStatement * pCmpdStmt ;
	SelectionStatement * pSelctStmt ;
	IterationStatement * pItertStmt ;
	JumpStatement * pJumpStmt ;
protected:
private:
};

/*

statement:
labeled-statement 
expression-statement 
compound-statement 
selection-statement 
iteration-statement 
jump-statement  


*/