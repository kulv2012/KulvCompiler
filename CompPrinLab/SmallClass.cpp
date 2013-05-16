#include "StdAfx.h"
#include "SmallClass.h"
#include <assert.h>
#include "GrammerAnalyzer.h"
#include <algorithm>

size_t STATE::stateID = 0  ;
int NoneTermItem::NoneTermItemID = 0;

STATE::STATE(void)
: isFinished(false)
,m_stateID(-1)
,grammar(NULL)
{
}

STATE::~STATE(void)
{
}

bool STATE::PushBack(ClosureItem &ci) 
{
	for ( size_t i = 0 ; i < m_closItems.size() ; i ++  ) {
		if ( ci == m_closItems[i] ) {
			return false ;
		}
	}
	m_closItems.push_back(ci) ;
	return true ;
}
int STATE::ClosureSelf( bool isLR )
{
	assert(grammar != NULL) ;
	ClosureItem bsClosure ; 
	NoneTermItem nti ;
	set<string > fristBa ;
	vector<string> Ba ;
	for ( size_t i = 0 ; i < m_closItems.size() ; i ++ ) {//for each items  
		//it sounds like one time is ok !!!
		Ba.clear() , nti.m_vecItems.clear() ,nti.m_First.clear() ,fristBa.clear() ;
		vector<string> *production = &m_closItems[i].term->m_vecItems[m_closItems[i].m_nSubItem] ;
		//find the production
		if ( m_closItems[i].pointPos < (int)production->size()   ) {//at the middle
			//different from SLR , that SLR don't care about the Ba's follow !!!
			string B = (*production)[m_closItems[i].pointPos] ;//get the next symbol
			if ( grammar->IsNoneTerm(B) == true ) {
////////////////////--Kulv--2010/12/10---22:23:01--///////////////////////
 //only LR(1) run !!!
				if ( isLR == true  ) {
					nti.m_strName = "__Ba__" ;
					for ( int j = m_closItems[i].pointPos+1 ; j < (int)production->size() ; j ++  ) {
						Ba.push_back( (*production)[j]  ) ;
					}
					for ( set<string>::const_iterator sy=m_closItems[i].symb.begin()
	/*this code */				;sy!=m_closItems[i].symb.end();sy++ ) {
	/*only run  */		Ba.push_back( *sy ) ;
	/*by LR(1)  */		nti.m_vecItems.push_back( Ba ) ;//just one production
	/************/		Ba.pop_back() ;
					}
					
					//nti.m_vecItems.push_back( Ba ) ;//just one production
					grammar->FRIST( &nti ,fristBa ) ;//get the first sets
					bsClosure.symb = fristBa ;
				}
				
////////////////////--Kulv--2010/12/10---22:23:13--///////////////////////
				NoneTermItem * nonetermB = grammar->GetNoneTermItem( B  ) ;
				assert( nonetermB != NULL ) ;
				//for each production
				for ( int fp = 0 ; fp < (int)nonetermB->m_vecItems.size() ; fp ++ ) {
					bsClosure.term = nonetermB ;
					bsClosure.m_nSubItem = fp ;
					bsClosure.pointPos = 0 ;
					ClosureItem * ishashead = IsHeadSame(bsClosure) ;
					if (  ishashead != NULL  ) {
						ishashead->symb.insert(bsClosure.symb.begin() , bsClosure.symb.end() ) ;
					}
					else {
						this->PushBack(bsClosure) ;
					}
				}
			}
		}
	}
	CompressSameHead() ;
	return 0;
}

ClosureItem * STATE::IsHeadSame(ClosureItem & newclusureitem)
{
	for ( size_t i = 0 ; i < this->m_closItems.size() ; i ++ ) {
		ClosureItem *tmp = &( this->m_closItems[i] ) ;
		if ( tmp->term == newclusureitem.term 
			&& tmp->m_nSubItem == newclusureitem.m_nSubItem 
			&& tmp->pointPos == newclusureitem.pointPos ) {
			return tmp ;
		}
	}
	return NULL;
}

int STATE::CompressSameHead(void)
{
	vector < ClosureItem > newclosure ; int j = 0 ;
	sort( this->m_closItems.begin() , this->m_closItems.end()  ) ;
	newclosure.push_back(m_closItems[0]) ;
	for ( size_t i = 1 ; i < m_closItems.size() ; i ++ ) {
		ClosureItem *tmp1 = &( this->m_closItems[i-1] ) ;
		ClosureItem *tmp2 = &( this->m_closItems[i] ) ;
		if ( tmp1->term == tmp2->term 
			&& tmp1->m_nSubItem == tmp2->m_nSubItem
			&& tmp1->pointPos == tmp2->pointPos ) {
				newclosure[j].symb.insert(tmp2->symb.begin() , tmp2->symb.end() ) ;
		}
		else {
			j ++ ;
			newclosure.push_back(m_closItems[i]) ;
		}
	}
	m_closItems.clear() ;
	m_closItems = newclosure ;
	return 0;
}
