#pragma once
#include <string>
#include <fstream>

using namespace std;

//
//__CLRCALL_OR_CDECL myendl(basic_ostream<_Elem, _Traits>& _Ostr)
//{	// insert newline and flush stream
//	_Ostr.put(_Ostr.widen('\n'));
//	_Ostr.flush();
//	return (_Ostr);
//}
void myendl(void ) ;
//this class is just used to print the information for convenince !

class InforPrinter
{
public:
	InforPrinter & operator << (const string &args ) ; 
	InforPrinter & operator << (const  char * args ) ; 
	InforPrinter & operator << (const  int args ) ;
	InforPrinter & operator << ( void (p)(void) ) ;

public :
	static InforPrinter * MyCreateInstance( ) ;
	~InforPrinter(void);
private:
	InforPrinter( );
	static bool m_bIsOut ;
	static InforPrinter * _ONE_ ;
	ofstream outfile ;
public:
	// 是否输出信息，参数true就输出
	static void SetPrintState(bool isout);
};
