#pragma once 
#include "BasicObject.h"
#include "AssignmentExpression.h"
#include "InitializerList.h"

class Initializer : public BasicObject
{
public:
	Initializer( ) {
		name = "initializer" ;
	}

	AssignmentExpression *pAsgmExpn ;
	InitializerList *pInitList ;
protected:
private:
};

/*

initializer:
assignment-expression 
{ initializer-list } 
{ initializer-list , }  

*/