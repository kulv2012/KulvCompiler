
#pragma once 
#include "BasicObject.h"
#include "Declaration.h"

class DeclarationList : public BasicObject
{
public:
	DeclarationList() {
		name = "declaration-list" ;
		pDecl = NULL ;
		pDeclList = NULL ;
	}
	virtual ~DeclarationList(){
		SAFE_DELETE(pDeclList) ;
		SAFE_DELETE(pDecl) ;
	}
	Declaration *pDecl ;
	DeclarationList *pDeclList ;
protected:
private:
};