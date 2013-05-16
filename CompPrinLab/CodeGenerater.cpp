#include "StdAfx.h"
#include "CodeGenerater.h"
#include <assert.h>
CodeGenerater::CodeGenerater(void)
:m_offState(false)
{
}

CodeGenerater::~CodeGenerater(void)
{
	if ( codefile ) {
		codefile.close() ;
	}
}

// ע�⣬����Ϊ�˷��㣬���˸��س���
int CodeGenerater::Gen(string strline )
{
	if ( m_offState == false ) {
		codefile << strline << endl ;
	}
	return 0;
}

int CodeGenerater::SetMildCodeFile(string path)
{
	codefile.open(path.c_str() , ios::out ) ;
	if ( !codefile ) {
		assert(1!=1) ;
	}
	return 0;
}

void CodeGenerater::SetOffState( bool isoff ) {
	m_offState = isoff ;
	return ;
}