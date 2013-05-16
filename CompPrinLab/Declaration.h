#pragma once 
#include "BasicObject.h"
#include "DeclarationSpecifiers.h"
#include "InitDeclaratorList.h"


class Declaration :public BasicObject
{
public:
	Declaration() {
		name = "declaration" ;
		pDeclSpfr = NULL ;
		pInitDeclList = NULL ;
	}
	virtual ~Declaration() {
		SAFE_DELETE( pDeclSpfr) ;
		SAFE_DELETE (pInitDeclList) ;
	}
	//规约完后就可以释放了哈！！！！！！
	DeclarationSpecifiers *pDeclSpfr ;
	InitDeclaratorList *pInitDeclList ;

protected:
private:
};