#pragma once 
#include "BasicObject.h"
#include "EqualityExpression.h"

class ANDExpression : public BasicObject
{
public:
	ANDExpression( ) {
		name = "" ;
		pEqltExpn = NULL ;
		pANDExpn = NULL ;
	}
	virtual ~ANDExpression () {
		SAFE_DELETE(pANDExpn) ;
		SAFE_DELETE(pEqltExpn) ;
	}
	string tmpentry ;
	EqualityExpression *pEqltExpn ;
	ANDExpression *pANDExpn ;
protected:
private:
};

/*

AND-expression:
equality-expression 
AND-expression & equality-expression  

*/