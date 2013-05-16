#include "stdafx.h"
#include "DeclarationHeaders.h"
#include "AbstractDeclarator.h"
#include <assert.h>

//string Declarator::GetIdentify( ){
//	return pDirtDecl->GetIdentify() ;
//}
////////////////////--Kulv--2010/12/30---2:43:22--///////////////////////
//string  DirectDeclarator::GetIdentify( ){
//	assert(0);
//	if ( subProduction == 1 ) {
//		return identify ;
//	}
//	else if ( subProduction == 2 ) {
//		return pDecltr->GetIdentify() ;
//	}
//	else{
//		return pDirtDecl->GetIdentify() ;
//	}/**/
//	return "";
//}
//string  DirectDeclarator::GetIdentify( ) {
//	if ( subProduction == 1 ) {
//		return identify ;
//	}
//	else if ( subProduction == 2 ) {
//		return pDecltr->pDirtDecl->GetIdentify() ;
//	}
//	else {
//		return pDirtDecl->GetIdentify() ;
//	}
//};
////////////////////--Kulv--2010/12/30---1:25:40--///////////////////////
PrimaryExpression::PrimaryExpression( ) {
	name = "primary-expression" ;
}
PrimaryExpression::~PrimaryExpression(){
	SAFE_DELETE ( pConst) ;
	SAFE_DELETE( pExpn ) ;
}
////////////////////--Kulv--2010/12/30---1:25:43--///////////////////////
ParameterDeclaration::ParameterDeclaration( ) {
	name = "parameter-declaration" ;
	pDeclSpfr = NULL  ;
	pDecltr = NULL ;
	pAbstDecl = NULL ;
}
ParameterDeclaration::~ParameterDeclaration () {
	SAFE_DELETE( pDeclSpfr ) ;
	SAFE_DELETE( pDecltr ) ;
	SAFE_DELETE( pAbstDecl ) ;
}
////////////////////--Kulv--2010/12/30---1:25:49--///////////////////////
DirectDeclarator::DirectDeclarator(void){
	name = "direct-declarator" ;
	pDecltr = NULL ;
	pDirtDecl = NULL ;
	pConstExpr = NULL ;
	pParmTypeList = NULL ;
	pIdntfy = NULL ;
}
DirectDeclarator::~DirectDeclarator(void){
	SAFE_DELETE(pDecltr ) ;
	SAFE_DELETE(pDirtDecl ) ;
	SAFE_DELETE(pConstExpr ) ;
	SAFE_DELETE(pParmTypeList ) ;
	SAFE_DELETE(pIdntfy ) ;
}
////////////////////--Kulv--2010/12/30---1:26:41--///////////////////////
