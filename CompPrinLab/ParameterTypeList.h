#pragma once 
#include "BasicObject.h"
#include "ParameterList.h"

class ParameterTypeList : public BasicObject
{
public:
	ParameterTypeList( ) {
		name = "parameter-type-list" ;
		pParmList = NULL ;
	}
	virtual ~ParameterTypeList() {
		SAFE_DELETE(pParmList) ;
	}
	ParameterList *pParmList ;
protected:
private:
};
/*

parameter-type-list:
parameter-list 
parameter-list , ... 

*/