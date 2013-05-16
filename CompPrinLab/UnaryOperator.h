

#pragma once 
#include "BasicObject.h"
#include <string>

class UnaryOperator : public BasicObject
{
public:
	UnaryOperator( ) {
		name = "unary-operator" ;
	}
	string  optr ;
protected:
private:
};


/*
unary-operator: 
& 
* 
+ 
- 
~ 
! */