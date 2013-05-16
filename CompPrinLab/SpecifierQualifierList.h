#pragma once 
#include "BasicObject.h"
#include "TypeSpecifier.h" 
#include "TypeQualifier.h"

class SpecifierQualifierList : public BasicObject
{
public:
	SpecifierQualifierList( ) {
		name = "specifier-qualifier-list" ;
	}
	TypeSpecifier *pTypeSpfr ;
		SpecifierQualifierList * pSpfrQuafrList ;
	TypeQualifier *PTypeQuafr ;

protected:
private:
};