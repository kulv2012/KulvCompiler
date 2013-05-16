#pragma once 
#include "BasicObject.h"
#include "Expression.h"

class JumpStatement : public BasicObject
{
public:
	JumpStatement( ) {
		name = "jump-statement" ;
	}

	string identify ;
	Expression * pExpn ;
protected:
private:
};


/*

jump-statement:
goto  identifier    ; 
continue  ; 
break  ; 
return  ; 
return  expression ; 

*/