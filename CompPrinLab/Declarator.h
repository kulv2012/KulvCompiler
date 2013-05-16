#pragma once 
#include "BasicObject.h"
#include "DirectDeclarator.h"
#include "Pointer.h"

class Declarator : public BasicObject
{
public:
	Declarator( ) {
		name = "declarator" ;
		pDirtDecl = NULL ;
		pPointer = NULL ;
	}
	virtual ~Declarator() {
		SAFE_DELETE( pDirtDecl) ;
		SAFE_DELETE( pPointer) ;
	}
	/*string GetIdentify( );{
		return pDirtDecl->GetIdentify() ;
	}*/
	DirectDeclarator *pDirtDecl ;
	Pointer * pPointer ;
protected:
private:
};

/*
declarator:
direct-declarator 
pointer direct-declarator 

*/