#pragma once 
#include "BasicObject.h"
#include "TypeQualifierList.h"
#include "Pointer.h"


class Pointer : public BasicObject
{
public:
	Pointer( ) {
		name = "pointer" ;
	}

	TypeQualifierList *pTypeQufrList ;
	Pointer *pPointer ;
protected:
private:
};

/*

pointer:
*  
* type-qualifier-list 
* pointer 
* type-qualifier-list pointer 


*/