#pragma once
#include <vector>
#include <string>
#include "TypeSpecifier.h"
#include "BasicObject.h"

class Constant : public BasicObject
{
public:
	Constant(void);
	~Constant(void);
	string ToString( ) ;
	TypeSpecifier * pType ;
	int entry ;
	static vector< string > m_intConstant ;
	static vector< string > m_charConstant ;
	static vector< string > m_floatConstant ;
	static vector< string > m_stringConstant ;
	int AddIntConstant( string value);
	int AddCharConstant( string value);
	int AddFloatConstant( string value);
	int AddStringConstant( string value);
};

/*
#define CST_STR			2048	//"```"
#define CST_CHAR		2049	//'*'
#define CST_CHAR_ES		2050	//'\n'
#define CST_DIGIT_8		2051	//
#define CST_DIGIT_10	2052	//
#define CST_DIGIT_16	2053	//
#define CST_FLOAT	2054	//float 
*/

/*

constant:
	integer-constant 
	character-constant 
	floating-constant 
	enumeration-constant   
	string-constant  

*/