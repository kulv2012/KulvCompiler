#pragma once 
#include "BasicObject.h"
#include <string>

class AssignmentOperator : public BasicObject
{
public:
	AssignmentOperator( ) {
		name = "assignment-operator" ;
	}
	string optr ;
protected:
private:
};

/*

assignment-operator:  
=  
*=  
/=  
%=  
+=  
-=  
<<= 
>>= 
&= 
^=  


|= */