#pragma once
#include "BasicObject.h" 

class TypeQualifier :public BasicObject
{
public:
	TypeQualifier() {
		name = "type-qualifier" ;
	}
	string value ;
	/*const  
	volatile */
protected:
private:
};