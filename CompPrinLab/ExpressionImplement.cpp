#include "stdafx.h"
#include "LogicalANDExpression.h"
#include "DeclarationHeaders.h"

LogicalANDExpression::LogicalANDExpression( ) {
	name = "logical-AND-expression" ;
	pLoglANDExpn = NULL ;
	pLoglORExpn = NULL ;
}
LogicalANDExpression::~LogicalANDExpression() {
	SAFE_DELETE( pLoglORExpn) ;
	SAFE_DELETE(pLoglANDExpn) ;
}