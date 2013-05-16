#pragma once
#include <hash_map>
#include <string>

using namespace std;
using namespace stdext ;

extern hash_map<std::string, size_t> m_hmKeyWord ;
extern hash_map< std::string , size_t > m_hmOpSp ;

////////////////////--Kulv--2010/11/25---11:02:37--///////////////////////
//class SymbolItem
//{
//public:
//	SymbolItem( ) ;
//	int m_nId ;
//	int m_nFristLine ;
//};

////////////////////--Kulv--2010/11/25---11:02:38--///////////////////////

class KeyWordOpSp
{
public:
	KeyWordOpSp(void);
	~KeyWordOpSp(void);

private:
	hash_map<std::string, size_t> m_hmKeyWord ;
	hash_map< std::string , size_t > m_hmOpSp ;
	//hash_map<std::string, SymbolItem > m_hmIdentfy ;//数字指的是标识符在其他表里的索引！
	//hash_map<std::string, SymbolItem> m_SBItem ;
	//vector<SymbolItem> m_indi
public:

	size_t m_nIdtfSub;

	bool IsKeyWord( const string & word) {
		if ( m_hmKeyWord.count(word) != 0  ) {
			return true ;
		}
		return false;
	}

	/*SymbolItem  GetIDTF(const string & idtf) {
	if ( m_hmIdentfy.count(idtf) != 0  ) {
	return m_hmIdentfy[idtf] ;
	}
	return SymbolItem();
	}*/

	/*bool InsertIDTF(const string & idtf ,int fristline  ) {
	SymbolItem syb =  GetIDTF(idtf) ;
	if (syb.m_nId == -1 ) {
	SymbolItem sbi ;
	sbi.m_nId = m_nIdtfSub++ ;
	sbi.m_nFristLine = fristline ;
	m_hmIdentfy[idtf] = sbi;
	return true ;
	}
	return false;
	}*/

	int GetOpSpID(const string & os)
	{
		if ( m_hmOpSp.count(os) != 0  ) {
			return m_hmOpSp[os] ;
		}
		return -1;
	}
private:
	bool LoadKeyWord(void);
	bool LoadOpSp(void);
};



