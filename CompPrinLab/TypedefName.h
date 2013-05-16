#pragma once 
#include "BasicObject.h"

class TypedefName : public BasicObject
{
public:
	TypedefName( ) {
		name = "typedef-name" ;
	}
	
	string identify ;
protected:
private:
};

/*

typedef-name:
identifier    

*/