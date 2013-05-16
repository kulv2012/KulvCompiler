#pragma once
#include <string>
#include <fstream>

class TOKEN 
{
public:
	TOKEN() : type(-1) { }
 	int type ;
	string sign;
	string origrinal  ;
	int line ;
};

class TokenFile
{
public:
	TokenFile(  )  ;
	~TokenFile(void);

	int GetCurLine( ){
		return m_currentLine ;
	}
private:
	string m_tokenFile ;
	ifstream m_tokenfile ;
	int m_currentLine ;
	TOKEN m_curToken ;
	TOKEN m_lastToken ;
public:
	//m_TokenFile << type << "\t" << str << endl ;
	TOKEN lookToken(void) {
		return m_curToken ;
	}
private:
	void ReadToken(void) ;

public:
	TOKEN ExtractToken(void);
	void SetFile(string file);
	int Translate(void);
	TOKEN * GetLastToken(void);
};
