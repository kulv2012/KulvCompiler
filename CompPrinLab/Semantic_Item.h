#pragma once
#include "TypeSpecifier.h"
#include "SymbolTable.h"

class IdentifyInfo ;
enum SemanticItemEnum { TYPE , IDENTIFY };
class Semantic_Item
{
public:
	Semantic_Item(void) ;
	~Semantic_Item(void);
	//int type ;
	BasicObject * pNoneterm ;
	int reserve ;
};

