#pragma once
#include <string>
#include <fstream>
#include <set>
#include <map>
#include <hash_map>
#include <stack>
#include "SmallClass.h"
#include "TokenFile.h"
#include "SemanticAnalyzer.h"

using namespace std;
using namespace stdext ;
//72¸ö·ÇÖÕ½á·û

class GrammerAnalyzer
{
	friend STATE ;
	friend SemanticAnalyzer ;
public:
	GrammerAnalyzer( string &tooken );
	~GrammerAnalyzer(void);
	bool SelfPrepare(void);
	
private:
	int m_nErrorCount ;
	int m_nWarningCount ;
	string m_tokenFile ;
	int m_nTotallRightProductions ;
	hash_map<string , NoneTermItem >  m_NoneTermTable ;
	string m_realStarter ;
	set<string>	m_termList ;
	vector < STATE > m_State_Set ;

	vector < ClosureItem * > m_IhaveNewSymb ;
	set< ClosureItem * > m_IhaveNewSymbSet ;

	////////////////////--Kulv--2010/12/12---12:13:06--///////////////////////
	hash_map<size_t , map<std::string, int > > m_GrammarGoTo ;
	hash_map<size_t , map<std::string, ActionRes > > m_GrammarAction ;
	////////////////////--Kulv--2010/12/12---12:13:08--///////////////////////
	stack<State_Stack> m_AnalyzeStack ;
	TokenFile token ;

	SemanticAnalyzer semanticAnalyzer ;
	TOKEN curToken ;
	ActionRes * actres  ;

public:
	bool LoadGrammer(void);
	size_t GetNoneTermCount(void);
	bool IsNoneTerm(const string & str);
	bool AddTopology(string & starter);
	
	STATE * Closure(STATE * state);
	int GoTo( STATE & I, const string & X, STATE & newState );
	bool Items(void);

private:
	bool FRIST( NoneTermItem * noneterm , set<string> & res);
	NoneTermItem * GetNoneTermItem(string &termname);
	bool FOLLOW(NoneTermItem * noneterm, set<string> & res);
	bool ComputeFRISTS(void);
	bool ComputeFOLLOWS(void);
	
	int AddSTATE(STATE & newstate); // return the state id !
	int ExtractTerminals(void);
public:
	int GetBroadcastsInfo(void);
	bool InitBroadcast(void);
	int BeginBroadcast(void);
private:
	void PrintClosureItem(ClosureItem * closureItem,bool isLR1 = true );//overload it 
	void PrintClosureItem( vector<ClosureItem>::const_iterator clusureIt ,bool isLR1= true  ) ;
	int PrintState( STATE & state ,bool isLR1  = true );
	int PrintAllStates( bool isLR1 = true);

public:
	int Build_ACTION_GOTO(void);
	bool IsEndClosureItem(ClosureItem * cit) ;
	int GOTO(size_t stateid, string nonterminal);
	ActionRes * ACTION(size_t stateid, string input);
	int BeginAnalyze(void);
	int GetGrammarResult(void);
	int SaveActionGoto(void);
	void PrintProduction(string &noneterminateid, int subid);
	int AddIhaveNewSymb(ClosureItem * cloitem);
	int DelIhaveNewSymb(ClosureItem * cloitem);
	void LoadActionGoto(void);
};
