#pragma once
#include "BasicObject.h"



class TypeSpecifier : public BasicObject
{
public:
	TypeSpecifier(){} ;
	TypeSpecifier( TYPE_ENUM k , int w , int subprod )
		: kind ( k )  
		, width ( w ) {
			name = "type-specifier" ;
			subProduction = subprod ;
	} 
	virtual ~TypeSpecifier( ){

	}
	virtual TypeSpecifier *CopyType( );
	TYPE_ENUM kind ;
	int width ;
	
};



class ARRAY :public TypeSpecifier 
{
public:
	int count ;
	TypeSpecifier * sonType ;
	virtual TypeSpecifier *CopyType( );
};
