#pragma once

#include "BasicObject.h" 

class StorageClassSpecifier : public BasicObject
{
public:
	StorageClassSpecifier(){
		name = "storage-class-specifier" ;
	}
	string value ;// 
	/*auto
	register 
	static 
	extern 
	typedef */
protected:
private:
};