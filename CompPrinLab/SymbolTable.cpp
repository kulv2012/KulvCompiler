#include "StdAfx.h"
#include "SymbolTable.h"
#include <assert.h>


using namespace std;

extern TypeSpecifier Void  ;
extern TypeSpecifier Char  ;
extern TypeSpecifier Short  ;
extern TypeSpecifier Signed;
extern TypeSpecifier Integer ;
extern TypeSpecifier Long  ;
extern TypeSpecifier Float  ;
extern TypeSpecifier Double ;

int IdentifyInfo::ENTRY = 0 ;
int IdentifyInfo::TMP_ID = 0 ;
//void IdentifyInfo::SetType(TYPE_ENUM e ) {
//	switch (e )
//	{
//	case KULV_VOID: 
//		pType = &Void ;
//		break ;
//	case KULV_CHAR: 
//		pType = &Char  ;
//		break ;
//	case KULV_SHORT: 
//		pType = &Short  ;
//		break ;
//	case KULV_INT: 
//		pType = &Integer  ;
//		break ;
//	case KULV_SIGNED: 
//		pType = &Signed  ;
//		break ;
//	case KULV_LONG: 
//		pType = &Long  ;
//		break ;
//	case KULV_FLOAT: 
//		pType = &Float ;
//		break ;
//	case KULV_DOUBLE: 
//		pType = &Double  ;
//		break ;
//	case KULV_ARRAY: 
//		break ;
//
//	case KULV_FUNCTION:
//		break ;
//		//pType = &  ;
//		//break ;
//	default:
//		assert (1!=1) ;
//	}
//}

SymbolTable::SymbolTable(void)
:outerSymbolTable(NULL)
,innerSymbolTable(NULL)
,lastEntry(-1)
{
}

SymbolTable::~SymbolTable(void)
{
	m_hmIdentfy.clear() ;
}


string SymbolTable::NewTmpIdty( TypeSpecifier * sourType ) {
	string name = "__tmp__" ;
	char buf[2048] ;
	_itoa_s(IdentifyInfo::TMP_ID++,buf,10) ;
	name.append(buf) ;
	IdentifyInfo tmpId ;
	tmpId.name = name ;
	tmpId.width = sourType->width ;
	tmpId.entry = IdentifyInfo::ENTRY ;
	IdentifyInfo::ENTRY += sourType->width ;
	tmpId.subProduction = sourType->subProduction ;
	tmpId.pType = sourType->CopyType() ;
	if ( this->m_hmIdentfy.count(name)>0 ) {
		assert(0) ;
	}
	m_hmIdentfy[name] = tmpId ;
	return name ;
}