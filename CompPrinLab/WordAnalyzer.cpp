#include "StdAfx.h"
#include "WordAnalyzer.h"
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

inline void MyTrim(char * str) 
{
	int len = strlen(str) ;
	for ( int i = len-1 ; i >= 0 ; i --  ) {
		if ( str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ) {
			str[i] = '\0' ;
		}
		else
			return ;
	}
	return ; 
}

WordAnalyzer::WordAnalyzer(string code  )
:m_strSourceCode(code)
,m_nResult(true)
{
	bfs.LoadFile( GetPureCodeFile() ) ;
}

WordAnalyzer::~WordAnalyzer(void)
{
}

/*FUNCTION: find the comment line of a .cpp file and output the
//            the Code line in a .txt file
//NAME :GetCode
//author : hw_henry2008  吴海文
//E-mail : hw_henry2008@126.com
//version : 0.0.1*/
bool WordAnalyzer::RetrivalCode(void)
{
	char line[MAX_LINE];//store each line
	ifstream cfile(m_strSourceCode.c_str(),ios::in);
	if (!cfile) {//if orror,then exit
		 (*outer) <<"Sorry ! "<<m_strSourceCode<<"  open error !"<<myendl;
		return false;
	}
	ofstream resfile(GetPureCodeFile().c_str(), ios::out);
	if (!resfile) {//if open error ,exit
		 (*outer) <<"Sorry ! cannot open the txt file !";
		return false;
	}
	bool isCommenting = false ;
	size_t curSub = 0 ;
	int isBlacking = false ;
	int isString = 0 ;
	while (cfile.getline(line, MAX_LINE , '\n')) 
	{//loop ,read a line in the .cpp file
		MyTrim(line) ;
		size_t strLength = strlen(line) ;
		curSub = 0 ;
		if ( isCommenting == false  ) {
continuing:	for (  ; curSub < strLength ; curSub ++  ) {
				if (!(line[curSub-1] == '\'' && line[curSub+1] == '\'') && line[curSub] == '"' ) {
					isString = (isString+1)%2 ;
				}
				if ( line[curSub] == '/' && line[curSub+1] == '/' && isString == 0) {
					curSub = 0 ;
					break ;
				}
				else if ( line[curSub] == '/' && line[curSub+1] == '*' && isString == 0 ) {
					isCommenting = true ;
					curSub = curSub + 2 ;
					break ;
				}
				else {
					if ( line[curSub] != ' ' && line[curSub] != '\t' ) {
						isBlacking = false ;
						resfile << line[curSub] ;
					}
					else {
						if ( isBlacking == false  ) {
							resfile << ' ' ;
							isBlacking = true ;
						}
					}
				}
			}
		}

		if ( isCommenting == true  ) {
			for ( ; curSub < strLength ; curSub ++  ) {
				if ( curSub == strLength -1 ) {
					cfile.getline(line, MAX_LINE , '\n');
					MyTrim(line) ;
					resfile << '\n' ;
					
					strLength = strlen(line) ;
					curSub = 0 ;
				}
				if ( line[curSub] == '*'  && line[curSub+1] == '/' ) {
					curSub = curSub + 2 ;
					isCommenting = false  ;
					goto continuing ;
				}
			}
		}
		resfile << '\n' ;
	}
	resfile.close();//close the file
	cfile.close();
	return true;
}

string WordAnalyzer::GetPureCodeFile(void)
{
	string temp(".\\Word Analyze\\Pure_Code_") ;
	temp += m_strSourceCode.substr( m_strSourceCode.find_last_of('\\') + 1 ) ;
	return temp ;
}

string WordAnalyzer::GetTokenFile(void)
{
	string temp(".\\Shared\\Token_") ;
	temp += m_strSourceCode.substr( m_strSourceCode.find_last_of('\\') + 1 ) ;
	return temp ;
}

int WordAnalyzer::LaunchAnalyze(void)
{
	m_curLine = 1 ;
	m_TokenFile.open( GetTokenFile().c_str() , ios::out ) ;
	/*if ( !m_TokenFile ) {
		throw "sorry ,open the token file error !" ;
		return -1;
	}*/
	bfs.ClearBf() ;

	while ( bfs.isEOF() == false )
	{
		bfs.ExtractWord() ;
		m_newCh	= bfs.GetNextChar() ;
		if ( m_newCh == ' ' ) {
			;
		}
		else if ( m_newCh == '\n' ) {
			EndLine() ;
		}
		else {
			if ( CheckIDF() == true ) {
				;//do nothing 
			}
			else if ( CheckDigit() == true ) {
				;//do nothing 
			}
			else if ( CheckOpSp() == true ) {
				;//do nothing 
			}
			else if ( CheckSpecial() == true  ) {
				;//do nothing 
			}
			else {
				ReportError( E_INVALID_CHAR  ) ;
			}
		}
	}
	WriteEndSign() ;
	m_TokenFile.close() ;
	return 0;
}

bool WordAnalyzer::CheckOpSp( )
{
	char forsee = bfs.GetNextChar() ;
	string tmp ;
	tmp += m_newCh ;
	tmp += forsee ;
	if ( stb.GetOpSpID(tmp) != -1 ) {
		WriteToken(stb.GetOpSpID(tmp) , tmp ) ;
		bfs.ExtractWord() ;
		return true ;
	}
	bfs.GoBackCh() ;
	tmp.clear() ;
	tmp += m_newCh ;
	if ( stb.GetOpSpID(tmp) != -1 ) {
		WriteToken( stb.GetOpSpID(tmp) , tmp ) ;
		bfs.ExtractWord() ;
		return true ;
	}
	
	return false;
}

bool WordAnalyzer::CheckSpecial( )
{
	switch (m_newCh)
	{
	case '"'://字符串
		while( bfs.isEOF() != true ){
			m_newCh = bfs.GetNextChar() ;
			if ( m_newCh == '"' ) {
				WriteToken( CST_STR ,  bfs.ExtractWord() ) ;
				return true ;//return 
			}
			else if ( m_newCh == '\n' ) {
				EndLine() ;
				ReportError(E_NO_STR_END )  ;
				return true ;
			}
		}
		ReportError(E_FILE_END  );
		break ;
	case '\''://字符
		{//'afa
			char tmp1,tmp2 , tmp3 ;
			tmp1 = bfs.GetNextChar() ;
			if ( tmp1 == '\\' ) {//处理转义字符！
				tmp2 = bfs.GetNextChar() ; tmp3 = bfs.GetNextChar() ;
				if ( tmp2=='n'||tmp2=='t'||tmp2=='v'||tmp2=='\''||tmp2=='r'||tmp2=='\\'||tmp2=='0') {
					if ( tmp3 == '\'' ) {
						WriteToken(CST_CHAR_ES , bfs.ExtractWord() ) ;
					}
					else{
						bfs.GoBackCh() ; bfs.GoBackCh() ; 
						ReportError(E_NO_CHAR_END ) ;
					}
				}
				else{
					if ( tmp2 == '\'' ) {
						ReportError(E_NO_CHAR_END ) ;
					}
					else if ( tmp3 == '\'' ) {
						ReportWarning(E_INVALID_ESC  ) ;
					}
					else{
						bfs.GoBackCh() ; bfs.GoBackCh() ; 
						ReportError(E_NO_CHAR_END   ) ;
					}
				}
			}
			else if (tmp1 != EOF ) {
				tmp2 = bfs.GetNextChar() ;
				if ( tmp2 == '\'' ) {
					/*if ( tmp1 == ' ' ) {
						tmp1 = 8;
					}*/
					WriteToken(CST_CHAR , string()+=tmp1 ) ;
				}
				else{
					bfs.GoBackCh() ;bfs.GoBackCh() ;
					ReportError(E_NO_CHAR_END ) ;
				}
			}
			else {
				ReportError(E_FILE_END );
			}
		}
		break ;
	default:
		return false ;//not a sperator !
	}
	bfs.ExtractWord() ;
	return true ;
}

bool WordAnalyzer::CheckDigit(void)
{
	char tmp = bfs.GetNextChar() ;
	bfs.GoBackCh() ;
	int type = 10 ;
	if ( isdigit(m_newCh) ) {
		if ( m_newCh !='0' || (m_newCh=='0'&& !isdigit(tmp) ) ) {
			bfs.GoBackCh() ;
			type = 10 ;
		}
		else if ( m_newCh == '0' && isdigit(tmp) ) {
			type = 8 ;
		}
		else if ( m_newCh == '0' && (tmp== 'X' || tmp == 'x') ) {
			type = 16 ;
		}

		do  {//得到真正的数字
			m_newCh = bfs.GetNextChar() ;
			if ( isdigit(m_newCh)  == false   ) {
				bfs.GoBackCh() ;
				string word = bfs.ExtractWord() ;
				//int dig = atoi( word.c_str() ) ;
				if ( type == 10 )
					WriteToken(CST_DIGIT_10,word) ;
				else if ( type == 8 )
					WriteToken(CST_DIGIT_8,word) ;
				else if ( type == 16 )
					WriteToken(CST_DIGIT_16,word) ;
				else
					throw "CheckDigit() 遇到意外的错误！" ;

				if ( isalpha(m_newCh)  ) {
					ReportError(E_DIGIT_CHAR) ;
				}
				return true ;
			}
		} while ( bfs.isEOF()== false  );
	}
	else
		return false ;
	return true ;
}

bool WordAnalyzer::CheckIDF(void)
{
	if ( isalpha(m_newCh) || m_newCh == '_'  ) {
		do
		{
			m_newCh = bfs.GetNextChar() ;
			if ( isalpha(m_newCh) == false  && isdigit(m_newCh)  == false && m_newCh != '_' ) {
				bfs.GoBackCh() ;
				string newword = bfs.ExtractWord() ;
				if ( stb.IsKeyWord( newword )  ) {
					WriteToken(  KEY_WORD , newword ) ;
				}
				else{
					//stb.InsertIDTF( newword ,m_curLine ) ;
					WriteToken( VARIABLE , newword ) ;
				}
				return true ;
			}
		}while ( bfs.isEOF() == false ) ;
	}
	else
		return false;
	return true ;
}

bool WordAnalyzer::EndLine(void)
{
	if ( m_TokenFile ) {
		char tmp[32] ;
		_itoa_s( m_curLine , tmp , 10 ) ;
		WriteToken(  NEW_LINE , string(tmp)  ) ;
	}
	m_curLine++ ;
	return true;
}

void WordAnalyzer::ReportError(int kind , const string detail )
{
	 (*outer)  << "error "<<kind<<" at line "<<m_curLine <<": "<<detail<<myendl ;
	m_nResult = false ;
}

void WordAnalyzer::ReportWarning(int kind, const string detail)
{
	 (*outer)  << "warning"<<kind<<" at line "<<m_curLine <<": "<<detail<<myendl ;
}

