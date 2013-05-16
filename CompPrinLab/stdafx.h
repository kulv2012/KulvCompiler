// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

////////////////////--Kulv--2010/12/10---22:22:13--///////////////////////
#define  NOT_PRINT_STATE_DETAIL 1
#define MAX_LINE  256
////////////////////--Kulv--2010/12/10---22:22:18--///////////////////////
#include "InforPrinter.h"
extern InforPrinter *outer ;
////////////////////--Kulv--2010/12/10---12:54:10--///////////////////////
#define TOPOLOGY_STARTER	"STARTER"
#define END_SIGN			"_KULV_END_"
#define INVALID_IDENTIFY	"_#_#_LOVE_#_#_"
////////////////////--Kulv--2010/12/10---22:20:22--///////////////////////
#define KEY_WORD_FILE ".\\Shared\\keyWords.txt"
#define OPERATOR_SPERATOR_FILE ".\\Shared\\Operator_Seperator.txt"
#define SYMBOL_ITEM_FILE	".\\Shared\\Symbole_Item.txt"
#define GRAMMER_FILE	".\\Grammar Analyze\\Grammar\\Grammar_EN--TARGET.txt"
#define INFORMATION_OUT_FILE	".\\Grammar Analyze\\Result\\Out_Information.txt" 
#define GOTO_FILE		".\\Grammar Analyze\\Result\\GOTO.txt"
#define ACTION_FILE		".\\Grammar Analyze\\Result\\ACTION.txt"
#define SEMANTIC_RES_IDENTIFY_FILE	".\\Semantic Analyze\\Identify.txt"
#define SEMANTIC_RES_MILDCODE_FILE	".\\Semantic Analyze\\MildCode.txt"
// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�

////////////////////--Kulv--2010/11/22---16:03:28--///////////////////////	-1
#define END_OF_FILE		-2
#define END_SIGN_ID		-1	//������׼
#define NEW_LINE	0		//new line 

#define KEY_WORD	1		// �ؼ���		 KEY_WORD	"string" 
#define VARIABLE	2		//����		 VARIABLE	���ű����ڵ�ַ

//#define OP_EQ_EQ	16		//	==		  
//#define OP_EQ		17		//	=		 
//#define ASDF		18		//	NO
//#define OP_SMALL	19		//	<		 
//#define OP_SM_EQ	20		//	<=		 
//#define OP_BIG		21		//	>		 	 
//#define OP_BI_EQ	22		//	>=	 
//#define OP_INCL		23		//	++		 
//#define OP_ADD		24		//	+		 
//#define OP_DECL		25		//	--		 
//#define OP_MIN		26		//	-		 
//#define OP_NE		27		//	!=	
//#define OP_NO		28		//	!
//
//#define SP_SLP		1024	//	(		
//#define SP_SRP		1025	//	)				
//#define SP_LP		1026	//	{		
//#define SP_RP		1027	//	}	
//#define SP_LSUB		1028	//	[
//#define SP_RSUB		1029	//	]
//#define SP_FETCH	1030	//	*
//#define SP_SEMI		1031	//	;
//#define SP_SHARP	1032	//	#
//#define SP_STR		1033	//	"
//#define SP_CHAR		1034	//	'


#define CST_STR			2048	//"```"
#define CST_CHAR		2049	//'*'
#define CST_CHAR_ES		2050	//'\n'
#define CST_DIGIT_8		2051	//
#define CST_DIGIT_10	2052	//
#define CST_DIGIT_16	2053	//
#define CST_FLOAT	2054	//float 

////////////////////--Kulv--2010/11/22---16:03:30--///////////////////////
//---------------ERROR---------------------------------
#define NO_IMPLEMENT	0,"�˴���û��ʵ�֣��Բ��𡤡���"
#define E_NO_STR_END	1,"�ַ�������ĩû��\"��β"
#define E_NO_CHAR_END	2,"�ַ�û���á�����������"
#define	E_INVALID_ESC	3,"�Ƿ���ת���ַ�����"
#define E_INVALID_CHAR	4,"�����Ƿ��ַ�"
#define E_FILE_END		5,"������ļ�ĩβ"
#define E_EXTRA_CHAR	6,"��������ķ���"
#define E_DIGIT_CHAR	7,"���ֺ��������ĸ�Ƿ�,�Ƿ������˷ָ�����"



////////////////////--Kulv--2010/12/02---10:10:24--///////////////////////
//---------------WARMMING-----------------------------
#define W_UNEXCEPT_ESCAPT	0,"����ʶ���ת���ַ�����"
