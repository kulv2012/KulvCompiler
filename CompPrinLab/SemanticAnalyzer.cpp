#include "StdAfx.h"
#include "SemanticAnalyzer.h"
#include "GrammerAnalyzer.h"
#include <iostream>
#include <assert.h>
#include "DeclarationHeaders.h"
#include "InforPrinter.h"


extern InforPrinter *outer ;
SemanticAnalyzer::SemanticAnalyzer(void)
{
	//init the symbol table , attention ,this is the global space !
	codGen.SetMildCodeFile(SEMANTIC_RES_MILDCODE_FILE) ;
	m_pCurSymbolTable = new SymbolTable() ;
	CALL_REDUCE_FUNCTIONS(SemanticAnalyzer) ;

	ofstream out(SEMANTIC_RES_IDENTIFY_FILE,ios::out) ;
	out.close() ;//clear it !
}

SemanticAnalyzer::~SemanticAnalyzer(void)
{
	SaveGlobalIdentify();//save the global !
	Semantic_Item semitem ;
	while ( ! m_Semantic_stack.empty() ) {
		semitem = m_Semantic_stack.back() ;
		m_Semantic_stack.pop_back() ;
		SAFE_DELETE(semitem.pNoneterm) ;
	}
}
int SemanticAnalyzer::LaunchError(  const string msg)
{
	(*outer) << "ERROR !Line:"<<m_pGrammer->token.GetCurLine()<<" "<<msg<<myendl ;
	m_pGrammer->m_nErrorCount ++ ;
	codGen.SetOffState(false) ;//if error ,close the code generator !
	return 0;
}
int SemanticAnalyzer::LaunchWarning(  const string msg)
{
	(*outer)<<"Warning !Line:"<<m_pGrammer->token.GetCurLine()<<" "<<msg<<myendl ;
	m_pGrammer->m_nWarningCount++ ;
	return 0;
}


bool SemanticAnalyzer::CheckOnlyOne(string id ){
	if ( m_pCurSymbolTable->m_hmIdentfy.count(id)>0 ) {
		LaunchError(id+" Redefinition!") ;
		return false ;
	}//over write it !
	return true ;
}
void SemanticAnalyzer::SetGrammerAnalyzer(GrammerAnalyzer * grammer)
{
	assert(grammer != NULL ) ;
	m_pGrammer = grammer ;
}

int SemanticAnalyzer::SaveFunctionIdentify(string funcname) {
	ofstream out(SEMANTIC_RES_IDENTIFY_FILE,ios::app) ;
	SymbolTable * tmp = m_pCurSymbolTable ;
	if ( tmp->innerSymbolTable == NULL&&tmp->outerSymbolTable==NULL ) {
		return 0;
	}
	if ( tmp->outerSymbolTable == NULL ) {
		tmp = tmp->innerSymbolTable ;//into the function 
		tmp->outerSymbolTable->innerSymbolTable = NULL ;
	}
	out<<"\n"<<funcname<<" :"<<endl ;
	while ( tmp  != NULL ) {
		hash_map< std::string , IdentifyInfo >::iterator it = tmp->m_hmIdentfy.begin() ;
		while ( it!= tmp->m_hmIdentfy.end() ) {
			out << it->first <<"\t" <<it->second.entry <<"\t"<<it->second.width <<endl ;
			it ++ ;
		}
		SymbolTable *dead = tmp ;
		tmp = tmp->innerSymbolTable ;//go to the inner!
		delete dead ;
	}
	out<< endl ;
	out.close(); 
	
	return 0;
}
int SemanticAnalyzer::SaveGlobalIdentify() {
	//assert(m_pCurSymbolTable->innerSymbolTable == NULL ) ;
	//assert(m_pCurSymbolTable->outerSymbolTable == NULL) ;
	ofstream out(SEMANTIC_RES_IDENTIFY_FILE,ios::app) ;
	out<<"\n\nGlobal Variables:"<<endl ;
	hash_map< std::string , IdentifyInfo >::iterator it = m_pCurSymbolTable->m_hmIdentfy.begin() ;
	while ( it!= m_pCurSymbolTable->m_hmIdentfy.end() ) {
		out << it->first <<"\t" <<it->second.entry <<"\t"<<it->second.width <<endl ;
		it ++ ;
	}
	out.close() ;
	return 0;
}
IdentifyInfo * SemanticAnalyzer::GetNearIdentify(string id ) {
	SymbolTable *tmptable = m_pCurSymbolTable ;
	while ( tmptable != NULL  ) {
		if ( tmptable->m_hmIdentfy.count(id)>0 ) {
			return &(tmptable->m_hmIdentfy[id] ) ;
		}
		tmptable = tmptable->outerSymbolTable ;//go out !
	}
	return NULL ;
}
////////////////////--Kulv--2010/12/26---23:15:18--///////////////////////
BEGIN_IMPLEMENT_REDUCE_FUNCTIONS(SemanticAnalyzer)   
ADD_PRODUCTIONS( "type-specifier" , &SemanticAnalyzer::type_specifier )
ADD_PRODUCTIONS( "declaration-specifiers" , &SemanticAnalyzer::declaration_specifiers )
ADD_PRODUCTIONS( "init-declarator-list" , &SemanticAnalyzer::init_declarator_list )
ADD_PRODUCTIONS( "init-declarator" ,&SemanticAnalyzer::init_declarator )
ADD_PRODUCTIONS( "declarator" , &SemanticAnalyzer::declarator )
ADD_PRODUCTIONS( "direct-declarator" , &SemanticAnalyzer::direct_declarator )
ADD_PRODUCTIONS( "declaration" , &SemanticAnalyzer::declaration )
ADD_PRODUCTIONS( "function-definition" , &SemanticAnalyzer::function_definition )
ADD_PRODUCTIONS( "compound-statement" , &SemanticAnalyzer::compound_statement )
ADD_PRODUCTIONS( "parameter-type-list" , &SemanticAnalyzer::parameter_type_list )
ADD_PRODUCTIONS( "parameter-list" , &SemanticAnalyzer::parameter_list )
ADD_PRODUCTIONS( "parameter-declaration" , &SemanticAnalyzer::parameter_declaration )
ADD_PRODUCTIONS( "declaration-list" , &SemanticAnalyzer::declaration_list )
ADD_PRODUCTIONS( "statement-list" , &SemanticAnalyzer::statement_list )
ADD_PRODUCTIONS( "statement" , &SemanticAnalyzer::statement )
ADD_PRODUCTIONS( "expression-statement" , &SemanticAnalyzer::expression_statement )
ADD_PRODUCTIONS( "expression" , &SemanticAnalyzer::expression )
ADD_PRODUCTIONS( "assignment-expression" , &SemanticAnalyzer::assignment_expression )
ADD_PRODUCTIONS( "assignment-operator" , &SemanticAnalyzer::assignment_operator )
ADD_PRODUCTIONS( "unary-expression" , &SemanticAnalyzer::unary_expression )
ADD_PRODUCTIONS( "cast-expression" , &SemanticAnalyzer::cast_expression )
ADD_PRODUCTIONS( "postfix-expression" , &SemanticAnalyzer::postfix_expression )
ADD_PRODUCTIONS( "primary-expression" , &SemanticAnalyzer::primary_expression )
ADD_PRODUCTIONS( "constant" , &SemanticAnalyzer::constant )
ADD_PRODUCTIONS( "conditional-expression" , &SemanticAnalyzer::conditional_expression )
ADD_PRODUCTIONS( "logical-OR-expression" , &SemanticAnalyzer::logical_OR_expression )
ADD_PRODUCTIONS( "logical-AND-expression" , &SemanticAnalyzer::logical_AND_expression )
ADD_PRODUCTIONS( "inclusive-OR-expression" , &SemanticAnalyzer::inclusive_OR_expression )
ADD_PRODUCTIONS( "exclusive-OR-expression" , &SemanticAnalyzer::exclusive_OR_expression )
ADD_PRODUCTIONS( "AND-expression" , &SemanticAnalyzer::AND_expression  )
ADD_PRODUCTIONS( "equality-expression" , &SemanticAnalyzer::equality_expression )
ADD_PRODUCTIONS( "relational-expression" , &SemanticAnalyzer::relational_expression  )
ADD_PRODUCTIONS( "shift-expression" , &SemanticAnalyzer::shift_expression  )
ADD_PRODUCTIONS( "additive-expression" , &SemanticAnalyzer::additive_expression  )
ADD_PRODUCTIONS( "multiplicative-expression" , &SemanticAnalyzer::multiplicative_expression  )
END_IMPLEMENT_REDUCE_FUNCTIONS(SemanticAnalyzer) 
////////////////////--Kulv--2010/12/26---23:15:21--///////////////////////

////////////////////--Kulv--2010/12/27---20:58:00--///////////////////////
int SemanticAnalyzer::Reduce( const ActionRes &actres )
{
	//m_reduceFuncs["asdf"] = NULL ;//type_specifier_int; ;
	if ( m_reduceFuncs.count( actres.terminal ) > 0) {
		func p ;
		p = m_reduceFuncs[ actres.terminal  ] ;
		//assert( p != NULL ) ;
		if ( p != NULL  ) {
			(this->*p)( actres.subid ) ;
		}
	}
	return 0;
}


int SemanticAnalyzer::MoveIn(const string & terminal)
{
	if ( terminal == "{" ) {
		if ( m_pGrammer->token.GetLastToken()->origrinal == ")" ) {
			//if it is a function definishion ,means alreay new it
			return 0 ;
		}
		//new a symbol table !
		cout << "\tnew a symbol table !" << endl ;
		SymbolTable * newSymbolTable = new SymbolTable() ;
		m_pCurSymbolTable->innerSymbolTable = newSymbolTable ;
		newSymbolTable->outerSymbolTable = m_pCurSymbolTable ;
		m_pCurSymbolTable = newSymbolTable ;
	}
	else if ( terminal == "}" ) {//lets delete the inner symbol table 
		cout << "\tdelete a symbol table !" << endl ;
		SymbolTable * inner = m_pCurSymbolTable ;
		m_pCurSymbolTable = m_pCurSymbolTable->outerSymbolTable ;
		//delete inner ; no !!!!
	}
	
	return 0;
}

int  SemanticAnalyzer::type_specifier ( int subproid  ) {
	cout << "\ttype_specifier called :"<<subproid << endl ;
	switch ( subproid )
	{
	case 0 :
		newSematitem.pNoneterm = new TypeSpecifier(KULV_VOID , 0 ,0) ;
		break ;
	case 1 :
		newSematitem.pNoneterm = new TypeSpecifier(KULV_CHAR , 1 , 1) ;
		break ;
	case 2 :
		newSematitem.pNoneterm = new  TypeSpecifier(KULV_SHORT , 2 ,2) ;
		break ;
	case 3 :
		newSematitem.pNoneterm = new TypeSpecifier(KULV_INT , 4 ,3) ;
		break ;
	case 4 :
		newSematitem.pNoneterm = new TypeSpecifier (KULV_LONG , 8 ,4) ;
		break ;
	case 5 :
		newSematitem.pNoneterm = new TypeSpecifier (KULV_FLOAT , 4 ,5) ;
		break ;
	case 6 :
		newSematitem.pNoneterm = new TypeSpecifier (KULV_DOUBLE ,8 ,6) ;
		break ;
	case 7 :
		newSematitem.pNoneterm = new TypeSpecifier (KULV_SIGNED , 4 ,7 ) ;
		break ;
	default:
		assert ( 1 != 1) ;
		break ;
	}
	m_Semantic_stack.push_back( newSematitem ) ;
	return 0 ;
}

int SemanticAnalyzer::declaration_specifiers(int subproid ){
	cout<< "\tdeclaration_specifiers called :"<< subproid<< endl  ;
	
	DeclarationSpecifiers *declspfier = new DeclarationSpecifiers() ;
	switch (subproid )
	{
		case 2:
			assert ( m_Semantic_stack.back().pNoneterm->name == "type-specifier" ) ;
			declspfier->pTypeSpfr = (TypeSpecifier*)(m_Semantic_stack.back().pNoneterm) ;
			newSematitem.pNoneterm = declspfier ;
			m_Semantic_stack.pop_back() ;
			break ;
		default:
			assert ( 1 != 1) ;
			break ;
	}
	declspfier->subProduction = subproid ;
	m_Semantic_stack.push_back( newSematitem ) ;
	return 0 ;
}
int SemanticAnalyzer::init_declarator_list(int subproid)
{
	cout << "\tinit_declarator_list called :" << subproid << endl ;
	assert ( m_Semantic_stack.back().pNoneterm->name == "init-declarator" ) ;
	InitDeclaratorList *pinitdecllist = new InitDeclaratorList() ;
	switch (subproid)
	{
		case 0 :
			pinitdecllist->pInitDecl = (InitDeclarator *)(m_Semantic_stack.back().pNoneterm ) ;
			m_Semantic_stack.pop_back() ;
			break ;
		case 1:
			pinitdecllist->pInitDecl = (InitDeclarator *)(m_Semantic_stack.back().pNoneterm);
			m_Semantic_stack.pop_back() ;
			pinitdecllist->pInitDeclList = (InitDeclaratorList*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			break ;
		default:
			assert ( 1 != 1) ;
			break ;
	}
	pinitdecllist->subProduction = subproid ;
	newSematitem.pNoneterm = pinitdecllist ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}



int SemanticAnalyzer::init_declarator ( int subproid ) {
	cout << "\tinit_declarator called :" << subproid << endl ;
	InitDeclarator *pinitdecl = new InitDeclarator  ;
	switch (subproid)
	{
	case 0 :
		assert ( m_Semantic_stack.back().pNoneterm->name == "declarator") ;
		pinitdecl->pDecl = (Declarator*)(m_Semantic_stack.back().pNoneterm) ;
		m_Semantic_stack.pop_back() ;
		break ;
	case 1:
		assert ( m_Semantic_stack.back().pNoneterm->name == "declarator") ;
		pinitdecl->pDecl = (Declarator*)(m_Semantic_stack.back().pNoneterm) ;
		m_Semantic_stack.pop_back() ;
		//assert(1 != 1) ;
		break ;
	default:
		assert ( 1 != 1) ;
		break ;
	}
	pinitdecl->subProduction = subproid ;
	newSematitem.pNoneterm =  pinitdecl ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}

int SemanticAnalyzer::declarator ( int subproid ) {
	cout << "\tdeclarator called :" << subproid << endl ;
	Declarator *pdecl  = new Declarator ;
	switch (subproid)
	{
	case 0 :
		assert(m_Semantic_stack.back().pNoneterm->name == "direct-declarator" ) ;
		pdecl->pDirtDecl = (DirectDeclarator*)m_Semantic_stack.back().pNoneterm ;
		m_Semantic_stack.pop_back() ;
		break ;
	default:
		assert ( 1 != 1) ;
		break ;
	}
	pdecl->subProduction = subproid ;
	newSematitem.pNoneterm =  pdecl ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}

int SemanticAnalyzer::direct_declarator ( int subproid ) {
	cout << "\tdirect_declarator called :" << subproid << endl ;
	DirectDeclarator *pnewnontm = new DirectDeclarator;
	switch (subproid)
	{
	case 0 ://identifier   
		{
			string identify = m_pGrammer->token.GetLastToken()->origrinal ;
			CheckOnlyOne(identify) ;
			/*IdentifyInfo idnty ;
			m_pCurSymbolTable->m_hmIdentfy[identify] = idnty ;*/
			pnewnontm->identify = identify ;
		}
		break ;
	case 4://direct-declarator ( parameter-type-list ) 
		{//no need to new a symbole! already newed in parameter-type-list
			assert(m_Semantic_stack.back().pNoneterm->name == "parameter-type-list" );
			pnewnontm->pParmTypeList = (ParameterTypeList*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			pnewnontm->pDirtDecl =(DirectDeclarator*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			codGen.Gen(pnewnontm->pDirtDecl->identify+" :") ;
		}
		break ;
	case 5:// direct-declarator ( ) 
		//new a symbol table !!!
		{
			assert(m_Semantic_stack.back().pNoneterm->name == "direct-declarator" );
			SymbolTable * newSymbolTable = new SymbolTable() ;
			m_pCurSymbolTable->innerSymbolTable = newSymbolTable ;
			newSymbolTable->outerSymbolTable = m_pCurSymbolTable ;
			m_pCurSymbolTable = newSymbolTable ;
			////////////////////--Kulv--2010/12/29---20:50:01--///////////////////////
			pnewnontm->pDirtDecl = (DirectDeclarator*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			codGen.Gen(pnewnontm->pDirtDecl->identify+" :") ;
		}
		break ;
	default:
		assert ( 1 != 1) ;
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm =  pnewnontm ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}


int SemanticAnalyzer::declaration( int subproid ) {
	cout << "\tdeclaration called :" << subproid << endl ;
	Declaration * pnewnontm = new Declaration ;
	switch (subproid)
	{
	case 0 ://if just a type !
		LaunchWarning( " missing identify ?" ) ;
		assert( m_Semantic_stack.back().pNoneterm->name == "declaration-specifiers") ;
		SAFE_DELETE(m_Semantic_stack.back().pNoneterm );
		pnewnontm->pDeclSpfr = NULL ;
		m_Semantic_stack.pop_back() ;
		break ;
	case 1 ://declaration-specifiers init-declarator-list ;
		////////////////////--Kulv--2010/12/29---16:59:48--///////////////////////
		{
			assert( m_Semantic_stack.back().pNoneterm->name == "init-declarator-list") ;
			InitDeclaratorList *pinitdecllist = 
				(InitDeclaratorList *)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			DeclarationSpecifiers *pdeclspfr = 
				(DeclarationSpecifiers *)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			//get the identifys !!!
			while ( NULL != pinitdecllist ) {
				string identy = pinitdecllist->pInitDecl->pDecl->pDirtDecl->identify;
				//fill !!!!
				IdentifyInfo *idinfo = &(m_pCurSymbolTable->m_hmIdentfy[identy]) ;
				idinfo->entry = idinfo->ENTRY ;
				idinfo->ENTRY += pdeclspfr->pTypeSpfr->width ;
				idinfo->width = pdeclspfr->pTypeSpfr->width ;
				idinfo->pType = pdeclspfr->GetTypeSpecifiers() ;
				//left!
				pinitdecllist = pinitdecllist->pInitDeclList ;
			}
		}
		break ;
		////////////////////--Kulv--2010/12/29---16:59:51--///////////////////////
	default:
		assert ( 1 != 1) ;
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}

int SemanticAnalyzer::function_definition ( int subproid ) {
	cout << "\tfunction_definition called :" << subproid << endl ;
	FunctionDefinition * pnewnontm = new FunctionDefinition;
	switch (subproid)
	{
	case 0 :
		assert( 0 );
		break ;
	case 1 :
		assert( 0 );
		break ;
	case 2 :
		{//declaration-specifiers declarator compound-statement 
			assert( m_Semantic_stack.back().pNoneterm->name=="compound-statement" ) ;
			CompoundStatement *pCmpdStmt = 
										(CompoundStatement *)(m_Semantic_stack.back().pNoneterm) ;
			assert(pCmpdStmt != NULL) ;
			m_Semantic_stack.pop_back() ;
			Declarator *pDecltr = (Declarator*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			DeclarationSpecifiers *pDeclSpfr =
										(DeclarationSpecifiers*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			
			string funcName = pDecltr->pDirtDecl->pDirtDecl->identify ;
			IdentifyInfo *idinfo = &(m_pCurSymbolTable->m_hmIdentfy[funcName] ) ;
			if ( idinfo->pType == NULL ) {//if no argruement
				idinfo->pType = new FunctionType ;
			}
			((FunctionType*)(idinfo->pType))->pRetnType = pDeclSpfr->pTypeSpfr ;
			SaveFunctionIdentify( pDecltr->pDirtDecl->pDirtDecl->identify) ;
		}
		break ;
	default:
		assert(0) ;
		break ;
	}
	codGen.Gen("\treturn") ;
	//DONT forget to reload the identify last entry 
	IdentifyInfo::ENTRY = m_pCurSymbolTable->lastEntry ;
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}

int SemanticAnalyzer::compound_statement ( int subproid ) {
	cout << "\tcompound_statement called :" << subproid << endl ;
	CompoundStatement *pnewnontm = new CompoundStatement;
	switch (subproid)
	{
	case 0 :
		//do nothing
		break ;
	case 1://{ statement-list } 
		assert(m_Semantic_stack.back().pNoneterm->name == "statement-list" ) ;
		pnewnontm->pStmtList = (StatementList*)(m_Semantic_stack.back().pNoneterm) ;
		m_Semantic_stack.pop_back() ;
		//do nothing
	case 2://{ declaration-list } 
		assert(m_Semantic_stack.back().pNoneterm->name == "declaration-list" ) ;
		pnewnontm->pDeclList = (DeclarationList*)(m_Semantic_stack.back().pNoneterm) ;
		m_Semantic_stack.pop_back() ;
		//do nothing !
		break ;
	case 3://{ declaration-list statement-list } 
		assert(m_Semantic_stack.back().pNoneterm->name == "statement-list" ) ;
		pnewnontm->pStmtList = (StatementList*)(m_Semantic_stack.back().pNoneterm) ;
		m_Semantic_stack.pop_back() ;
		assert(m_Semantic_stack.back().pNoneterm->name == "declaration-list" ) ;
		pnewnontm->pDeclList = (DeclarationList*)(m_Semantic_stack.back().pNoneterm) ;
		m_Semantic_stack.pop_back() ;
		//do nothing
		break ;
	default:
		assert(0) ;
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}


int SemanticAnalyzer::parameter_type_list ( int subproid ) {
	cout << "\tparameter_type_list called :" << subproid << endl ;
	ParameterTypeList *pnewnontm = new ParameterTypeList ;
	switch (subproid)
	{
	case 0 ://parameter-list
		assert(m_Semantic_stack.back().pNoneterm->name == "parameter-list") ;
		pnewnontm->pParmList = (ParameterList*)(m_Semantic_stack.back().pNoneterm) ;
		m_Semantic_stack.pop_back() ;
		//the arguement is already add in parameter-list
		break ;
	case 1://parameter-list , ...
		assert(m_Semantic_stack.back().pNoneterm->name == "parameter-list") ;
		assert(0) ;
	default:
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}

int SemanticAnalyzer::parameter_list ( int subproid ) {
	cout << "\tparameter_list called :" << subproid << endl ;
	ParameterList *pnewnontm = new ParameterList ;
	switch (subproid)
	{
	case 0 ://parameter-declaration
		{
//here , we new a symbol table ! just once !
			assert( m_Semantic_stack.back().pNoneterm->name=="parameter-declaration") ;
			ParameterDeclaration* tmpParmDecltr = 
										(ParameterDeclaration*)(m_Semantic_stack.back().pNoneterm) ;
			pnewnontm->pParmDecl = tmpParmDecltr ;
			m_Semantic_stack.pop_back() ;
			assert(m_Semantic_stack.back().pNoneterm->name=="direct-declarator") ;
			string funcName = ((DirectDeclarator*)(m_Semantic_stack.back().pNoneterm))->identify;
			CheckOnlyOne(funcName) ;
			IdentifyInfo funcIdinfo ;
			FunctionType *fy = new FunctionType ;
			funcIdinfo.pType = fy ;
			funcIdinfo.name = funcName ;//the return type will add at function-definition
			fy->entryAddress = funcName;//the address is the label , that is just the name;
			fy->kind = KULV_FUNCTION ;
			m_pCurSymbolTable->m_hmIdentfy[funcName] = funcIdinfo ;
			////////////////////--Kulv--2010/12/30---0:49:41--///////////////////////
			cout << "\tnew a symbol table !" << endl ;
			m_pCurSymbolTable->lastEntry = IdentifyInfo::ENTRY ;//store the last entry !only function
			IdentifyInfo::ENTRY  = 0 ;
			SymbolTable * newSymbolTable = new SymbolTable() ;
			m_pCurSymbolTable->innerSymbolTable = newSymbolTable ;
			newSymbolTable->outerSymbolTable = m_pCurSymbolTable ;
			m_pCurSymbolTable = newSymbolTable ;
			
			////////////////////--Kulv--2010/12/30---1:46:37--///////////////////////
			TypeSpecifier *ptmptypespfr=tmpParmDecltr->pDeclSpfr->GetTypeSpecifiers() ;
			fy->pParamTypeList.push_back(ptmptypespfr) ;
			if ( tmpParmDecltr->subProduction == 0 ) {
				//do nothing
			}
			else if ( tmpParmDecltr->subProduction == 1 ) {
				IdentifyInfo parminfo ;
				Declarator *ptmpdecltr = tmpParmDecltr->pDecltr ;
				parminfo.name  = tmpParmDecltr->pDecltr->pDirtDecl->identify ;
				CheckOnlyOne(parminfo.name ) ;
				parminfo.entry = IdentifyInfo::ENTRY ;
				IdentifyInfo::ENTRY += ptmptypespfr->width ;
				parminfo.width = ptmptypespfr->width ;
				parminfo.pType = ptmptypespfr ;//add a parment
				m_pCurSymbolTable->m_hmIdentfy[parminfo.name] = parminfo ;

			}
			else if ( tmpParmDecltr->subProduction == 2 ) {
				assert(0) ;
			}
			else assert(0) ;
			
			////////////////////--Kulv--2010/12/30---1:46:40--///////////////////////
		}
		
		break ;
	case 1://parameter-list , parameter-declaration 
		{
			ParameterDeclaration* tmpParmDecltr = 
									(ParameterDeclaration*)(m_Semantic_stack.back().pNoneterm) ;
			pnewnontm->pParmDecl = tmpParmDecltr;
			m_Semantic_stack.pop_back() ;
			pnewnontm->pParmList = (ParameterList *)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			////////////////////--Kulv--2010/12/30---2:22:32--///////////////////////
			TypeSpecifier *ptmptypespfr=tmpParmDecltr->pDeclSpfr->GetTypeSpecifiers() ;
			if ( tmpParmDecltr->subProduction == 0 ) {
				//do nothing
			}
			else if ( tmpParmDecltr->subProduction == 1 ) {
				IdentifyInfo parminfo ;
				Declarator *ptmpdecltr = tmpParmDecltr->pDecltr ;
				parminfo.name  = tmpParmDecltr->pDecltr->pDirtDecl->identify ;
				CheckOnlyOne(parminfo.name ) ;
				parminfo.entry = IdentifyInfo::ENTRY ;
				IdentifyInfo::ENTRY += ptmptypespfr->width ;
				parminfo.width = ptmptypespfr->width ;
				parminfo.pType = ptmptypespfr ;//add a parment
				m_pCurSymbolTable->m_hmIdentfy[parminfo.name] = parminfo ;

			}
			else if ( tmpParmDecltr->subProduction == 2 ) {
				assert(0) ;
			}
			else assert(0) ;
		}
		
		break ;
	default:
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}


int SemanticAnalyzer::parameter_declaration ( int subproid ) {
	cout << "\tparameter_declaration called :" << subproid << endl ;
	ParameterDeclaration *pnewnontm = new ParameterDeclaration ;
	switch (subproid)
	{
	case 0 ://declaration-specifiers 
		assert(m_Semantic_stack.back().pNoneterm->name == "declaration-specifiers");
		pnewnontm->pDeclSpfr = (DeclarationSpecifiers*)(m_Semantic_stack.back().pNoneterm) ;
		m_Semantic_stack.pop_back() ;
		break ;
	case 1://declaration-specifiers declarator 
		assert(m_Semantic_stack.back().pNoneterm->name == "declarator");
		pnewnontm->pDecltr = (Declarator*)(m_Semantic_stack.back().pNoneterm) ;
		m_Semantic_stack.pop_back() ;
		pnewnontm->pDeclSpfr = (DeclarationSpecifiers*)(m_Semantic_stack.back().pNoneterm) ;
		m_Semantic_stack.pop_back() ;
		break ;
	case 3://declaration-specifiers abstract-declarator 
		assert(m_Semantic_stack.back().pNoneterm->name == "abstract-declarator");
		pnewnontm->pAbstDecl = (AbstractDeclarator*)(m_Semantic_stack.back().pNoneterm) ;
		m_Semantic_stack.pop_back() ;
		pnewnontm->pDeclSpfr = (DeclarationSpecifiers*)(m_Semantic_stack.back().pNoneterm) ;
		m_Semantic_stack.pop_back() ;
		assert(0) ;
		break ;
	default:
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}


int SemanticAnalyzer::declaration_list ( int subproid ) {
	cout << "\tdeclaration_list called :" << subproid << endl ;
	DeclarationList *pnewnontm = new DeclarationList ;
	switch (subproid)
	{
	case 0 ://declaration 
		assert(m_Semantic_stack.back().pNoneterm->name == "declaration") ;
		pnewnontm->pDecl = (Declaration*)(m_Semantic_stack.back().pNoneterm) ;
		m_Semantic_stack.pop_back() ;
		break ;
	case 1://declaration-list declaration 
		assert(m_Semantic_stack.back().pNoneterm->name == "declaration") ;
		pnewnontm->pDecl = (Declaration*)(m_Semantic_stack.back().pNoneterm) ;
		m_Semantic_stack.pop_back() ;
		pnewnontm->pDeclList = (DeclarationList*)(m_Semantic_stack.back().pNoneterm) ;
		break ;
	default:
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}

int SemanticAnalyzer::statement_list ( int subproid ) {
	cout << "\tstatement_list called :" << subproid << endl ;
	StatementList *pnewnontm = new StatementList ;
	switch (subproid)
	{
	case 0 ://statement 
		assert(m_Semantic_stack.back().pNoneterm->name == "statement" ) ;
		pnewnontm->pStmt = (Statement*)(m_Semantic_stack.back().pNoneterm) ;
		m_Semantic_stack.pop_back() ;
		break ;
	case 1://statement-list statement 
		assert(m_Semantic_stack.back().pNoneterm->name == "statement" ) ;
		pnewnontm->pStmt = (Statement*)(m_Semantic_stack.back().pNoneterm) ;
		m_Semantic_stack.pop_back() ;
		pnewnontm->pStmtList = (StatementList*)(m_Semantic_stack.back().pNoneterm) ;
		m_Semantic_stack.pop_back() ;
		break ;
	default:
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}

int SemanticAnalyzer::statement ( int subproid ) {
	cout << "\tstatement called :" << subproid << endl ;
	Statement *pnewnontm = new Statement ;
	//no need to add the statement to tree ;
	BasicObject *dead = m_Semantic_stack.back().pNoneterm ;
	switch (subproid)
	{
	case 0 ://labeled-statement 
		assert( m_Semantic_stack.back().pNoneterm->name == "labeled-statement" ) ;
		m_Semantic_stack.pop_back() ;
		break ;
	case 1 ://expression-statement 
		assert( m_Semantic_stack.back().pNoneterm->name == "expression-statement" ) ;
		m_Semantic_stack.pop_back() ;
		break ;
	case 2 ://compound-statement 
		assert( m_Semantic_stack.back().pNoneterm->name == "compound-statement" ) ;
		m_Semantic_stack.pop_back() ;
		break ;
	case 3 ://selection-statement 
		assert( m_Semantic_stack.back().pNoneterm->name == "selection-statement" ) ;
		m_Semantic_stack.pop_back() ;
		break ;
	case 4 ://iteration-statement
		assert( m_Semantic_stack.back().pNoneterm->name == "iteration-statement" ) ;
		m_Semantic_stack.pop_back() ;
		break ; 
	case 5 ://jump-statement
		assert( m_Semantic_stack.back().pNoneterm->name == "jump-statement" ) ;
		m_Semantic_stack.pop_back() ;
		break ;
	default:
		assert(0) ;
		break ;
	}
	delete dead ;
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}


int SemanticAnalyzer::expression_statement ( int subproid ) {
	cout << "\texpression_statement called :" << subproid << endl ;
	ExpressionStatement *pnewnontm = new ExpressionStatement;
	switch (subproid)
	{
	case 0 : // ; 
		//nothing !
		break ;
	case 1:// expression ; 
		assert( m_Semantic_stack.back().pNoneterm->name == "expression" ) ;
		//just pop it !
		delete m_Semantic_stack.back().pNoneterm ;
		m_Semantic_stack.pop_back() ;
		break ;
	default:
		assert( 0 ) ;
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}

int SemanticAnalyzer::expression ( int subproid ) {
	cout << "\texpression called :" << subproid << endl ;
	Expression *pnewnontm = new Expression ;
	switch (subproid)
	{
	case 0 ://assignment-expression 
		{
			AssignmentExpression *pasgmExpn = (AssignmentExpression*)(m_Semantic_stack.back().pNoneterm) ;
			IdentifyInfo *asexidinfo = GetNearIdentify(pasgmExpn->tmpentry) ;
			assert(asexidinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(asexidinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pasgmExpn->tmpentry) ;
			m_Semantic_stack.pop_back() ;
		}
		
		break ;
	case 1://expression , assignment-expression 
		{
			AssignmentExpression *pasgmExpn = (AssignmentExpression*)(m_Semantic_stack.back().pNoneterm) ;
			IdentifyInfo *asexidinfo = GetNearIdentify(pasgmExpn->tmpentry) ;
			assert(asexidinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(asexidinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pasgmExpn->tmpentry) ;
			m_Semantic_stack.pop_back() ;
			m_Semantic_stack.pop_back() ;
		}
		
		break ;
	default:
		assert( 0 ) ;
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}

int SemanticAnalyzer::assignment_expression ( int subproid ) {
	cout << "\tassignment_expression called :" << subproid << endl ;
	AssignmentExpression *pnewnontm = new AssignmentExpression ;
	switch (subproid)
	{
	case 0 ://conditional-expression 
		{
			ConditionalExpression *pcondexpn = (ConditionalExpression*)(m_Semantic_stack.back().pNoneterm) ;
			IdentifyInfo *asexidinfo = GetNearIdentify(pcondexpn->tmpentry) ;
			assert(asexidinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(asexidinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pcondexpn->tmpentry) ;
			m_Semantic_stack.pop_back() ;
		}
		break ;
	case 1://unary-expression assignment-operator assignment-expression 
		{//忽略了类型检查
			AssignmentExpression *pAsgnExpn=(AssignmentExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ; 
			AssignmentOperator *pAsgnOptr=(AssignmentOperator*)(m_Semantic_stack.back().pNoneterm);
			m_Semantic_stack.pop_back() ;
			UnaryExpression *pUnryExpn=(UnaryExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *asexidinfo = GetNearIdentify(pAsgnExpn->tmpentry) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(asexidinfo->pType) ;
			codGen.Gen(pUnryExpn->tmpentry+" "+pAsgnOptr->optr+" "+pAsgnExpn->tmpentry) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+ pUnryExpn->tmpentry ) ;
		}
		break ;
	default:
		assert(0) ;
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}



int SemanticAnalyzer::assignment_operator ( int subproid ) {
	cout << "\tassignment_operator called :" << subproid << endl ;
	AssignmentOperator *pnewnontm = new AssignmentOperator ;
	pnewnontm->optr =  m_pGrammer->token.GetLastToken()->origrinal ;
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}



int SemanticAnalyzer::unary_expression ( int subproid ) {
	cout << "\tunary_expression called :" << subproid << endl ;
	UnaryExpression *pnewnontm = new UnaryExpression ;
	switch (subproid)
	{
	case 0 ://postfix-expression 
		{
			PostfixExpression *pPofxExpn=(PostfixExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pPofxExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pPofxExpn->tmpentry) ;
		}
		
		break ;
	case 1 ://++ unary-expression 
		{
			UnaryExpression *pUnryExpn=(UnaryExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pUnryExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pUnryExpn->tmpentry+" + "+"1") ;
		}
		m_Semantic_stack.pop_back() ;
		break ;
	case 2 ://-- unary-expression 
		{
			UnaryExpression *pUnryExpn=(UnaryExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pUnryExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pUnryExpn->tmpentry+" - "+"1") ;
		}
		break ;
	case 3 ://unary-operator cast-expression 
		{
			assert( 0 ) ;
			CastExpression *pCastExpn=(CastExpression*)(m_Semantic_stack.back().pNoneterm);
			m_Semantic_stack.pop_back() ;
			UnaryOperator *pUnryOptr=(UnaryOperator*)(m_Semantic_stack.back().pNoneterm);
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo=GetNearIdentify(pCastExpn->tmpentry) ;
			assert(idinfo!=NULL ) ;
			pnewnontm->tmpentry=m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pUnryOptr->optr+" "+pCastExpn->tmpentry) ;
		}
		break ;
	case 4 ://sizeof  unary-expression 
		{
			UnaryExpression *pUnryExpn=(UnaryExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pUnryExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(&Integer) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+"4" ) ;
		}
		break ;
	case 5 ://sizeof  ( type-name ) 
		assert( 0 ) ;
		m_Semantic_stack.pop_back() ;
		break ;
	default:
		assert(0) ;
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}


int SemanticAnalyzer::cast_expression ( int subproid ) {
	cout << "\tcast_expression called :" << subproid << endl ;
	CastExpression *pnewnontm = new CastExpression ;
	switch (subproid)
	{
	case 0 ://unary-expression 
		{
			UnaryExpression *pUnryExpn=(UnaryExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pUnryExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(&Integer) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+ pUnryExpn->tmpentry ) ;
		}
		break ;
	case 1 ://( type-name ) cast-expression  
		assert(0 ) ;
		m_Semantic_stack.pop_back() ;
		break ;
	default:
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}

int SemanticAnalyzer::postfix_expression ( int subproid ) {
	cout << "\tpostfix_expression called :" << subproid << endl ;
	PostfixExpression *pnewnontm = new PostfixExpression;
	switch (subproid)
	{
	case 0 ://primary-expression 
		{
			PrimaryExpression *pPrmyExpn=(PrimaryExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pPrmyExpn->identify) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+ pPrmyExpn->identify ) ;
		}
		break ;
	case 1 ://postfix-expression [ expression ] 
		assert(0 ) ;
		m_Semantic_stack.pop_back() ;
		break ;
	case 2 ://postfix-expression ( ) 
		assert(0 ) ;
		m_Semantic_stack.pop_back() ;
		break ;
	case 3 ://postfix-expression ( argument-expression-list )
		assert( 0) ;
		m_Semantic_stack.pop_back() ;
		break ;
	case 4 ://postfix-expression -> identifier   
		assert(0 ) ;
		m_Semantic_stack.pop_back() ;
		break ;
	case 5 ://postfix-expression ++ 
		assert(0 ) ;
		m_Semantic_stack.pop_back() ;
		break ;
	case 6 ://postfix-expression -- 
		assert(0 ) ;
		m_Semantic_stack.pop_back() ;
		break ;
	default:
		assert(0) ;
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}


int SemanticAnalyzer::primary_expression ( int subproid ) {
	cout << "\tprimary_expression called :" << subproid << endl ;
	PrimaryExpression *pnewnontm = new PrimaryExpression ;
	switch (subproid)
	{
	case 0 ://identifier
		pnewnontm->identify = m_pGrammer->token.GetLastToken()->origrinal ;
		if ( GetNearIdentify(pnewnontm->identify)== NULL  ) {
			LaunchError("Variable "+pnewnontm->identify+" NO DECLARATION !" ) ;
			IdentifyInfo idinfo ;// if no declaration ,then we assume it be void 
			idinfo.entry=IdentifyInfo::ENTRY ;
			idinfo.width = 0 ;
			idinfo.name = "NO DECLARATION !" ;
			idinfo.pType = &Void ;
			m_pCurSymbolTable->m_hmIdentfy[pnewnontm->identify]=idinfo ;
		}
		break ;
	case 1 ://constant 
		{
			Constant *pConst = (Constant*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			pnewnontm->identify = m_pCurSymbolTable->NewTmpIdty(pConst->pType) ;
			codGen.Gen( "\t"+pnewnontm->identify+" = "+pConst->ToString() ) ;
		}
		
		break ;
	case 2 ://( expression ) 
		{
			Expression *pExpn = (Expression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pExpn->tmpentry ) ;
			pnewnontm->identify = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->identify+" = "+pExpn->tmpentry ) ;
		}
		
		break ;
	default:
		assert(0) ;
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}

int SemanticAnalyzer::constant ( int subproid ) {
	cout << "\tconstant called :" << subproid << endl ;
	Constant *pnewnontm = new Constant ;
	switch (subproid)
	{
	case 0 ://integer-constant 
		pnewnontm->entry = pnewnontm->AddIntConstant(
									m_pGrammer->token.GetLastToken()->origrinal ) ;
		pnewnontm->pType =  new TypeSpecifier(KULV_INT , 4 ,3) ;
		break ;
	case 1 ://character-constant 
		pnewnontm->entry = pnewnontm->AddCharConstant(
										m_pGrammer->token.GetLastToken()->origrinal ) ;
		pnewnontm->pType =  new TypeSpecifier(KULV_CHAR , 1 , 1) ;
		break ;
	case 2 ://floating-constant 
		pnewnontm->entry = pnewnontm->AddFloatConstant(
										m_pGrammer->token.GetLastToken()->origrinal ) ;
		pnewnontm->pType =  new TypeSpecifier (KULV_FLOAT , 4 ,5) ;
		break ;
	case 3 ://string-constant  
		pnewnontm->entry = pnewnontm->AddStringConstant(
										m_pGrammer->token.GetLastToken()->origrinal) ;
		pnewnontm->pType =  new TypeSpecifier(KULV_STRING , 1024 ,-1) ;
		break ;
	default:
		assert(0) ;
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}

int SemanticAnalyzer::conditional_expression ( int subproid ) {
	cout << "\tconditional_expression called :" << subproid << endl ;
	ConditionalExpression *pnewnontm = new ConditionalExpression;
	switch (subproid)
	{
	case 0 ://logical-OR-expression 
		{
			LogicalORExpression *pLogOrExpn=(LogicalORExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pLogOrExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pLogOrExpn->tmpentry) ;
		}
		break ;
	case 1://logical-OR-expression ? expression : conditional-expression  
		{
			ConditionalExpression *pCndtExpn=(ConditionalExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			Expression *pExpn = (Expression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back();
			LogicalORExpression *pLoglOrExpn=(LogicalORExpression*)(m_Semantic_stack.back().pNoneterm);
			m_Semantic_stack.pop_back();
			IdentifyInfo *idinfo = GetNearIdentify(pLoglOrExpn->tmpentry) ;
			pnewnontm->tmpentry=m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			//这里得回填！！
			assert(0) ;
		}
		break ;
	default:
		assert(0) ;
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}
int SemanticAnalyzer::logical_OR_expression ( int subproid ) {
	cout << "\tlogical_OR_expression called :" << subproid << endl ;
	LogicalORExpression *pnewnontm = new LogicalORExpression ;
	switch (subproid)
	{
	case 0 ://logical-AND-expression 
		{
			LogicalANDExpression *pLogOrExpn=(LogicalANDExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pLogOrExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pLogOrExpn->tmpentry) ;
		}
		break ;
	case 1://logical-OR-expression || logical-AND-expression  
		{
			LogicalANDExpression *pLoglAndExpn=(LogicalANDExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			LogicalORExpression *pLoglOrExpn=(LogicalORExpression*)(m_Semantic_stack.back().pNoneterm ) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pLoglAndExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pLoglOrExpn->tmpentry+" || "+pLoglAndExpn->tmpentry) ;
		}
		break ;
	default:
		assert(0) ;
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}

int SemanticAnalyzer::logical_AND_expression ( int subproid ) {
	cout << "\tlogical_AND_expression called :" << subproid << endl ;
	LogicalANDExpression *pnewnontm = new LogicalANDExpression;
	switch (subproid)
	{
	case 0 ://inclusive-OR-expression
		{
			InclusiveORExpression *pLogOrExpn=(InclusiveORExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pLogOrExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pLogOrExpn->tmpentry) ;
		}
		break ;
	case 1://logical-AND-expression && inclusive-OR-expression  
		{
			InclusiveORExpression *pInsvOrExpn=(InclusiveORExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			LogicalANDExpression *pLoglOrExpn=(LogicalANDExpression*)(m_Semantic_stack.back().pNoneterm ) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pInsvOrExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pLoglOrExpn->tmpentry+" | "+pInsvOrExpn->tmpentry) ;
		}
		break ;
	default:
		assert(0) ;
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}

int SemanticAnalyzer::inclusive_OR_expression ( int subproid ) {
	cout << "\tinclusive_OR_expression called :" << subproid << endl ;
	InclusiveORExpression *pnewnontm = new InclusiveORExpression;
	switch (subproid)
	{
	case 0 ://exclusive-OR-expression 
		{
			ExclusiveORExpression *pLogOrExpn=(ExclusiveORExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pLogOrExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pLogOrExpn->tmpentry) ;
		}
		break ;
	case 1://inclusive-OR-expression | exclusive-OR-expression
		{
			ExclusiveORExpression *pExsvOrExpn=(ExclusiveORExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			InclusiveORExpression *pInsvOrExpn=(InclusiveORExpression*)(m_Semantic_stack.back().pNoneterm ) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pExsvOrExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pInsvOrExpn->tmpentry+" | "+pExsvOrExpn->tmpentry) ;
		}
		break;
	default:
		assert(0) ;
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}

int SemanticAnalyzer::exclusive_OR_expression ( int subproid ) {
	cout << "\texclusive_OR_expression called :" << subproid << endl ;
	ExclusiveORExpression *pnewnontm = new ExclusiveORExpression ;
	switch (subproid)
	{
	case 0 ://AND-expression 
		{
			ANDExpression *pLogOrExpn=(ANDExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pLogOrExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pLogOrExpn->tmpentry) ;
		}
		break ;
	case 1://exclusive-OR-expression ^ AND-expression  
		{
			ANDExpression *pAndExpn=(ANDExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			ExclusiveORExpression *pExsvOrExpn=(ExclusiveORExpression*)(m_Semantic_stack.back().pNoneterm ) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pAndExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pExsvOrExpn->tmpentry+" ^ "+pAndExpn->tmpentry) ;
		}
		break;
	default:
		assert(0) ;
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}

int SemanticAnalyzer::AND_expression ( int subproid ) {
	cout << "\tAND_expression called :" << subproid << endl ;
	ANDExpression *pnewnontm = new ANDExpression ;
	switch (subproid)
	{
	case 0 ://equality-expression 
		{
			EqualityExpression *pLogOrExpn=(EqualityExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pLogOrExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pLogOrExpn->tmpentry) ;
		}
		break ;
	case 1://AND-expression & equality-expression  
		{
			EqualityExpression *pEqtyExpn=(EqualityExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			ANDExpression *pAndExpn=(ANDExpression*)(m_Semantic_stack.back().pNoneterm ) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pEqtyExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pAndExpn->tmpentry+" & "+pEqtyExpn->tmpentry) ;
		}
		break;
	default:
		assert(0) ;
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}


int SemanticAnalyzer::equality_expression ( int subproid ) {
	cout << "\tequality_expression called :" << subproid << endl ;
	EqualityExpression *pnewnontm = new EqualityExpression;
	switch (subproid)
	{
	case 0 ://relational-expression 
		{
			RalationalExpression *pLogOrExpn=(RalationalExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pLogOrExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pLogOrExpn->tmpentry) ;
		}
		break ;
	case 1://equality-expression == relational-expression 
		{
			RalationalExpression *pRatnExpn=(RalationalExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			EqualityExpression *pEqtyExpn=(EqualityExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pRatnExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pEqtyExpn->tmpentry+" == "+pRatnExpn->tmpentry) ;
		}
		break;
	case 2://equality-expression != relational-expression 
		{
			RalationalExpression *pRatnExpn=(RalationalExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			EqualityExpression *pEqtyExpn=(EqualityExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pRatnExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pEqtyExpn->tmpentry+" != "+pRatnExpn->tmpentry) ;
		}
		break ;
	default:
		assert(0) ;
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}

int SemanticAnalyzer::relational_expression ( int subproid ) {
	cout << "\trelational_expression called :" << subproid << endl ;
	RalationalExpression *pnewnontm = new RalationalExpression ;
	switch (subproid)
	{
	case 0 ://shift-expression 
		{
			ShiftExpression  *pLogOrExpn=(ShiftExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pLogOrExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pLogOrExpn->tmpentry) ;
		}
		break ;
	case 1://relational-expression < shift-expression 
		{
			ShiftExpression  *pShftExpn=(ShiftExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			RalationalExpression *pRatnExpn = (RalationalExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify( pShftExpn->tmpentry) ;
			assert( idinfo!= NULL ) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pShftExpn->tmpentry+" < "+pRatnExpn->tmpentry) ;
			assert(0);
		}
		break;
	case 2://relational-expression > shift-expression
		{
			ShiftExpression  *pShftExpn=(ShiftExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			RalationalExpression *pRatnExpn = (RalationalExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify( pShftExpn->tmpentry) ;
			assert( idinfo!= NULL ) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pShftExpn->tmpentry+" > "+pRatnExpn->tmpentry) ;
			assert(0);
		}
		break;
	case 3://relational-expression <= shift-expression
		{
			ShiftExpression  *pShftExpn=(ShiftExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			RalationalExpression *pRatnExpn = (RalationalExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify( pShftExpn->tmpentry) ;
			assert( idinfo!= NULL ) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pShftExpn->tmpentry+" <= "+pRatnExpn->tmpentry) ;
			assert(0);
		}
		break;
	case 4://relational-expression >= shift-expression
		{
			ShiftExpression  *pShftExpn=(ShiftExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			RalationalExpression *pRatnExpn = (RalationalExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify( pShftExpn->tmpentry) ;
			assert( idinfo!= NULL ) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pShftExpn->tmpentry+" >= "+pRatnExpn->tmpentry) ;
			assert(0);
		}
		break;
	default:
		assert(0) ;
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}


int SemanticAnalyzer::shift_expression ( int subproid ) {
	cout << "\tshift_expression called :" << subproid << endl ;
	ShiftExpression *pnewnontm = new ShiftExpression  ;
	switch (subproid)
	{
	case 0 ://additive-expression 
		{
			AdditiveExpression *pLogOrExpn=(AdditiveExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pLogOrExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pLogOrExpn->tmpentry) ;
		}
		break ;
	case 1://shift-expression << additive-expression 
		{
			AdditiveExpression *pAditExpn=(AdditiveExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			ShiftExpression *pShftExpn=(ShiftExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pAditExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pAditExpn->tmpentry+" << "+pShftExpn->tmpentry ) ;
		}
		break;
	case 2://shift-expression >> additive-expression  
		{
			AdditiveExpression *pAditExpn=(AdditiveExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			ShiftExpression *pShftExpn=(ShiftExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pAditExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pAditExpn->tmpentry+" >> "+pShftExpn->tmpentry ) ;
		}
	default:
		assert(0) ;
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}


int SemanticAnalyzer::additive_expression ( int subproid ) {
	cout << "\tadditive_expression called :" << subproid << endl ;
	AdditiveExpression *pnewnontm = new AdditiveExpression ;
	switch (subproid)
	{
	case 0 ://multiplicative-expression 
		{
			MultiplicativeExpression *pLogOrExpn=(MultiplicativeExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pLogOrExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pLogOrExpn->tmpentry) ;
		}
		break ;
	case 1://additive-expression + multiplicative-expression 
		{
			MultiplicativeExpression *pCastExpn=(MultiplicativeExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			AdditiveExpression * pMultExpn= (AdditiveExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *castidinfo = GetNearIdentify(pCastExpn->tmpentry) ;
			IdentifyInfo *multidinfo = GetNearIdentify(pMultExpn->tmpentry) ;
			assert(castidinfo!= NULL && multidinfo !=NULL ) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(castidinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pMultExpn->tmpentry+" + "+pCastExpn->tmpentry) ;
		}
		break;
	case 2://additive-expression - multiplicative-expression  
		{
			MultiplicativeExpression *pCastExpn=(MultiplicativeExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			AdditiveExpression * pMultExpn= (AdditiveExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *castidinfo = GetNearIdentify(pCastExpn->tmpentry) ;
			IdentifyInfo *multidinfo = GetNearIdentify(pMultExpn->tmpentry) ;
			assert(castidinfo!= NULL && multidinfo !=NULL ) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(castidinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pMultExpn->tmpentry+" - "+pCastExpn->tmpentry) ;
		}
		break ;
	default:
		assert(0) ;
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}


int SemanticAnalyzer::multiplicative_expression ( int subproid ) {
	cout << "\tmultiplicative_expression called :" << subproid << endl ;
	MultiplicativeExpression *pnewnontm = new MultiplicativeExpression;
	switch (subproid)
	{
	case 0 ://cast-expression 
		{
			CastExpression *pLogOrExpn=(CastExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *idinfo = GetNearIdentify(pLogOrExpn->tmpentry) ;
			assert(idinfo!= NULL) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(idinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pLogOrExpn->tmpentry) ;
		}
		break ;
	case 1://multiplicative-expression * cast-expression 
		{
			CastExpression *pCastExpn=(CastExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			MultiplicativeExpression * pMultExpn= (MultiplicativeExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *castidinfo = GetNearIdentify(pCastExpn->tmpentry) ;
			IdentifyInfo *multidinfo = GetNearIdentify(pMultExpn->tmpentry) ;
			assert(castidinfo!= NULL && multidinfo !=NULL ) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(castidinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pMultExpn->tmpentry+" * "+pCastExpn->tmpentry) ;
		}
		break;
	case 2://multiplicative-expression / cast-expression 
		{
			CastExpression *pCastExpn=(CastExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			MultiplicativeExpression * pMultExpn= (MultiplicativeExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *castidinfo = GetNearIdentify(pCastExpn->tmpentry) ;
			IdentifyInfo *multidinfo = GetNearIdentify(pMultExpn->tmpentry) ;
			assert(castidinfo!= NULL && multidinfo !=NULL ) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(castidinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pMultExpn->tmpentry+" / "+pCastExpn->tmpentry) ;
		}
		break;
	case 3://multiplicative-expression % cast-expression
		{
			CastExpression *pCastExpn=(CastExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			MultiplicativeExpression * pMultExpn= (MultiplicativeExpression*)(m_Semantic_stack.back().pNoneterm) ;
			m_Semantic_stack.pop_back() ;
			IdentifyInfo *castidinfo = GetNearIdentify(pCastExpn->tmpentry) ;
			IdentifyInfo *multidinfo = GetNearIdentify(pMultExpn->tmpentry) ;
			assert(castidinfo!= NULL && multidinfo !=NULL ) ;
			pnewnontm->tmpentry = m_pCurSymbolTable->NewTmpIdty(castidinfo->pType) ;
			codGen.Gen("\t"+pnewnontm->tmpentry+" = "+pMultExpn->tmpentry+" % "+pCastExpn->tmpentry) ;
		}
		break;
	default:
		assert(0) ;
		break ;
	}
	pnewnontm->subProduction = subproid ;
	newSematitem.pNoneterm = pnewnontm  ;
	m_Semantic_stack.push_back(newSematitem) ;
	return 0 ;
}


/*
int SemanticAnalyzer:: ( int subproid ) {
cout << "\t called :" << subproid << endl ;
*pnewnontm = new ;
switch (subproid)
{
case 0 ://
assert(0 ) ;
m_Semantic_stack.pop_back() ;
break ;
case 1://
assert(0);
break;
default:
assert(0) ;
break ;
}
pnewnontm->subProduction = subproid ;
newSematitem.pNoneterm = pnewnontm  ;
m_Semantic_stack.push_back(newSematitem) ;
return 0 ;
}

*/
