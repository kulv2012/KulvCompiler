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
	// ע�⣬����Ϊ�˷��㣬���˸��س���
	int Gen(string strline );
	int SetMildCodeFile(string path);
	void SetOffState( bool isoff ) ;
};
