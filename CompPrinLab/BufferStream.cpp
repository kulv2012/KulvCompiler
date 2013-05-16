#include "StdAfx.h"
#include "BufferStream.h"
#include <iostream>

using namespace std;

BufferStream::BufferStream( string str )
:m_strFile(str)
,m_nCurLine(0) 
,m_nBegin(0)
,m_nForward(0)
{
	if ( m_strFile != "" ) {
		m_inFile.open(str.c_str(),ios::in);
		if (!m_inFile) {//if orror,then exit
			throw "file open error in bufferstream !" ;
		}
		ReadBuf( 0 ) ;
		ReadBuf( 1 ) ;
	}
}

BufferStream::~BufferStream(void)
{
		m_inFile.close() ;
}

char BufferStream::GetNextChar(void)
{
	if ( m_nForward == m_nCurLength   ) {
		if ( m_inFile.eof() == true  ) {
			return EOF ;
		}
		if ( m_nCurLine == 0  ) {
			m_nCurLine = 1 ;
			ReadBuf(m_nCurLine) ;
		}
		else if ( m_nCurLine == 1 ) {
			m_nCurLine = 0 ;
			ReadBuf(m_nCurLine) ;
		}
		m_nForward = 0 ;
	}
	return m_sBuf[m_nCurLine][m_nForward++] ;
}

bool BufferStream::GoBackCh(void)
{
	if ( m_nForward == 0  ) {
		m_nCurLine = (m_nCurLine+1)%2 ;
		m_nForward = strlen(m_sBuf[m_nCurLine]) -1 ;
	}
	else
		m_nForward -- ;
	return true ;
}

string BufferStream::ExtractWord(void)
{
	string newWord ;
	if ( m_nBegin > m_nForward ) {//we assume that words longer than MAX_BUF_LEN is illage !
		int x = (m_nCurLine+1)%2 ;
		size_t tmp = strlen(m_sBuf[x] ) ;
		for ( size_t i = m_nBegin ; i < tmp ; i ++  ) {
			newWord += m_sBuf[x][i]  ;
		}
		for ( size_t i = 0 ; i < m_nForward ; i ++ ) {
			newWord += m_sBuf[m_nCurLine][i]  ;
		}
	}
	else if(m_nBegin < m_nForward )
	{
		for ( size_t i = m_nBegin ; i < m_nForward ; i ++  ) {
			newWord +=  m_sBuf[m_nCurLine][i]   ;
		}
	}
	else
		return string() ;

	char tmp = GetNextChar() ;
	if (  tmp != ' ' && tmp != '\t' ) {
		GoBackCh() ;//去除接下来的空格！
	}
	
	m_nBegin = m_nForward ;
	return newWord ;
}

bool BufferStream::ReadBuf( int line )
{
	if ( line !=  0 && line != 1  ) {
		throw "read buf error ,error argument !" ;
		return false ;
	}

	//m_inFile.read( m_sBuf[0] ,MAX_BUF_LINE ) ;
	m_inFile.read( m_sBuf[line] ,MAX_BUF_LINE ) ;
	int tmp = m_inFile.gcount() ;
	m_sBuf[m_nCurLine][tmp] = '\0' ;
	m_nCurLength = strlen( m_sBuf[line] ) ;
	return true  ;
}

bool BufferStream::LoadFile(string file)
{
	if ( file != "" ) {
		m_strFile = file ;
		m_inFile.open(m_strFile.c_str(),ios::in);
		if (!m_inFile) {//if orror,then exit
			throw "file open error in bufferstream !" ;
		} 
		 
		//m_inFile.seekg(ios::beg) ;
		ReadBuf( 0 ) ; 
		return true ;
	}
	return false ;
}

bool BufferStream::ClearBf(void)
{
	if ( m_inFile ) {
		m_nCurLine = 0 ;
		m_nBegin = 0 ;
		m_nForward = 0 ;
		m_inFile.seekg(ios::beg) ;
		ReadBuf(0) ;
		return true  ;
	}
	return false ;
}
