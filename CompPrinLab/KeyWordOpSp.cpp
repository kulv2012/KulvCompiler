#include "StdAfx.h"
#include "KeyWordOpSp.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

////////////////////--Kulv--2010/12/26---16:07:17--///////////////////////

////////////////////--Kulv--2010/11/25---11:17:11--///////////////////////
//SymbolItem::SymbolItem()
//:m_nId(-1)
//, m_nFristLine(0) 
//{
//
//}
////////////////////--Kulv--2010/11/25---11:17:08--///////////////////////
////////////////////--Kulv--2010/11/25---11:17:05--///////////////////////
KeyWordOpSp::KeyWordOpSp(void)
:m_nIdtfSub(0) 
{
	LoadKeyWord() ;
	LoadOpSp() ;
}

KeyWordOpSp::~KeyWordOpSp(void)
{
	
}

bool KeyWordOpSp::LoadKeyWord(void)
{
	//string infile(KEY_WORD_FILE) ;
	ifstream kwfile( KEY_WORD_FILE /*infile.c_str() */,ios::in) ;
	if (!kwfile) {//if orror,then exit
		throw "file open error in LoadKeyWord !" ;
	}
	size_t sub = 0 ;
	string key ;
	while ( kwfile >> key )
	{
		if ( 0 == m_hmKeyWord.count(key) ) {
			m_hmKeyWord[key] = sub++ ;
		}
	}
	kwfile.close() ;
	/*stdext::hash_map<string, size_t>::const_iterator iter = m_hmKeyWord.begin();
	while ( iter != m_hmKeyWord.end() )
	{
	(*outer)  << iter->first << myendl  ;
	iter ++ ;
	}*/
	return true;
}

bool KeyWordOpSp::LoadOpSp(void)
{
	ifstream osfile( OPERATOR_SPERATOR_FILE ,ios::in) ;
	if (!osfile) {//if orror,then exit
		throw "file open error in LoadOpSp !" ;
	}
	size_t sub = 16 ;
	string str ;
	while ( osfile >> str )
	{
		if ( 0 == m_hmOpSp.count( str ) ) {
			m_hmOpSp[ str ] = sub++ ;
		}
	}
	osfile.close() ;
	return true;
}


