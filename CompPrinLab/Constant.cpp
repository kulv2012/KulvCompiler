#include "StdAfx.h"
#include "Constant.h"
#include <assert.h>
 //这到底是为什么呀？？？？申明？？定义？？那么我是不是得了解一下static的含义呢？
vector< string > Constant::m_intConstant ;
vector< string > Constant::m_charConstant ;
vector< string > Constant::m_floatConstant ;
vector< string > Constant::m_stringConstant ;


Constant::Constant(void)
:pType(NULL)
,entry(-1)
{
	name = "constant" ;
}

Constant::~Constant(void)
{
}

string Constant::ToString( ){
	if ( pType->kind == KULV_INT ) {
		return m_intConstant[entry] ;
	}
	else if ( pType->kind == KULV_FLOAT ) {
		return m_floatConstant[entry] ;
	}
	else if ( pType->kind ==KULV_CHAR ) {
		return m_charConstant[entry] ;
	}
	else if ( pType->kind == KULV_STRING ) {
		return m_stringConstant[entry] ;
	}
	else assert(0) ;
	return "" ;
}

int Constant::AddIntConstant(  string value){
	int size  = m_intConstant.size() ;
	for ( int i = 0 ; i <  size ; i ++ ) {
		if ( m_intConstant[i] == value ) {
			return i ;
		}
	}
	m_intConstant.push_back(value ) ;
	return size ;
}

int Constant::AddCharConstant(  string value){
	int size  = m_charConstant.size() ;
	for ( int i = 0 ; i <  size ; i ++ ) {
		if ( m_charConstant[i] == value ) {
			return i ;
		}
	}
	m_charConstant.push_back(value ) ;
	return size ;
}

int Constant::AddFloatConstant(  string value){
	int size  = m_floatConstant.size() ;
	for ( int i = 0 ; i <  size ; i ++ ) {
		if ( m_floatConstant[i] == value ) {
			return i ;
		}
	}
	m_floatConstant.push_back(value ) ;
	return size ;
}

int Constant::AddStringConstant( string value){
	int size  = m_stringConstant.size() ;
	for ( int i = 0 ; i <  size ; i ++ ) {
		if ( m_stringConstant[i] == value ) {
			return i ;
		}
	}
	m_stringConstant.push_back(value ) ;
	return size ;
}
