#pragma once 
#include "BasicObject.h"
#include "Declaration.h"
#include "FunctionDefinition.h"


class ExternalDeclaration:public BasicObject
{
public:
	ExternalDeclaration(){
		name = "external-declaration" ;
	}
	FunctionDefinition *pFuncDecl ;
	Declaration *pDecl ;
protected:
private:
};


