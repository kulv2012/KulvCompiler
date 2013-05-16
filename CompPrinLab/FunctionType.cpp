#include "StdAfx.h"
#include "FunctionType.h"

FunctionType::FunctionType(void)
:pRetnType(NULL)
{
}

FunctionType::~FunctionType(void)
{
	SAFE_DELETE(pRetnType );
	vector< TypeSpecifier *>::iterator it =  pParamTypeList.begin();
	while ( it != pParamTypeList.end() ) {
		SAFE_DELETE( *it ) ;
		it ++  ;
	}
}

TypeSpecifier *FunctionType::CopyType(  ){
	FunctionType *tmp = new FunctionType ;
	tmp->entryAddress = this->entryAddress ;
	tmp->kind = this->kind ;
	tmp->name = this->name ;
	tmp->pRetnType = this->pRetnType ;
	tmp->pParamTypeList = this->pParamTypeList ;
	return tmp ;
 }