#pragma once 
#include "BasicObject.h"
#include "DeclarationSpecifiers.h"
//#include "Declarator.h"
//#include "AbstractDeclarator.h"

class Declarator ;
class AbstractDeclarator ;
class ParameterDeclaration : public BasicObject
{
public:
	ParameterDeclaration( );/* {
		name = "parameter-declaration" ;
		pDeclSpfr = NULL  ;
		pDecltr = NULL ;
		pAbstDecl = NULL ;
	}*/
	virtual ~ParameterDeclaration (); /*{
		SAFE_DELETE( pDeclSpfr ) ;
		SAFE_DELETE( pDecltr ) ;
		SAFE_DELETE( pAbstDecl ) ;
	}*/
	DeclarationSpecifiers *pDeclSpfr ;
	Declarator *pDecltr ;
	AbstractDeclarator *pAbstDecl ;

protected:
private:
};

/*

parameter-declaration:
declaration-specifiers 
declaration-specifiers declarator 
declaration-specifiers abstract-declarator 


*/