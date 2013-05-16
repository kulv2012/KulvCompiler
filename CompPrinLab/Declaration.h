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
	//��Լ���Ϳ����ͷ��˹�������������
	DeclarationSpecifiers *pDeclSpfr ;
	InitDeclaratorList *pInitDeclList ;

protected:
private:
};