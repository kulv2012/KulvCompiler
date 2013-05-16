#pragma once
#include "BasicObject.h"
#include "Declarator.h"
#include "ConstantExpression.h"
#include "ParameterTypeList.h"
#include "IdentifierList.h"


class DirectDeclarator : public BasicObject
{
public:
	DirectDeclarator(void); /*{
		name = "direct-declarator" ;
		pDecltr = NULL ;
		pDirtDecl = NULL ;
		pConstExpr = NULL ;
		pParmTypeList = NULL ;
		pIdntfy = NULL ;
	}*/
	virtual ~DirectDeclarator(void) ;/*{
		SAFE_DELETE(pDecltr ) ;
		SAFE_DELETE(pDirtDecl ) ;
		SAFE_DELETE(pConstExpr ) ;
		SAFE_DELETE(pParmTypeList ) ;
		SAFE_DELETE(pIdntfy ) ;
	}*/
	string identify ;
	Declarator *pDecltr ;
	DirectDeclarator *pDirtDecl ;
	ConstantExpression *pConstExpr ;
	ParameterTypeList *pParmTypeList ;
	IdentifierList * pIdntfy ;

	/*string   GetIdentify( ) ;{
		if ( subProduction == 1 ) {
			return identify ;
		}
		else if ( subProduction == 2 ) {
			return pDecltr->pDirtDecl->GetIdentify() ;
		}
		else {
			return pDirtDecl->GetIdentify() ;
		}
	}*/
	

};

/*direct-declarator:
identifier   
( declarator ) 
direct-declarator [ ] 
direct-declarator [ constant-expression ] 
direct-declarator ( parameter-type-list ) 
direct-declarator ( ) 
direct-declarator ( identifier-list ) */