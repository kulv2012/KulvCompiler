#pragma once 
#include "BasicObject.h"
#include "InitDeclarator.h"


class InitDeclaratorList : public BasicObject
{
public:
	InitDeclaratorList( ) {
		name = "init-declarator-list" ;
		pInitDecl = NULL ;
		pInitDeclList = NULL ;
	}
	virtual ~InitDeclaratorList(){
		SAFE_DELETE(pInitDecl ) ;  
		SAFE_DELETE(pInitDeclList ) ; 
	}
	InitDeclarator *pInitDecl ;
	InitDeclaratorList *pInitDeclList ;
protected:
private:
};