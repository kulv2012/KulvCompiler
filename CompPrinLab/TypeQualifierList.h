#pragma once 
#include "BasicObject.h"
#include "TypeQualifier.h"

class TypeQualifierList : public BasicObject
{
public:
	TypeQualifierList( ) {
		name = "type-qualifier-list" ;
	}
	
	TypeQualifier *pTypeQuafr ;
	TypeQualifierList *pTypeQufrList ;
protected:
private:
};