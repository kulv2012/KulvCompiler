#pragma once
#include "SmallClass.h"
#include <hash_map>
#include <string>
#include "Semantic_Item.h"
#include "SymbolTable.h"
#include "CodeGenerater.h"
#include <stack>

#define  DECLARE_REDUCE_FUNCTIONS(classname)  void Reduce_Function_##classname(void) ;
////////////////////--Kulv--2010/12/26---23:30:50--///////////////////////
#define	 CALL_REDUCE_FUNCTIONS(classname) Reduce_Function_##classname( ) ;
////////////////////--Kulv--2010/12/26---23:30:53--///////////////////////
#define BEGIN_IMPLEMENT_REDUCE_FUNCTIONS(classname)	void \
				classname::Reduce_Function_##classname(void)	 \
			{				
////////////////////--Kulv--2010/12/26---23:14:27--///////////////////////

#define ADD_PRODUCTIONS(noneterminal ,function) \
		m_reduceFuncs[noneterminal] =  function ;	  	

////////////////////--Kulv--2010/12/26---23:14:31--///////////////////////

#define END_IMPLEMENT_REDUCE_FUNCTIONS(classname)  return  ;		\
				}
////////////////////--Kulv--2010/12/26---23:21:04--///////////////////////
class GrammerAnalyzer ;
class SemanticAnalyzer
{
public:
	typedef int (SemanticAnalyzer::*func)( int ) ;
	DECLARE_REDUCE_FUNCTIONS(SemanticAnalyzer) 

	SemanticAnalyzer(void);
	~SemanticAnalyzer(void);
	int Reduce( const ActionRes &actres );
	int MoveIn(const string & terminal);
	int SaveGlobalIdentify() ;
	int SaveFunctionIdentify(string funcname) ;
private:
	GrammerAnalyzer * m_pGrammer ;
	SymbolTable *m_pCurSymbolTable ;
	list< Semantic_Item > m_Semantic_stack ;
	Semantic_Item newSematitem ;
	hash_map< string , func > m_reduceFuncs ;
	CodeGenerater codGen ;
public:
	////////////////////--Kulv--2010/12/27---20:59:07--///////////////////////
	int type_specifier(  int    ) ;
	int declaration_specifiers(int   ) ;
	int init_declarator ( int  ) ;
	int init_declarator_list(int  );
	int declarator(int) ;
	int direct_declarator(int ) ;
	int declaration( int ) ;
	int function_definition( int ) ;
	int compound_statement(int ) ;
	int parameter_type_list ( int  ) ;
	int parameter_list(int);
	int parameter_declaration(int ) ;
	int declaration_list( int ) ;
	int statement_list( int ) ;
	int statement ( int) ;
	int expression_statement(int ) ;
	int expression( int ) ;
	int assignment_expression(int ) ;
	int assignment_operator( int ) ;
	int unary_expression ( int ) ;
	int cast_expression(int ) ;
	int postfix_expression(int ) ;
	int primary_expression(int) ;
	int constant(int) ;
	int conditional_expression( int ) ;
	int logical_OR_expression( int ) ;
	int logical_AND_expression( int ) ;
	int inclusive_OR_expression( int ) ;
	int exclusive_OR_expression(int ) ;
	int AND_expression( int ) ;
	int equality_expression( int ) ;
	int relational_expression(int ) ;
	int shift_expression( int ) ;
	int additive_expression( int ) ;
	int multiplicative_expression( int ) ;
	////////////////////--Kulv--2010/12/27---20:59:10--///////////////////////
	void SetGrammerAnalyzer(GrammerAnalyzer * grammer);
	IdentifyInfo * GetNearIdentify(string id ) ;
	
	int LaunchError( const string msg);
	int LaunchWarning( const string msg);
	bool CheckOnlyOne(string id ) ;

};
 