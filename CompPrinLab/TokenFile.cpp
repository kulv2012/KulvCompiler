#include "StdAfx.h"
#include "TokenFile.h"
#include <assert.h>

TokenFile::TokenFile( )
:m_currentLine(1)
{

}


TokenFile::~TokenFile(void)
{
	if (m_tokenfile ) {
		m_tokenfile.close() ;
	}
}

TOKEN TokenFile::ExtractToken(void)
{
	TOKEN tmp = m_curToken ;
	ReadToken() ;
	return tmp ;
}

void TokenFile::SetFile(string file)
{
	m_tokenFile = file ;
	m_tokenfile.open(m_tokenFile.c_str(),ios::in) ;
	if (!m_tokenfile) {//if orror,then exit
		(*outer) <<"Sorry ! "<<m_tokenFile<<" open error in !TokenFile"<<myendl;
		throw "  open error in !TokenFile" ;
	}
	ReadToken() ;
}

void TokenFile::ReadToken(void)
{
	m_lastToken = m_curToken ;
	while( !m_tokenfile.eof()  ){
		m_tokenfile >> m_curToken.type  ;
		char tmp ;m_tokenfile.read(&tmp,1) ;//读出那个水平制表符
		//if ( m_curToken.type == CST_STR ) {
			char line[MAX_LINE] ;
			m_tokenfile.getline(line , MAX_LINE , '\n') ;
			m_curToken.origrinal.clear();
			m_curToken.origrinal  = line ; 
		//}
		//else {
		//	m_tokenfile >> m_curToken.origrinal ;
		//}
		m_curToken.sign = m_curToken.origrinal ;
		m_curToken.line = m_currentLine ;
		if ( m_curToken.type == NEW_LINE ) {
			m_currentLine ++ ;
		}
 		else {
			//translate it 
			Translate();
			return ;
		}
	}
	//eof 
	m_curToken.type = END_OF_FILE ;
	return ;
}
int TokenFile::Translate(void)
{
	if ( m_curToken.type == KEY_WORD ) {
		;
	}
	else if ( m_curToken.type == VARIABLE ) {
		m_curToken.sign = "identifier" ;
	}
	else if ( m_curToken.type == CST_STR ) {
		m_curToken.sign = "string-constant" ;
	}
	else if ( m_curToken.type == CST_CHAR ) {
		m_curToken.sign = "character-constant" ;
	}
	else if ( m_curToken.type ==  CST_CHAR_ES) {
		m_curToken.sign = "character-constant" ;//escape char is also a char !!!
	}
	else if ( m_curToken.type == CST_DIGIT_8 ) {
		m_curToken.sign = "integer-constant" ;
	}
	else if ( m_curToken.type == CST_DIGIT_10 ) {
		m_curToken.sign = "integer-constant" ;
	}
	else if ( m_curToken.type == CST_DIGIT_16) {
		m_curToken.sign = "integer-constant" ;
	}
	else if ( m_curToken.type == CST_FLOAT  ) {
		//m_curToken.sign = 	
	}
	else{
		assert(1 == 1 ) ;
	}
	return 0;
}


TOKEN * TokenFile::GetLastToken(void)
{
	return &m_lastToken ;
}
