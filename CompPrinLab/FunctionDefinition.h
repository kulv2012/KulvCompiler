#pragma once 
#include "BasicObject.h"
#include "Declarator.h"
#include "CompoundStatement.h"
#include "DeclarationList.h"
#include "DeclarationSpecifiers.h"


class FunctionDefinition:public BasicObject
{
public:
	FunctionDefinition() {
		name = "function-definition" ;
		pDecl = NULL ;
		pCompStatm = NULL ;
		pDeclList  = NULL ;
		pDeclSpfr = NULL ;
	}
	virtual ~FunctionDefinition() {
		SAFE_DELETE(pDecl ) ;
		SAFE_DELETE( pCompStatm) ;
		SAFE_DELETE(pDeclList ) ;
		SAFE_DELETE( pDeclSpfr) ;
	}

	Declarator * pDecl ;
		CompoundStatement *pCompStatm ;

		DeclarationList *pDeclList ;
	DeclarationSpecifiers *pDeclSpfr ;
protected:
private:
};

