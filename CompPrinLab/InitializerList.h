#pragma once 
#include "BasicObject.h"
//#include "Initializer.h"

class Initializer ;
class InitializerList : public BasicObject
{
public:
	InitializerList( ) {
		name = "initializer-list" ;
	}
	InitializerList *pInitList ;
	Initializer *pInit ;
protected:
private:
};

/*

initializer-list:
initializer 
initializer-list , initializer  

*/
