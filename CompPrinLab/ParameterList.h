#pragma once 
#include "BasicObject.h"
#include "ParameterDeclaration.h"


class ParameterList : public BasicObject
{
public:
	ParameterList( ) {
		name = "parameter-list" ;
		pParmDecl = NULL ;
		pParmList = NULL ;
	}
	virtual ~ParameterList () {
		SAFE_DELETE ( pParmList ) ;
		SAFE_DELETE ( pParmDecl ) ;
	}
	ParameterDeclaration *pParmDecl ;
	ParameterList *pParmList ;
protected:
private:
};
/*

parameter-list:
parameter-declaration
parameter-list , parameter-declaration 

*/