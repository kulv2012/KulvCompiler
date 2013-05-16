#pragma once 
#include "BasicObject.h"
#include "ExternalDeclaration.h"


class TranslationUnit :public BasicObject
{
public:
	TranslationUnit(){
		name = "translation-unit" ;
	}
	TranslationUnit *pTranUnit ;
		ExternalDeclaration *pExtDecl ;
	
protected:
private:
};