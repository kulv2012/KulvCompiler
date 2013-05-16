#pragma once
#include <string>
#include <fstream>
using namespace std;


#define MAX_BUF_LINE 1024


class BufferStream
{
public:
	BufferStream( string str = "");
	~BufferStream(void);
private:
	string m_strFile ;

	ifstream m_inFile ;
	char m_sBuf[2][MAX_BUF_LINE+2] ;
	size_t m_nCurLength ;
	int m_nCurLine ;
	size_t m_nBegin ;
	size_t m_nForward ;
public:
	char GetNextChar(void);
	bool GoBackCh(void);
	string ExtractWord(void);
	bool isEOF(void) {
		if ( m_nForward == m_nCurLength   ) {
			if ( m_inFile.eof() == true  ) {
				return true  ;
			}
		}
		return false ;
	}

private:
	bool ReadBuf(int line);
public:
	bool LoadFile(string file);
	bool ClearBf(void);
};
