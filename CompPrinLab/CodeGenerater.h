#pragma once
#include <fstream>
#include <string>

class CodeGenerater
{
public:
	CodeGenerater(void);
	~CodeGenerater(void);
	ofstream codefile ;
	bool m_offState ;
	// 注意，后面为了方便，加了个回车键
	int Gen(string strline );
	int SetMildCodeFile(string path);
	void SetOffState( bool isoff ) ;
};
