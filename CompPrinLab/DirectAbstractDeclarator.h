#pragma once 
#include "BasicObject.h"
#include "AbstractDeclarator.h"
//#include "ConstantExpression.h"
#include "ParameterTypeList.h"

class ConstantExpression;

class DirectAbstractDeclarator : public BasicObject
{
public:
	DirectAbstractDeclarator( ) {
		name = "direct-abstract-declarator" ;
	}

	AbstractDeclarator *pAbstDecl ;
	DirectAbstractDeclarator *pDirtAbstDecl ;
	ConstantExpression *pConstExpn ;
	ParameterTypeList *pParmTypeList ;

protected:
private:
};

/*

direct-abstract-declarator:
( abstract-declarator ) 
[ ] 
[ constant-expression ] 
direct-abstract-declarator [  ] 
direct-abstract-declarator [ constant-expression ] 
( )
( parameter-type-list ) 
direct-abstract-declarator ( ) 
direct-abstract-declarator ( parameter-type-list ) 


*/