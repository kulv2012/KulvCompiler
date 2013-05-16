#pragma once 
#include "BasicObject.h"
#include "Pointer.h"
#include "DirectAbstractDeclarator.h"

class AbstractDeclarator : public BasicObject
{
public:
	AbstractDeclarator( ) {
		name = "abstract-declarator" ;
	}
	Pointer *pPointer ;
	DirectAbstractDeclarator *pDirtAbstDecl ;
protected:
private:
};

/*

abstract-declarator:
pointer 
direct-abstract-declarator 
pointer direct-abstract-declarator 

*/