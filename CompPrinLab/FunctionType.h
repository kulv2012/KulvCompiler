#pragma once
#include <string>
#include "BasicObject.h"
#include <vector>
#include "TypeSpecifier.h"

class FunctionType :public TypeSpecifier
{
public:
	FunctionType(void);
	virtual ~FunctionType(void);
	virtual TypeSpecifier *CopyType( );
	string entryAddress ;
	TypeSpecifier *pRetnType ;
	vector< TypeSpecifier *> pParamTypeList ;
};

