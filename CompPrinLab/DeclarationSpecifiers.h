#pragma once
#include "BasicObject.h" 
#include "StorageClassSpecifier.h"
#include "TypeSpecifier.h"
#include "TypeQualifier.h"


class DeclarationSpecifiers :public BasicObject
{
public:
	DeclarationSpecifiers (void) {
		name = "declaration-specifiers" ;
		pStorClsSpfr = NULL ;
		pDecSpfr = NULL ;
		//pTypeSpfr = NULL ;
		pTypeQufr = NULL ;
	}
	~DeclarationSpecifiers(void){
		SAFE_DELETE( pStorClsSpfr) ;
		SAFE_DELETE( pDecSpfr) ;
		//SAFE_DELETE( pTypeSpfr) ;
		SAFE_DELETE( pTypeQufr) ;
	};
	TypeSpecifier* GetTypeSpecifiers(){
		if ( subProduction ==  2||subProduction == 3) {
			return pTypeSpfr ;
		}
		else{
			return pDecSpfr->GetTypeSpecifiers() ;
		}
	}
	/*int CopyTypeSpecifier(TypeSpecifier *tmp ){
		this->kind = tmp->kind ;
		this->width = tmp->width ;
		return 0 ;
	}*/
	StorageClassSpecifier *pStorClsSpfr ;
								DeclarationSpecifiers *pDecSpfr ;
	TypeSpecifier * pTypeSpfr ;//可以直接删除了
	TypeQualifier * pTypeQufr ;
};


/*

declaration-specifiers:
storage-class-specifier ##估计这个没用,肯定是错的
storage-class-specifier declaration-specifiers 
type-specifier 
type-specifier declaration-specifiers 
type-qualifier 
type-qualifier declaration-specifiers 


*/