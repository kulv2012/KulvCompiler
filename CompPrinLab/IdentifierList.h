#pragma once 
#include "BasicObject.h"


class IdentifierList : public BasicObject
{
public:
	IdentifierList( ) {
		name = "identifier-list" ;
		//assert(1 != 1 ) ;//��ʶ��û����string��ʾ
	}
	
	IdentifierList *pIdtfList ;
	string identify ;

protected:
private:
};

/*

identifier-list:
identifier    
identifier-list , identifier  

*/