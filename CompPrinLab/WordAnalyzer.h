#pragma once
#include <string>
#include "BufferStream.h"
#include "KeyWordOpSp.h"
#include <fstream>


using namespace std;



class WordAnalyzer
{
public:
	WordAnalyzer( string code ) ;
	~WordAnalyzer(void);
	
private:
	string m_strSourceCode  ;
	BufferStream bfs ;
	KeyWordOpSp stb ;
	ofstream m_TokenFile ;
	char m_newCh ;
	int m_curLine ;
	bool m_nResult ;
	bool m_bIsSucced ;
public:
	bool IsSucceed(){
		return m_nResult ;
	}
	bool RetrivalCode(void);

	string GetPureCodeFile(void);
	string GetTokenFile(void) ;
	int LaunchAnalyze(void);

	bool CheckOpSp( void );
	bool CheckSpecial( void );
	bool CheckDigit(void);
	bool CheckIDF(void);

	bool EndLine(void);
	void ReportError( int kind ,  const string detail );

	void WriteToken( int type, string str) {
		m_TokenFile << type << "\t" << str << endl ;
	}
	void ReportWarning(int kind, const string detail);
	int WriteEndSign(void){
		m_TokenFile << END_SIGN_ID << "\t" << END_SIGN  ;
		return 0 ;
	}
};
