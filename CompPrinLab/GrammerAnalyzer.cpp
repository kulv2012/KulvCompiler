#include "StdAfx.h"
#include <assert.h>
#include <string>
#include "GrammerAnalyzer.h"
#include <iostream>
#include "SmallClass.h"

using namespace std;

//int globaldepth = 0 ;
GrammerAnalyzer::GrammerAnalyzer( string &tooken )
:m_nTotallRightProductions(0)
,m_nErrorCount(0)
,m_nWarningCount(0)
{
	token.SetFile(tooken) ;
	semanticAnalyzer.SetGrammerAnalyzer( this ) ;
}

GrammerAnalyzer::~GrammerAnalyzer(void)
{
}

bool GrammerAnalyzer::LoadGrammer(void)
{
	ifstream gmfile( GRAMMER_FILE /*infile.c_str() */,ios::in) ;
	if (!gmfile) {//if orror,then exit
		 (*outer)  << "FILE not find !"<< myendl ;
		throw "file open error in LoadGrammer !" ;
		return false ;
	}
	string word , unit ;
	NoneTermItem nti ;
	vector<string> production ;
	char line[256] ;
	////////////////////--Kulv--2010/12/09---1:32:16--///////////////////////
	gmfile >> word  ;
	AddTopology( word.substr(0,word.length()-1) ) ;//拓广文法
	do {//each one iteration finish a none terminate identify 
		gmfile.getline(line, 256 , '\n') ;//extract the \n line 
		if ( word.length() > 1 && word[word.length() - 1] == ':' &&word[0]!='#'&&word[1]!='#') {
			nti.m_strName = word.substr(0,word.length()-1) ;//store the name 

			while(gmfile.getline(line, 256 , '\n') ) {
				if ( line[0] == '\t' ) {//get the units of a line , store it in the vector!!!
					const int len = strlen(line) ;
					for ( int i = 1 ; i < len ; i++ ){//we assume the first char of line is space!
						if ( line[i] =='#' &&line[i+1] == '#' ) {
							break ;
						}
						else if ( line[i] != ' ' && line[i] != '\n' && line[i] != '\t' ) {
							unit  +=  line[i]   ;
						}
						else if( unit.length() > 0 ) {
							production.push_back(unit) ;
							unit.clear() ;
						}
						if ( i == len-1 && unit.length() > 0 ) {
							production.push_back(unit) ;
							unit.clear() ;
						}
					}
					int trys = production.size() ;
						if( production.size() != 0 ){ 
						nti.m_vecItems.push_back(production) ;//add a production in the list 
						m_nTotallRightProductions++ ;
						production.clear() ;
					}
				}
				else {//finished a new production 
					break ;
				}
			}
			nti.m_terminateID =  NoneTermItem::NoneTermItemID ++ ;
			//m_NoneTermTable.push_back(nti) ;//push it in 
			m_NoneTermTable[nti.m_strName] = nti ;//push it in 
			nti.m_vecItems.clear() ;//clear the nonterminate 
		}
		else{
			// (*outer)  << "文法格式不对！请核对文法格式是否正确,正在处理："<<word<<" 时"<<endl;
			//throw "文法格式不对！请核对文法格式是否正确,正在处理："+word+" 时" ;
			//return false ;
		}//
	}while( gmfile >> word ) ;

	gmfile.close() ;//close the file 
	return true ;
}

size_t GrammerAnalyzer::GetNoneTermCount(void)
{
	return m_NoneTermTable.size();
}

bool GrammerAnalyzer::IsNoneTerm(const string &str)
{
	/*hash_map< string ,NoneTermItem >::const_iterator it = m_NoneTermTable.begin() ;
	while (it != m_NoneTermTable.end() )
	{
		if ( str == it->first )
			return true ;
		it ++ ;
	}*/
	if ( m_NoneTermTable.count(str) > 0 ) {
		return true ;
	}
	return false ;
}

//we assurme that the termname is really a none terminal 
NoneTermItem * GrammerAnalyzer::GetNoneTermItem(string &termname)
{
	//for ( int i = 0 ; i < (int)m_NoneTermTable.size() ; i ++ ) {
		if ( m_NoneTermTable.count(termname) != 0 ) {
			return &m_NoneTermTable[termname] ;
		}
	//}
	return NULL;
}


bool GrammerAnalyzer::AddTopology(string & starter)
{
	m_realStarter = starter ;
	NoneTermItem nti ;
	vector<string> production ;
	production.push_back(starter) ;
	nti.m_strName = TOPOLOGY_STARTER ;
	nti.m_vecItems.push_back(production) ;
	nti.m_terminateID = NoneTermItem::NoneTermItemID ++ ;
	//nti.m_Follow.insert( END_SIGN ) ;//这是结束符号！记得词法分析一定要加上这个结束符号！
	m_NoneTermTable[nti.m_strName] = nti ;
	return false;
}

/*
求一个项目集（状态）的闭包
*/
STATE * GrammerAnalyzer::Closure( STATE * state )
{
	assert(0== 1) ;
	state->isFinished = true ;
	//state->ClosureSelf();
	return state ;
}

//if production can be empty ,then return false ,else true ;
bool  GrammerAnalyzer::FRIST(NoneTermItem * noneterm , set<string> & res )
{	
	// (*outer)  << noneterm->m_strName << "\t"<< globaldepth++ << myendl  ;
	assert( noneterm != NULL ) ;

	if ( noneterm->m_First.size() > 0 ) {
		res.insert(noneterm->m_First.begin(),noneterm->m_First.end() ) ;//if we have already computed it , return ;
		return true ;
	}
	if ( noneterm->m_bIsCalculating == true ) {
		return true ;//this is cruise , avoid the noneterminal recruise 无穷递归!!!
	}
	vector< vector<string> > ::iterator it = noneterm->m_vecItems.begin() ;
	if ( it == noneterm->m_vecItems.end() ) {
		return false ;//if is empty 
	}
	noneterm->m_bIsCalculating = true ;// record the state , avoid the 递归
	while ( it != noneterm->m_vecItems.end() )
	{//each production
		vector<string>::iterator prodit = it->begin() ;
		while ( prodit != it->end() )
		{
			if ( IsNoneTerm( *prodit ) == false ) {
				noneterm->m_First.insert( *prodit ) ;
				break ;
			}
			else {
				if ( true == FRIST( GetNoneTermItem(*prodit) , noneterm->m_First ) ){
					break ;//if no empty
				}
			}
			prodit ++ ;
		}
		it ++ ;
	}
	res.insert(noneterm->m_First.begin() , noneterm->m_First.end() ) ;
	noneterm->m_bIsCalculating = false ;
	//noneterm->m_First.insert(tmp.begin() , tmp.end() ) ;
	return  true ;
}


bool GrammerAnalyzer::FOLLOW(NoneTermItem * noneterm, set<string> & res)
{
	return false;
}

bool GrammerAnalyzer::ComputeFRISTS(void)
{
	 (*outer)  << "\n\nFRIST Sets :\n" ;
	 hash_map<string , NoneTermItem >::iterator hashit = m_NoneTermTable.begin() ;
	 while ( hashit != m_NoneTermTable.end( ) ) {
		//for ( size_t i = 0 ; i < (int)m_NoneTermTable.size() ; i ++ ) {
			//global depth = 0 ;
			FRIST( &(hashit->second) , hashit->second.m_First ) ;
			 (*outer)  << hashit->second.m_strName << "\t :   " ;
			for ( set<string>::iterator it  = hashit->second.m_First.begin()
				; it != hashit->second.m_First.end(); it ++ ) 
				 (*outer)  << *it << "\t" ;
			 (*outer)  << "\n\n" ;
		//}
			 hashit ++ ;
	 }
	return true;
}

bool GrammerAnalyzer::ComputeFOLLOWS(void)
{
	hash_map<string, NoneTermItem >::iterator noneTerm = m_NoneTermTable.begin() ;
	while ( noneTerm != m_NoneTermTable.end() )
	{//for each none terminatal
		assert(noneTerm->second.m_vecItems.size() > 0 ) ;
		vector< vector<string> >::iterator production = noneTerm->second.m_vecItems.begin() ;
		while ( production != noneTerm->second.m_vecItems.end() )
		{//for each production
			assert( 1 != 1 ) ;// sounds that there is no need to compute it !
			production ++ ;
		}
		noneTerm ++ ;
	}
	return false;
}

int GrammerAnalyzer::GoTo(STATE & I, const string & X , STATE & newState  )
{
	if ( I.m_GoTo.count( X ) > 0 ) {
		return  I.m_GoTo[X] ;// if existed ,just return the state id !
	}
	vector < ClosureItem >::const_iterator closureitem = I.m_closItems.begin() ;
	while ( closureitem != I.m_closItems.end() ) {
		assert(closureitem->term != NULL ) ;
		if ( closureitem->term->m_vecItems[closureitem->m_nSubItem].size() > closureitem->pointPos
			&& closureitem->term->m_vecItems[closureitem->m_nSubItem][closureitem->pointPos] == X ){
				//find the right production that pos is befor X
			ClosureItem tmp = *closureitem ;
			tmp.pointPos ++ ;
			newState.PushBack( tmp ) ;
		}
		closureitem ++ ;
	}
	if ( newState.m_closItems.size() == 0 ) {
		return -1 ;
	}
	//newState.ClosureSelf( isLR ) ; //donot clusure self!!!
	assert( newState.m_stateID == -1 ) ;
	return -1;
}

bool GrammerAnalyzer::Items(void)
{
	STATE newstate , tmpstate ;
	ClosureItem tmp ;
	tmp.term = &m_NoneTermTable[TOPOLOGY_STARTER] ;
	tmp.m_nSubItem = 0 ;
	tmp.pointPos = 0 ;
	tmp.newSymb.insert( END_SIGN ); //at frist , we insert````
	newstate.PushBack( tmp ) ;
	newstate.grammar = this ;
	//newstate.ClosureSelf( false ) ; //not get the SLR set 
	AddSTATE( newstate ) ;//add the first closure

	for( size_t i = 0 ; i < m_State_Set.size() ;  i ++ ) {
		//for each state!
		tmpstate = m_State_Set[i] ;
		tmpstate.ClosureSelf(false) ;
		////////////////////--Kulv--2010/12/15---23:13:24--///////////////////////
		vector < ClosureItem >::const_iterator closuit = tmpstate.m_closItems.begin() ;
		while ( closuit != tmpstate.m_closItems.end() ) {
			assert(closuit->term != NULL ) ;
			if ( closuit->term->m_vecItems[closuit->m_nSubItem].size() > closuit->pointPos ){
				string B = closuit->term->m_vecItems[closuit->m_nSubItem][closuit->pointPos] ;
					newstate.Clear() ;
					GoTo(tmpstate , B , newstate) ;
					if ( newstate.m_closItems.size() > 0  ) {//not empty
						m_State_Set[i].m_GoTo[B] = AddSTATE( newstate ) ;
						//cout << "goto " << i <<"\t" << m_State_Set[i].m_GoTo[ itnontermitem->m_strName]<< endl ;
					}
			}
			closuit ++ ;
		}
		//continue ;
		//////////////////////--Kulv--2010/12/15---23:13:28--///////////////////////
		//hash_map<string,NoneTermItem >::const_iterator itnontermitem = m_NoneTermTable.begin() ;
		//while (itnontermitem != m_NoneTermTable.end() )
		//{//for each none terminals 
		//	newstate.Clear() ;
		//	/*tmpstate = m_State_Set[i] ;
		//	tmpstate.ClosureSelf(false) ;*/
		//	GoTo( tmpstate , itnontermitem->second.m_strName , newstate  ) ;
		//	if ( newstate.m_closItems.size() > 0  ) {//not empty
		//		m_State_Set[i].m_GoTo[itnontermitem->second.m_strName] = AddSTATE( newstate ) ;
		//		//cout << "goto " << i <<"\t" << m_State_Set[i].m_GoTo[ itnontermitem->m_strName]<< endl ;
		//	}
		//	itnontermitem ++ ;
		//}
		////for each terminals !
		//set<string>::iterator ittermitem = m_termList.begin() ;
		//while (ittermitem != m_termList.end() ) {
		//	newstate.Clear() ;
		//	/*tmpstate = m_State_Set[i] ;
		//	tmpstate.ClosureSelf(false) ;*/
		//	GoTo( tmpstate , *ittermitem , newstate  ) ;
		//	if ( newstate.m_closItems.size() > 0  ) {//not empty
		//		//add the state , return the state id , store it in the table !
		//		m_State_Set[i].m_GoTo[ *ittermitem ] = AddSTATE( newstate ) ;
		//		//cout << "goto " << i <<"\t" << m_State_Set[i].m_GoTo[ *ittermitem ]  << endl ;
		//	}
		//	ittermitem ++ ;
		//}
	}
	return false;
}

int GrammerAnalyzer::AddSTATE(STATE & newstate)
{
	assert(newstate.m_stateID == -1 ) ;
////////////////////--Kulv--2010/12/09---18:46:47--///////////////////////
	vector < STATE >::iterator it = m_State_Set.begin() ;
	while (it != m_State_Set.end() )
	{//search if the state is already existed !
		if ( it->m_closItems.size() == newstate.m_closItems.size() //for the sack of performance ,first compare this
			&& it->m_closItems == newstate.m_closItems ) {
			return it->m_stateID ;//if already existed , just return false 
		}
		it ++ ;
	}
	//if it is new ! add it 
	newstate.m_stateID = STATE::stateID++ ;
	newstate.isFinished = true ;
	m_State_Set.push_back(newstate) ;

	PrintState(newstate , false ) ;
	//(*outer)  << "\nadd state : "<<newstate.m_stateID <<"\t\tSize : "<< newstate.m_closItems.size() ;
	return newstate.m_stateID ;
}

int GrammerAnalyzer::ExtractTerminals(void)
{
	(*outer)  << "\n\nNone Terminals :" <<"\tTotal count :\t"<<m_NoneTermTable.size() << myendl ;
	if ( m_termList.size() == 0  ) {
		hash_map<string, NoneTermItem >::const_iterator nonetermit = m_NoneTermTable.begin() ;
		while (nonetermit != m_NoneTermTable.end() )
		{ (*outer)  << "\t" << nonetermit->second.m_strName ;
			vector< vector<string> >::const_iterator production = nonetermit->second.m_vecItems.begin() ;
			while ( production != nonetermit->second.m_vecItems.end()  ) {
				vector<string>::const_iterator words = production->begin() ;
				while ( words != production->end()  ) {
					if ( IsNoneTerm( *words ) == false  ) {//not a none terminals , then insert it !
						m_termList.insert(*words) ;//insert it , no depulibicate
					}
					
					words++ ;
				}
				production ++ ;
			}
			nonetermit ++ ;
		}
	}
	 (*outer)  << "\n\nTerminals :" << "\tTotal count :\t" << m_termList.size() << myendl  ;
	for ( set<string>::iterator it = m_termList.begin() ; it != m_termList.end() ; it ++ ) {
		 (*outer)  << "\t" << *it  ;
	} (*outer)  << myendl ;
	return m_termList.size() ;
}

bool GrammerAnalyzer::SelfPrepare(void)
{
	(*outer)  << "Total None Terminates : "<< GetNoneTermCount() << myendl ;
	(*outer)  << "Total Right Productions :" << m_nTotallRightProductions << myendl ;
	(*outer)  << "Finished Loading C Grammar!"<< myendl ;

	ComputeFRISTS() ; // compute the frist set , for performance 
	ExtractTerminals() ; // extract the terminals out !
	
	Items() ; // compute the totall states 
	(*outer) <<"\nTotall LR(0) States is : "<< this->m_State_Set.size() << myendl ;

	(*outer) << "\n\nBroadcast Information:\n" ;
	GetBroadcastsInfo() ;

	(*outer) << "\n\nBegin Broadcast :\n" ;
	BeginBroadcast() ;
	//(*outer)<<"\n\nafter all ! :" << myendl ;
	//PrintAllStates( ) ;
	(*outer) << "\n\nBuild Action ,Goto Chart !\n" ;
	Build_ACTION_GOTO() ;
	return true ;
}

void GrammerAnalyzer::PrintClosureItem(ClosureItem * closureItem , bool isLR1 )
{
	assert(closureItem != NULL ) ;
	//static NoneTermItem * lastterm = NULL ;
	NoneTermItem * term = closureItem->term ;
	/*if(term != lastterm )*/(*outer) << term->m_strName << " --> " ;
	//else   (*outer) << "\t\t" ;//just print one header
	/*lastterm = term ;*/
	vector<string> * pProduction = &(term->m_vecItems[ closureItem->m_nSubItem ]) ;
	for ( size_t i = 0 ; i < (*pProduction).size() ; i ++ ) {
		//print the none terminals befor the point !
		if ( i == closureItem->pointPos  ) 
			(*outer)  <<" ● "; 
		(*outer)  << (*pProduction)[i] << "  " ;
	} 
	if ( closureItem->pointPos == (*pProduction).size() )
		(*outer)  <<" ● "; // if the point is at the last 
	////////////////////--Kulv--2010/12/11---11:22:53--///////////////////////
	if ( isLR1 == true  ) {
		(*outer)  << "\t\t【 ";
		for ( set<string>::iterator sy = closureItem->symb.begin() ; 
			sy != closureItem->symb.end() ; sy ++ ) {//print the lasts 
				(*outer) << *sy <<"   " ;
		}
		(*outer)<<" 】" ;
	}
	(*outer)<<myendl;
}

void GrammerAnalyzer::PrintClosureItem( vector<ClosureItem>::const_iterator clusureIt , bool isLR1  )
{
	//static NoneTermItem * lastterm = NULL ;
	NoneTermItem * term = clusureIt->term ;
	/*if(term != lastterm )*/(*outer) << term->m_strName << " --> " ;
	//else   (*outer) << "\t\t" ;//just print one header
	/*lastterm = term ;*/
	vector<string> * pProduction = &(term->m_vecItems[ clusureIt->m_nSubItem ]) ;
	for ( size_t i = 0 ; i < (*pProduction).size() ; i ++ ) {
		//print the none terminals befor the point !
		if ( i == clusureIt->pointPos  ) 
			(*outer)  <<" ● "; 
		(*outer)  << (*pProduction)[i] << "  " ;
	} 
	if ( clusureIt->pointPos == (*pProduction).size() )
		(*outer)  <<" ● "; // if the point is at the last 
	////////////////////--Kulv--2010/12/11---11:22:53--///////////////////////
	if ( isLR1 == true ) {
		(*outer)  << "\t\t【 ";
		for ( set<string>::const_iterator sy = clusureIt->symb.begin() ; 
			sy != clusureIt->symb.end() ; sy ++ ) {//print the lasts 
				(*outer) << *sy <<"   " ;
		}
		(*outer)<<" 】" ;
	}
	(*outer) <<myendl ;
		

}
int GrammerAnalyzer::PrintState( STATE & state ,bool isLR1   )
{
	(*outer)  << "\nstate : "<<state.m_stateID <<"\t\tSize : "<< state.m_closItems.size()<<myendl  ;
	for ( size_t sub = 0 ; sub < state.m_closItems.size() ; sub ++  ) {
		PrintClosureItem( &(state.m_closItems[sub]) ,isLR1  ) ;
////////////////////--Kulv--2010/12/11---11:23:19--///////////////////////
	} 
	return 0;
}

int GrammerAnalyzer::PrintAllStates( bool isLR1  )
{
	vector < STATE >::iterator stateIt = m_State_Set.begin() ;
	while ( stateIt != m_State_Set.end() ) {
		stateIt->ClosureSelf ( true ) ;
		PrintState( *stateIt ,isLR1 ) ;
		stateIt ++ ;
	}
	return 0;
}


int GrammerAnalyzer::GetBroadcastsInfo(void)
{
	STATE J , shouldEmpty ;
	ClosureItem tmpclusureitem ;
	InitBroadcast() ;
	//attention : the states in m_State_Set is already kernel Items !!!!
	vector< STATE >::iterator stateIt = m_State_Set.begin() ;
	while ( stateIt != m_State_Set.end()  ) {	
		(*outer) << "\nstate: "<< stateIt->m_stateID  ;
		//for each states eg: state 0 
		vector<ClosureItem>::iterator clusureIt = stateIt->m_closItems.begin() ;
		while ( clusureIt != stateIt->m_closItems.end() ) {
			//for each clusureItem eg: S -> R . L
			//destruct a closure item.
			tmpclusureitem.symb.insert(INVALID_IDENTIFY) ;//others is same
			tmpclusureitem.term = clusureIt->term ;
			tmpclusureitem.m_nSubItem = clusureIt->m_nSubItem ;
			tmpclusureitem.pointPos = clusureIt->pointPos ;
			J.Clear() ; J.grammar = this ;
			J.m_closItems.push_back(tmpclusureitem) ;//insert into the tmpstate 
			J.ClosureSelf( true ) ; // get the LR(1) ClosureItem
			
			vector<ClosureItem>::iterator JsClosureIt = J.m_closItems.begin() ;
			while ( JsClosureIt != J.m_closItems.end() ) {
				//for each J's closureitems .eg : [ B -> r.Xp , a ]
				vector<string> * production = &(JsClosureIt->term->m_vecItems[JsClosureIt->m_nSubItem]) ;
				if ( JsClosureIt->pointPos < (*production).size() ) {
					//if not the end !!!
					string X = (*production)[ JsClosureIt->pointPos ] ;
					int stateID = GoTo(*stateIt , X ,shouldEmpty) ;
					assert( shouldEmpty.m_stateID == -1 ) ;
					if( stateID == -1 ) {JsClosureIt ;continue ; } 
					
					//find the B -> rX.p in goto( I , X)
					vector<ClosureItem> * pGoTo_I_X = &(m_State_Set[stateID].m_closItems) ;
					for ( size_t closItemgotoI_X = 0 ; closItemgotoI_X < pGoTo_I_X->size() ; closItemgotoI_X++ ) {
						bool hasNewProduses = false ;
						vector<string> *gotoI_X_production = 
									&((*pGoTo_I_X)[closItemgotoI_X].term->m_vecItems[(*pGoTo_I_X)[closItemgotoI_X].m_nSubItem] );
						if ( X == (*gotoI_X_production)[(*pGoTo_I_X)[closItemgotoI_X].pointPos-1] ){
							set<string>::iterator itinner = JsClosureIt->symb.begin() ;
							while ( itinner != JsClosureIt->symb.end() ) {
								if ( *itinner == INVALID_IDENTIFY ) {//if is "#",then broadcast
									clusureIt->broadcastTo.push_back( &(*pGoTo_I_X)[closItemgotoI_X] ) ;
									//(*outer) <<"\t\tBroadcast from : " ;PrintClosureItem(clusureIt,false) ;
									//(*outer) <<"\t\tTo : \t\t\t\t\t\t\t" ;PrintClosureItem(&(*pGoTo_I_X)[closItemgotoI_X],false) ;
									//(*outer) <<"broadcast to :"<< (*pGoTo_I_X)[closItemgotoI_X].term->m_strName<< myendl ;
								}
								else   {
									(*pGoTo_I_X)[closItemgotoI_X].newSymb.insert( *itinner ) ;
									//(*outer) << "\t\tproduct \" " <<*itinner<<"\" from : ";
									//PrintClosureItem(clusureIt,false) ;(*outer) << "\t\tTo :\t\t\t\t\t\t\t"; 
									//PrintClosureItem(&(*pGoTo_I_X)[closItemgotoI_X],false) ;
									hasNewProduses = true ;
								}
								itinner ++ ;//now , allow me to simply push_back it !!```` i know it's bad `
							}
							if( hasNewProduses == true)  {
								AddIhaveNewSymb(&(*pGoTo_I_X)[closItemgotoI_X]) ;
								//m_IhaveNewSymb.push_back(&(*pGoTo_I_X)[closItemgotoI_X]) ;
							}
						}
					}
				} 
				JsClosureIt ++ ;
			}
			clusureIt ++ ;
		}
		stateIt ++ ;
	}
	return 0;
}

bool GrammerAnalyzer::InitBroadcast(void)
{
	//vector < ClosureItem > * pFirstClosureItems = &(m_State_Set[0].m_closItems[0] ) ;
	//ClosureItem * pFirstItem = &( (*pFirstClosureItems)[0] ) ;
	//assert( pFirstItem != NULL ) ;
	//m_IhaveNewSymb.push_back(pFirstItem) ;
	//m_IhaveNewSymb.push_back( &( m_State_Set[0].m_closItems[0] ) ) ;
	AddIhaveNewSymb( &( m_State_Set[0].m_closItems[0] ) ) ;
	return false;
}

int GrammerAnalyzer::BeginBroadcast(void)
{
	for( size_t newCluItem =  0 ; newCluItem < m_IhaveNewSymb.size() ; newCluItem ++) {
		//for each to 
		ClosureItem * currentCloItem = (m_IhaveNewSymb[newCluItem]) ;
		if ( currentCloItem->newSymb.size() == 0 )
			continue ;
		for( size_t sub = 0 ; sub < currentCloItem->broadcastTo.size() ; sub ++ ) {
			ClosureItem * tmp = currentCloItem->broadcastTo[sub] ;

			//(*outer) << "\nfrom : " ;PrintClosureItem(currentCloItem);(*outer) << "to :\t" ;
			//PrintClosureItem(tmp);(*outer)<<"\twith : ";

			//check if i have it !
			bool  isnew  = false;//for each look ahead char
			for ( set<string>::iterator it=currentCloItem->newSymb.begin();it!=currentCloItem->newSymb.end();it++ ) {
				if ( tmp->symb.count(*it) == 0 ) {//i dont have it 
					tmp->newSymb.insert(*it) ;isnew = true ;
					//(*outer)<<*it<< "  " ;
				}
			}
			if( isnew == true ) {
				AddIhaveNewSymb((currentCloItem->broadcastTo[sub] )) ;
				//m_IhaveNewSymb.push_back( (currentCloItem->broadcastTo[sub] ) ) ;
			}
			//else{
				//for ( set<string>::iterator it=currentCloItem->newSymb.begin();it!=currentCloItem->newSymb.end();it++ ) 
			//	;	//(*outer)<<*it<< "  " ;(*outer) <<myendl ;
				//(*outer) << "&&&&&&&&&&But I have it ! so no more &&&&&&&&&&&&&&&&&&&&&&&" ;
			//}
			//(*outer) <<myendl ;
			//tmp->newSymb.insert(  currentCloItem->newSymb.begin() , currentCloItem->newSymb.end() ) ;

		}
		currentCloItem->symb.insert(currentCloItem->newSymb.begin() , currentCloItem->newSymb.end() ) ;
		currentCloItem->newSymb.clear() ;
		DelIhaveNewSymb(currentCloItem) ;
		//m_IhaveNewSymb  i know i should delete the old element , best of all 
	}

	m_IhaveNewSymb.clear() ;
	return 0;
}

//hash_map<std::string, int > m_GoTo ;
int GrammerAnalyzer::Build_ACTION_GOTO(void)
{
	////////////////////--Kulv--2010/12/12---12:15:44--///////////////////////
	//GOTO 
	map<std::string, int > tmpgotoitem ;
	map<std::string, ActionRes > tmpactionitem ;
	ActionRes tmpactionres ;
	for(size_t statid = 0 ; statid < m_State_Set.size() ; statid ++ ) {
		hash_map<std::string,int>::iterator gotoit = m_State_Set[statid].m_GoTo.begin() ;
		while ( gotoit != m_State_Set[statid].m_GoTo.end() ) {
			if ( IsNoneTerm( gotoit->first ) == true ) {
				// if none terminal ,then goto 
				tmpgotoitem.insert(make_pair( gotoit->first , gotoit->second) ) ;
				//(*outer) << statid << " face " << gotoit->first <<" goto " <<gotoit->second <<myendl ;
			}
			else {	// if terminals ,, move into 
					tmpactionres.type = ACTION_MOVE_IN ;
					tmpactionres.stateid = gotoit->second ;
					tmpactionitem.insert( make_pair(gotoit->first,tmpactionres)  );
					//(*outer) << statid << " face " << gotoit->first <<" move to " <<gotoit->second<<myendl ;
			}
			gotoit ++ ;
		}
		if ( tmpgotoitem.size() > 0  ) {
			m_GrammarGoTo[statid] = tmpgotoitem ;
			tmpgotoitem.clear() ;
		}
		//then deal with the S' -> S. ,that's reduce
		ClosureItem * findreduce = NULL ;
		for ( size_t closuresub = 0 ; closuresub<m_State_Set[statid].m_closItems.size();closuresub++ ) {
			//seach all the closure items 
			findreduce  = &(m_State_Set[ statid].m_closItems[closuresub] ) ;
			int citsize = findreduce->term->m_vecItems[findreduce->m_nSubItem].size() ;
			if ( findreduce->pointPos == citsize ) { //find the target 
				for( set<string>::iterator symbit=findreduce->symb.begin();symbit!=findreduce->symb.end();symbit++)
				{//for each look forward sign 
					//if is S' -> S.
					if ( IsEndClosureItem(findreduce) == true ) {
						tmpactionres.type = ACTION_ACCEPT ;
						tmpactionres.terminal = findreduce->term->m_strName ;
						tmpactionres.subid = findreduce->m_nSubItem ;
						tmpactionitem.insert(make_pair( END_SIGN , tmpactionres ) ) ;
						//(*outer)<< statid  << " faced : " << *symbit << "\t\t果断接受！ ";PrintClosureItem(findreduce) ;
						continue ;
					}//accept it ! or , reduce
					tmpactionres.type = ACTION_REDUCE ;
					tmpactionres.terminal = findreduce->term->m_strName;
					tmpactionres.subid = findreduce->m_nSubItem ;
					tmpactionitem.insert(make_pair( *symbit , tmpactionres ) ) ;
					//(*outer) << statid << " faced : " << *symbit << "\t\tReduce: ";PrintClosureItem(findreduce) ;
				}
			}
		}
		if ( tmpactionitem.size() > 0 ) {
			m_GrammarAction[statid] = tmpactionitem ;
			tmpactionitem.clear() ;
		}

	}
	////////////////////--Kulv--2010/12/12---12:15:49--///////////////////////
	return 0;
}

bool GrammerAnalyzer::IsEndClosureItem(ClosureItem * cit)
{
	if ( cit->term->m_strName ==  TOPOLOGY_STARTER 
		&& cit->term->m_vecItems[cit->m_nSubItem].size() == 1
		&& cit->pointPos == 1
		&& (cit->term->m_vecItems[cit->m_nSubItem])[0] == m_realStarter ) {
		return true ;
	}
	return false ;
}

int GrammerAnalyzer::GOTO( size_t stateid, string nonterminal)
{
	//hash_map<size_t , map<std::string, int > > m_GrammarGoTo ;
	assert( stateid < STATE::stateID && stateid >= 0 ) ;
	map<std::string, int >::iterator it = m_GrammarGoTo[stateid].find(nonterminal) ;
	if ( it == m_GrammarGoTo[stateid].end() ) {
		return -1 ;
	}
	return (m_GrammarGoTo[stateid])[nonterminal] ;
}

ActionRes * GrammerAnalyzer::ACTION(size_t stateid, string input)
{
	//hash_map<size_t , map<std::string, ActionRes > > m_GrammarAction ;
	assert( stateid < STATE::stateID && stateid >=0 ) ;
	map<std::string, ActionRes >::iterator it = m_GrammarAction[stateid].find(input) ;
	if ( it == m_GrammarAction[stateid].end() ) {
		return NULL ;
	}
	return  &(m_GrammarAction[stateid][input] );
}

int GrammerAnalyzer::GetGrammarResult(void)
{
	return m_nErrorCount ;
}

void GrammerAnalyzer::PrintProduction(string &terminal, int subid)
{
	(*outer) << m_NoneTermTable[terminal].m_strName << " --> " ;
	vector<string>  * tmpp = &(m_NoneTermTable[terminal].m_vecItems[subid]) ;
	vector<string>::iterator it = tmpp->begin() ;
	while ( it != tmpp->end() ) {
		(*outer) << *it << " " ;
		it ++ ;
	}
	(*outer) << "\n" ;
}

int GrammerAnalyzer::AddIhaveNewSymb(ClosureItem * cloitem)
{
	/*set< ClosureItem * >::iterator it = m_IhaveNewSymbSet.find(cloitem) ;
	if ( it == m_IhaveNewSymbSet.end( ) && m_IhaveNewSymbSet.size() > 0 ) {
		return 0 ;
	}*/
	if ( m_IhaveNewSymbSet.count(cloitem) > 0  ) {
		return  0 ;
	}
	m_IhaveNewSymb.push_back(cloitem) ;
	m_IhaveNewSymbSet.insert(cloitem ) ;
	return 0;
}

int GrammerAnalyzer::DelIhaveNewSymb(ClosureItem * cloitem)
{
	set< ClosureItem * >::iterator it = m_IhaveNewSymbSet.find(cloitem) ;
	if ( it != m_IhaveNewSymbSet.end() ) {
		*it = NULL ;
	}
	return 0;
}

int GrammerAnalyzer::SaveActionGoto(void)
{
	////////////////////--Kulv--2010/12/15---17:28:59--///////////////////////
	ofstream outfile(GOTO_FILE, ios::out ) ;
	if (!outfile) {//if orror,then exit
		(*outer) <<"Sorry ! "<< GOTO_FILE<<" open error !"<<myendl;
		return false;
	}
	outfile << "state\treceive\tnewState\n" << endl ;
	hash_map<size_t , map<std::string, int > >::const_iterator gotoit = m_GrammarGoTo.begin() ;
	while ( gotoit != m_GrammarGoTo.end() ) {
		map<std::string,int>::const_iterator it = gotoit->second.begin() ;
		while ( it != gotoit->second.end() ) {
			outfile << gotoit->first<<"\t"<<it->first << "\t" << it->second <<"\n" ;
			it ++ ;
		}
		gotoit ++ ;
	}
	outfile.close() ;
	////////////////////--Kulv--2010/12/12---23:33:15--///////////////////////
	outfile.open(ACTION_FILE, ios::out ) ;
	if (!outfile) {//if orror,then exit
		(*outer) <<"Sorry ! "<< ACTION_FILE<<" open error !"<<myendl;
		return false;
	}
	outfile << "state\treceive\t\taction\t\tstate/(nontermainalID,subID):" << endl ;
	hash_map<size_t , map<std::string, ActionRes > >::const_iterator actionit = m_GrammarAction.begin() ;
	while ( actionit != m_GrammarAction.end() ) {
		map<std::string,ActionRes >::const_iterator it = actionit->second.begin() ;
		while ( it != actionit->second.end() ) {
			outfile << actionit->first<<"\t"<<it->first << "\t\t" ;
			if ( it->second.type ==ACTION_MOVE_IN ) {
				outfile<<it->second.type<<"\t"<<it->second.stateid  << endl ;
			}
			else if ( it->second.type == ACTION_REDUCE ) {
				outfile<<it->second.type<<"\t"<< it->second.terminal << "\t"<<it->second.subid	<<endl ;
			}
			else if ( it->second.type == ACTION_ACCEPT ) {
				outfile<<it->second.type<<"\t"<< it->second.terminal << "\t"<<it->second.subid	<<endl ;
			}
			it ++ ;
		}
		actionit ++ ;
	}
	outfile.close() ;
	return 0;
}


void GrammerAnalyzer::LoadActionGoto(void)
{
	size_t stateid = 0 ,laststatid = -1 , newstatid;
	string recev ;
	map<std::string, int > acpstat ;
	ifstream gotofile(GOTO_FILE, ios::in ) ;
	if (!gotofile) {//if orror,then exit
		(*outer) << "Sorry ! "<< GOTO_FILE<<" open error !"<<myendl;
		return  ;
	}
	char tmp[MAX_LINE] ;
	gotofile.getline(tmp,MAX_LINE,'\n') ;//delete the frist line 
	while ( !gotofile.eof() ) {
		gotofile>> stateid >>  recev >> newstatid ;
		
		if ( stateid != laststatid && laststatid != -1 ) {
			m_GrammarGoTo[laststatid] = acpstat ;
			acpstat.clear() ;
		}
		laststatid = stateid ;
		acpstat.insert( make_pair(recev , newstatid) ) ;
	}
	if ( acpstat.size() > 0 ) {
		m_GrammarGoTo[laststatid] = acpstat ;
	}
	gotofile.close() ;
	////////////////////--Kulv--2010/12/16---12:28:46--///////////////////////
	int type ;
	ActionRes actres ;
	int subid ;
	string terminal ;
	map<std::string, ActionRes > actitem ;
	ifstream actionfile( ACTION_FILE, ios::in ) ;
	if (!actionfile) {//if orror,then exit
		(*outer) <<"Sorry ! "<< ACTION_FILE<<" open error !"<<myendl;
		return  ;
	}
	actionfile.getline(tmp,MAX_LINE,'\n') ;//delete the frist line 
	laststatid = -1 ;
	while ( !actionfile.eof() ) {
		actionfile >> stateid >> recev >> type ;
		actres.type = (ACTION_TYPE)type ;
		if ( type == ACTION_MOVE_IN  ) {
			actionfile >> newstatid ;
			actres.stateid = newstatid ;
		}
		else if ( type == ACTION_REDUCE || type ==ACTION_ACCEPT ){
			actionfile >> terminal >> subid ;
			actres.terminal = terminal ;
			actres.subid = subid ;
		}

		if ( stateid != laststatid && laststatid != -1 ) {
			m_GrammarAction.insert(make_pair( laststatid , actitem ) ) ;
			STATE::stateID ++ ;// increase the state id 
			actitem.clear() ;
		}
		laststatid = stateid ;
		actitem.insert( make_pair( recev, actres) ) ;
	}
	if ( actitem.size() > 0 ) {
		m_GrammarAction.insert(make_pair( laststatid , actitem ) ) ;
		STATE::stateID ++ ;// increase the state id 
	}
	actionfile.close() ;
}



int GrammerAnalyzer::BeginAnalyze(void)
{
	State_Stack topStack = {0 , TOPOLOGY_STARTER } ;
	string A ; // A -> ab.   reduce !!
	m_AnalyzeStack.push(topStack) ;

	while(1){
		curToken = token.lookToken() ;
		topStack = m_AnalyzeStack.top() ;
		actres = ACTION(topStack.statid , curToken.sign ) ;
		if ( actres == NULL  ) {//error
			if ( curToken.type == END_OF_FILE ) {
				return -1;
			}
			(*outer) << "Line :"<< curToken.line << "\tGrammar error !\t\tDrop :" << curToken.origrinal << myendl ;
			token.ExtractToken() ;
			m_nErrorCount ++ ;
		}
		else if ( actres->type == ACTION_MOVE_IN ) {
			topStack.statid = actres->stateid ;
			topStack.sign = curToken.origrinal ;
			m_AnalyzeStack.push(topStack) ;
			(*outer) << "Move in :\t" << curToken.origrinal << myendl ;
			semanticAnalyzer.MoveIn( curToken.origrinal ) ;
			token.ExtractToken() ;
		}
		else if ( actres->type == ACTION_REDUCE ) {
			(*outer) << "Reduce :\t";
			PrintProduction(actres->terminal , actres->subid ) ;

			////////////////////--Kulv--2010/12/26---17:18:32--///////////////////////
			semanticAnalyzer.Reduce( *actres ) ;
			////////////////////--Kulv--2010/12/26---17:18:33--///////////////////////
			A = (m_NoneTermTable[actres->terminal]).m_strName;
			size_t len = ( (m_NoneTermTable[actres->terminal]).m_vecItems[actres->subid] ).size() ;
			for ( size_t num = 0 ; num < len ; num ++ ) {
				m_AnalyzeStack.pop() ;
			}
			topStack = m_AnalyzeStack.top() ;
			topStack.sign = A ;
			size_t newstate = GOTO( topStack.statid , A ) ;
			assert( 0 <= newstate && newstate <= STATE::stateID   ) ;
			topStack.statid = newstate ;
			m_AnalyzeStack.push(topStack) ;
		}
		else if ( actres->type == ACTION_ACCEPT ) {
			(*outer) << "\n\t\t\t接收，语法分析完成！！"<<myendl;

			return 0 ;
		}
		else{
			(*outer) << "BAD !! BAD action[][] returns " <<myendl;
		}
	}
	return 0;
}