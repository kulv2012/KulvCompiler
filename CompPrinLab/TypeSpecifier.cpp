#include "StdAfx.h"
#include "TypeSpecifier.h"
#include <assert.h>


TypeSpecifier Void(KULV_VOID , 0 ,0) ;
TypeSpecifier Char(KULV_CHAR , 1 , 1) ;
TypeSpecifier Short(KULV_SHORT , 2 ,2) ;
TypeSpecifier Integer(KULV_INT , 4 ,3) ;
TypeSpecifier Long(KULV_LONG , 8 ,4) ;
TypeSpecifier Float(KULV_FLOAT , 4 ,5) ;
TypeSpecifier Double(KULV_DOUBLE ,8 ,6) ;
TypeSpecifier Signed(KULV_SIGNED , 4 ,7 ) ;

TypeSpecifier *TypeSpecifier::CopyType(  ){
	TypeSpecifier *tmp = new TypeSpecifier() ;
	tmp->kind = this->kind ;
	tmp->name = this->name ;
	tmp->subProduction = this->subProduction ;
	tmp->width = this->width ;
	return tmp ;
}

TypeSpecifier *ARRAY::CopyType(  ){
	assert(0) ;
	return NULL ;
}