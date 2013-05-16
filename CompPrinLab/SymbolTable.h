#pragma once
#include "TypeSpecifier.h"
#include <hash_map>
#include <string>
#include "BasicObject.h"

using namespace std;
using namespace stdext ;

class IdentifyInfo :public BasicObject
{
public:
	IdentifyInfo( ): entry(-1) , pType(NULL), width(0) { }
	static int ENTRY ;
	static int TMP_ID ;
	int entry ;//地址
	int width ;//宽度
	TypeSpecifier * pType ;//类型
	/*void SetType( TYPE_ENUM e ) ;*/
};

class SymbolTable
{
public:
	SymbolTable(void);
	~SymbolTable(void);
	SymbolTable * outerSymbolTable ;
	SymbolTable * innerSymbolTable ;
	int lastEntry ;
	hash_map< std::string , IdentifyInfo > m_hmIdentfy ;

	string NewTmpIdty( TypeSpecifier * sourType ) ;
	//返回值为其tmp变量的地址。
};



