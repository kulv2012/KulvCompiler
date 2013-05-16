#pragma once 
#include "BasicObject.h"
#include "SpecifierQualifierList.h"
#include "AbstractDeclarator.h"


class TypeName : public BasicObject
{
public:
	TypeName( ) {
		name = "type-name" ;
	}

	SpecifierQualifierList *pSpfrQuafList ;
	AbstractDeclarator *pAbstDecl ;
protected:
private:
};

/*

type-name:
specifier-qualifier-list  
specifier-qualifier-list abstract-declarator  

*/