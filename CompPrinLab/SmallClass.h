#pragma once
#include <string>
#include <vector>
#include <set>
#include <hash_map>

using namespace std;
using namespace stdext ;


class GrammerAnalyzer ;
////////////////////--Kulv--2010/12/09---1:47:40--///////////////////////
//store a none terminate's all productions 
class  NoneTermItem
{
public:
	NoneTermItem():m_bIsCalculating(false){} 
	string m_strName ;
	int m_terminateID ;
	static int NoneTermItemID ;
	vector< vector<string> > m_vecItems ;//容器里面的每一项都代表一个产生式的右部
	//set<string>m_Follow ; //because the follow set is diffict to compute ,so we stored it 
	set<string>m_First ;
	bool m_bIsCalculating ;
protected:
private:
};

////////////////////--Kulv--2010/12/09---1:48:30--///////////////////////
class  ClosureItem
{
public:
	ClosureItem():term(NULL),m_nSubItem(-1){ };

	NoneTermItem *	term ;//point to the left none termainate
	size_t			m_nSubItem ;//point to the subitem of term,that's a production
	size_t			pointPos ;//the point of the production
	set<string>		symb ; // the symbol eg:$ , c , d ```` terminals 
	set<string>		newSymb ;//others give me

	vector< ClosureItem * > broadcastTo ;

	bool operator!=(ClosureItem & others) {
		if ( this->term == others.term && this->m_nSubItem == others.m_nSubItem
			&& this->pointPos == others.pointPos && this->symb == others.symb ) {
			return false ;
		}
		else
			return true ;
	}

	bool operator == (const ClosureItem & others)const {
		if ( this->term == others.term && this->m_nSubItem == others.m_nSubItem
			&& this->pointPos == others.pointPos && this->symb == others.symb ) {
				return true ;
		}
		else
			return false ;
	}

	friend bool operator < (const ClosureItem & one ,const ClosureItem & others ){
		if ( one.term->m_vecItems[ one.m_nSubItem ]
		<  others.term->m_vecItems[ others.m_nSubItem ]) {
			return true ;
		}
		return false ;
	}
};

class STATE 
{
public:
	STATE(void) ;
	~STATE(void);
	static size_t stateID ;
	size_t m_stateID ;
	GrammerAnalyzer * grammar ;
	vector < ClosureItem > m_closItems ;
	hash_map<std::string, int > m_GoTo ;
	
	
	bool isFinished ;
	//friend bool operator == (const STATE & one ,const STATE & others) {
	//	if ( one.m_closItems == others.m_closItems ) {
	//		return true ;
	//	}
	//	else return false ;
	//}

	//friend bool operator < (const STATE & one ,const STATE & others ){
	//	if(  one.m_closItems < others.m_stateID )
	//		return true ;
	//	else return false ;
	//}
protected:
private:
public:
	void Clear( ){
		m_closItems.clear() ;
		isFinished = false ;
		m_stateID = -1 ;
	}
	int ClosureSelf( bool isLR );
	ClosureItem * IsHeadSame(ClosureItem & newclusureitem);
	int CompressSameHead(void);
	bool PushBack(ClosureItem &ci) ;
};


enum ACTION_TYPE{ ACTION_MOVE_IN , ACTION_REDUCE , ACTION_ACCEPT };
class ActionRes 
{
public:
	ACTION_TYPE type ;
	//union{
		int stateid ;//goto where 
		struct{
			string terminal;//which terminal
			int subid ;//the sub production id 
		};
	//};
};


class State_Stack
{
public:
	size_t statid ;
	string sign ;
protected:
private:
};