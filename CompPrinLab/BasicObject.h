#pragma once
#include <string>

enum TYPE_ENUM{ KULV_VOID , KULV_CHAR , KULV_SHORT , 
			KULV_INT,KULV_SIGNED ,KULV_LONG, KULV_FLOAT ,
			KULV_DOUBLE
			, KULV_ARRAY ,KULV_STRING ,KULV_FUNCTION };

#define  SAFE_DELETE(x) if ( x != NULL ) { \
		delete x ;					\
		x = NULL ;					\
	}
 
class BasicObject
{
public:
	BasicObject(void);
	virtual ~BasicObject(void);
public:
	string name ;
	int subProduction ;
};


