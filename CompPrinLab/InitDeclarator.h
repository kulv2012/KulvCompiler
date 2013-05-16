#pragma once 
#include "BasicObject.h"
#include "Declarator.h"
#include "Initializer.h"


class InitDeclarator : public BasicObject
{
public:
	InitDeclarator( ) {
		name = "init-declarator" ;
		pDecl = NULL ;
		pInitializer = NULL ;
	}
	virtual ~InitDeclarator(){
		SAFE_DELETE (pDecl) ;
		SAFE_DELETE(pInitializer)  ;
	}
	//string   GetIdentify( ){
	//	return pDecl->GetIdentify() ;
	//}
	Declarator *pDecl ;
	Initializer *pInitializer ;
protected:
private:
};