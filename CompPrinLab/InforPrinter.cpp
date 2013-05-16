#include "StdAfx.h"
#include "InforPrinter.h"
#include <iostream>

using namespace std;
void myendl(void ) {
	//empty
}
//initialize the one instance !
InforPrinter * InforPrinter::_ONE_  = NULL ;
bool InforPrinter::m_bIsOut = true  ;
InforPrinter::InforPrinter(  )
{
	outfile.open( INFORMATION_OUT_FILE ,ios::out) ;
	if (!outfile) {//if orror,then exit
		 cout  << "InforPrinter(string file ) open file error !"<<endl ;
		throw "file open error in SaveSymbolTable !" ;
	}
}

InforPrinter::~InforPrinter(void)
{
	outfile.close() ;//close the instance !
}
InforPrinter * InforPrinter::MyCreateInstance( ) 
{
	if ( _ONE_ == NULL ) {
		_ONE_ = new InforPrinter( ) ;
	}//just one inistance !!!!
		return _ONE_ ;
}
////////////////////--Kulv--2010/12/10---16:17:41--///////////////////////
#define INNER_OUT	if( m_bIsOut == true ){\
					outfile << args ; \
					/**/cout  << args ;/**/ \
					}\
					return *this ;
					

InforPrinter & InforPrinter::operator << ( const string &args )
{
	INNER_OUT
}

InforPrinter & InforPrinter::operator << ( const int  args )
{
	INNER_OUT
}

InforPrinter & InforPrinter::operator << (const  char * args )
{
	INNER_OUT
}

InforPrinter & InforPrinter::operator << ( void (p)(void) )
{
	if ( m_bIsOut == true ) {
		endl(outfile) ;
		cout  << endl ;
	}
	
	return *this ;
}
// 是否输出信息，参数true就输出
void InforPrinter::SetPrintState(bool isout)
{
	m_bIsOut = isout ;
}
