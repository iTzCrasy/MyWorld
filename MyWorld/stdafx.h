#pragma once

//////////////////////////////////////////////////////////////////////////
//=> Defines

#define __3RD_LEGEND16
#define __VER 21

#define NULL_ID 0xffffffff

#define WIN32_LEAN_AND_MEAN
#define LOG_ERROR 0
#define LOG_SUCCESS 1
#define LOG_INFO 2
#define COLOR_BLACK		0
#define COLOR_DARK_BLUE	1
#define COLOR_GREEN		2
#define COLOR_BLUE		3
#define COLOR_PINK		5
#define COLOR_BROWN		6
#define	COLOR_SILVER	7
#define COLOR_DSILVER	9
#define COLOR_BGREEN	10
#define COLOR_CYAN		11
#define COLOR_RED		12

#define AUTH_OBSERVER      'D'
#define AUTH_GENERAL       'F'
#define AUTH_LOGCHATTING   'G'
#define AUTH_JOURNALIST    'H'
#define AUTH_HELPER        'J'
#define AUTH_GAMEMASTER    'L'
#define AUTH_GAMEMASTER2   'M'
#define AUTH_GAMEMASTER3   'N'
#define AUTH_OPERATOR      'O'
#define AUTH_ADMINISTRATOR 'P'

#define TCM_CLIENT 0
#define TCM_SERVER 1
#define TCM_BOTH   2

#define MAX_REGIONDESC 256
#define MAX_REGIONTITLE 256

#define	MAX_OBJARRAY			8
#define	MAX_QUICKSLOT			21
#define	MAX_EQUIPMENT			18
#define	MAX_INVENTORY			42
#define MAX_GUILDBANK			42
#define	MAX_BANK				42
#define	MAX_REPAIR				16
#define	MAX_TRADE				25
#define	MAX_VENDITEM			30
#define	MAX_REPAIRINGITEM		25
#define	MAX_VENDORNAME			48
#define	MAX_STUFF				( MAX_INVENTORY + MAX_QUICKSLOT )
#define	MAX_EXPLPPOINT			41
#define	MAX_EXPSKILL			21
#define	MAX_EXPCHARACTER		200
#define	MAX_FXPCHARACTER		200
#define	MAX_CHARACTER_LIST		3 
#define	MAX_VENDOR_INVENTORY	100
#define	MAX_VENDOR_INVENTORY_TAB	4
#define	MAX_QUEST				100
#define	MAX_COMPLETE_QUEST		300 
#define MAX_CHECKED_QUEST		5
#define MAX_PARTYLEVEL			10
#define MAX_ADDEXPPARTY			16
#define MAX_RENEWEVENT			8000
#define MAX_REALITEM			8
#define MAX_EVENTREALITEM		4096
#define MAX_EXPJOBLEVEL			90
#define	ITEM_KIND_MAX			100
#define	MAX_HONOR_TITLE		150
#define MAX_VENDOR_REVISION		20

#define MATCHLESS_MODE					(DWORD)0x00000001
#define TRANSPARENT_MODE				(DWORD)0x00000002
#define ONEKILL_MODE					(DWORD)0x00000004
#define DONMOVE_MODE					(DWORD)0x00000008
#define SAYTALK_MODE					(DWORD)0x00000010
#define MATCHLESS2_MODE					(DWORD)0x00000020
#define NO_ATTACK_MODE					(DWORD)0x00000040
#define COMMUNITY_MODE					(DWORD)0x00000100
#define TALK_MODE						(DWORD)0x00000200
#define SHOUTTALK_MODE					(DWORD)0x00000400
#define	FREEPK_MODE						(DWORD)0x00001000
#define	MODE_MAILBOX					(DWORD)0x00008000
#define	EVENT_OLDBOY_MODE				(DWORD)0x00010000
#define	EQUIP_DENIAL_MODE				(DWORD)0x00020000
#define MODE_EXPUP_STOP					(DWORD)0x00040000
#define FRESH_MODE						(DWORD)0x10000000
#define DONTALK_MODE					(DWORD)0x00000610
#define OBSERVE_MODE					(DWORD)0x000000c0
#define	QUIZ_RENDER_SKIP_MODE			(DWORD)0x00200000

#define BEFORESENDDUAL( ar, dw, dpid_, dpid__ )	\
	vAr ar;		\
	int nBufSize;	\
	ar << dpid_ << dpid__ << dw;

#define	SEND( ar, pDPMng, idTo ) \
	LPBYTE lpBuf	= ar.GetBuffer( &nBufSize );	\
	SendPacket( (void*)pDPMng, (LPVOID)lpBuf, nBufSize, idTo );



#define BEGINTHREAD( pfnStartAddr, pvParam )  (HANDLE)_beginthreadex( NULL, NULL, pfnStartAddr, (void*)pvParam , NULL, NULL)


#define SAFE_DELETE(p)       { if(p) { delete(p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete [] (p); (p)=NULL; } }


#define NAKED __declspec( naked )


#define SetVar(Type, addr, Value) \
{ \
	*(Type*)addr = Value;\
}\

#define GetVar(Type, addr) \
{\
	return *(Type*)addr; \
}\

#define SET_ACCESSOR( type, name, ptr )      inline void Set##name( type value )   { *(type*)(this + ptr) = value; };
#define GET_ACCESSOR( type, name, ptr)       inline type Get##name()           { return *(type*)(this + ptr); };
#define GET_SET_ACCESSOR( type, name, ptr )   SET_ACCESSOR( type, name, ptr ) GET_ACCESSOR( type, name, ptr )


#define SET_ACCESSOR_GLOBAL( type, name, ptr )      inline void Set##name( type value )   { *(type*)(ptr) = value; };
#define GET_ACCESSOR_GLOBAL( type, name, ptr)       inline type Get##name()           { return *(type*)(ptr); };
#define GET_SET_ACCESSOR_GLOBAL( type, name, ptr )   SET_ACCESSOR( type, name, ptr ) GET_ACCESSOR( type, name, ptr )


#define	MAX_NAME	64

#define	MIN(x)	(1000*60*((int)x))
#define	SEC(x)	(1000*((int)x))

#define	AF_GENERIC			(DWORD)0x00000001
#define	AF_MISS				(DWORD)0x00000002
#define	AF_RESERVED			(DWORD)0x00000004
#define	AF_MAGIC			(DWORD)0x00000008
#define AF_MELEESKILL		(DWORD)0x00000010
#define AF_MAGICSKILL		(DWORD)0x00000020
#define AF_CRITICAL1		(DWORD)0x00000040
#define AF_CRITICAL2		(DWORD)0x00000080
#define AF_CRITICAL			(DWORD)0x000000c0
#define AF_PUSH				(DWORD)0x00000100
#define AF_PARRY			(DWORD)0x00000200
#define AF_RESIST			(DWORD)0x00000400
#define AF_STUN				(DWORD)0x00000800
#define AF_BLOCKING			(DWORD)0x00001000
#define AF_FORCE			(DWORD)0x00002000
#define AF_RANGE			(DWORD)0x00004000
#define AF_MONSTER_SP_CLIENT (DWORD)0x00008000
#define AF_FLYING			(DWORD)0x10000000


#define	COLOR_PLAYER			0xffffffff
#define COLOR_GAMEMASTER        0xff2D7CAE
#define COLOR_ADMINISTRATOR     0xffAE2D2D
#define	COLOR_NPC				0xffa0a0ff  
#define	COLOR_MONSTER			0xffffffa0
#define	COLOR_PARTY				0xff70f070
#define COLOR_GUILDCOMBAT		0xff00ff00

#define	MOP_NONE				0x00000000
#define	MOP_SWDFORCE			0x00000001
#define	MOP_FIXED				0x00000002
#define	MOP_NO_TRANS			0x00000004
#define	MOP_HITSLOW				0x00000008

#define	REQ_USESKILL			0x00000001
#define	REQ_MOTION				0x00000002

#define	OBJTYPE_PLAYER			0x00000001		
#define	OBJTYPE_MONSTER			0x00000002		
#define OBJTYPE_CTRL			0x00000004		
#define	OBJTYPE_FLYING			0x00010000

#define	CRITICAL_PROBABILITY	3
#define	CRITICAL_BERSERK_HP		30
#define	CRITICAL_BERSERK_PROB	22
#define	CRITICAL_AFTER_DEATH	22

#define	UI_NUM					0
#define	UI_HP					1
#define	UI_RN					2
#define	UI_AO					3
#define	UI_RAO					4
#define	UI_IR					5
#define	UI_PIERCING_SIZE		6
#define	UI_PIERCING				7
#define UI_COOLTIME				8
#define	UI_FLAG					9
#define	UI_RANDOMOPTITEMID		10
#define	UI_KEEPTIME				11
#define UI_REPAIR_NUM			12

#define UI_ULTIMATE_PIERCING_SIZE	13
#define UI_ULTIMATE_PIERCING		14

#define UI_PETVIS_SIZE			15
#define UI_PETVIS_ITEM			16
#define UI_PETVIS_ITEMSWAP		17
#define UI_TRANSFORM_VISPET		18

#define		MAX_SHORTCUT_STRING		128
#define		MAX_GOLD_COIN			32767
#define		MAX_GOLD_REWARD			INT_MAX
#define		MAX_INPUT_REWARD		200000000
#define		MIN_INPUT_REWARD		1000
#define		REQ_WANTED_GOLD			1000


#define MAX_SLOT_APPLET			18
#define MAX_SLOT_ITEM			10
#define MAX_SLOT_QUEUE			6
#define	MAX_SLOT_ITEM_COUNT		5

#define	SHORTCUT_NONE    0
#define	SHORTCUT_ETC     1
#define	SHORTCUT_APPLET  2
#define	SHORTCUT_MOTION  3
#define	SHORTCUT_SCRIPT  4
#define	SHORTCUT_ITEM    5
//#define	SHORTCUT_CARD    5
//#define	SHORTCUT_JACKBOX 6
#define	SHORTCUT_SKILL   6
#define SHORTCUT_OBJECT  7
#define SHORTCUT_CHAT    8
#define SHORTCUT_SKILLFUN 9
#define SHORTCUT_EMOTICON 10
#define SHORTCUT_LORDSKILL	 11

#define		FRAME_PER_SEC		60
#define		PROCESS_COUNT		(FRAME_PER_SEC / 4)

#define RESTATE_LOW				50


#define MAX_SKILL_JOB	( MAX_JOB_SKILL + MAX_EXPERT_SKILL + MAX_PRO_SKILL + MAX_MASTER_SKILL + MAX_HERO_SKILL + MAX_LEGEND_HERO_SKILL )

#define	TICK_CHEERPOINT	MIN( 60 )


#define	MAX_CHEERPOINT	3
#define	NULL_CHGPARAM	0x7FFFFFFF



#define	LEGEND_CLASS_NORMAL			0
#define	LEGEND_CLASS_MASTER			1
#define	LEGEND_CLASS_HERO			2

#define V(dtr){_vr = dtr; if(_vr != ERROR_SUCCESS)Log(LOG_ERROR, "%s Failed! Line: %d", __FUNCTION__, __LINE__);  }

#define SafeDetourToVar(varTo, t, dtFunc, dtMyFunc) varTo = (t)DetourFunction((PBYTE)dtFunc, (PBYTE)dtMyFunc );
#define SafeDetour(dtFunc, dtMyFunc)DetourFunction((PBYTE)dtFunc, (PBYTE)dtMyFunc); Log(LOG_SUCCESS, "%s | %s", __FUNCTION__, #dtFunc); 

//#define SafeDetour(dtFunc, dtMyFunc)DetourFunction((PBYTE)dtFunc, (PBYTE) dtMyFunc); 


#define MAP_SIZE (128)
#define NUM_PATCHES_PER_SIDE (16)
#define PATCH_SIZE (MAP_SIZE/NUM_PATCHES_PER_SIDE)
#define LIGHTMAP_SIZE ((PATCH_SIZE-1)*NUM_PATCHES_PER_SIDE)

#define DBGBREAK __asm{ int 3 }

#define FOR_LINKMAP( _pWorld, _vPos, _pObj, _nRange, _nLayer ) { \
	int _nLinkX = (int)( _vPos.x / _pWorld->m_iMPU );	\
	int _nLinkZ = (int)( _vPos.z / _pWorld->m_iMPU );	\
	for( int _i = 0; _i < _pWorld->m_linkMap.GetMaxLinkLevel( _nLayer ); _i++ ) {	\
		int _nWidthLink	= _pWorld->m_linkMap.GetLinkWidth( _i, _nLayer );	\
		vCtrl** _pObjs	= _pWorld->m_linkMap.GetObj( _i, _nLayer );	\
		int _nMaxWidth	= _nWidthLink * _pWorld->m_nLandWidth;	\
		int _nMaxHeight	= _nWidthLink * _pWorld->m_nLandHeight;	\
		int _nUnit	=  ( MAP_SIZE * _pWorld->m_nLandWidth ) / _nMaxWidth;	\
		int _nX		= ( _nLinkX / _nUnit ) * _nUnit * _pWorld->m_iMPU;	\
		int _nZ		= ( _nLinkZ / _nUnit ) * _nUnit * _pWorld->m_iMPU;	\
		int _d		= _nUnit * _pWorld->m_iMPU / 2;	\
		_nX		= ( (int)( _vPos.x ) - _nX > _d )? 1: 0;	\
		_nZ		= ( (int)( _vPos.z ) - _nZ > _d )? 1: 0;	\
		int _nLinkXMin = ( ( _nLinkX - _nRange ) / _nUnit ) + ( _nX - 1 );	if( _nLinkXMin < 0 ) _nLinkXMin = 0;	\
		int _nLinkZMin = ( ( _nLinkZ - _nRange ) / _nUnit ) + ( _nZ - 1 );	if( _nLinkZMin < 0 ) _nLinkZMin = 0;	\
		int _nLinkXMax = ( ( _nLinkX + _nRange ) / _nUnit ) + _nX;	if( _nLinkXMax >= _nMaxWidth  ) _nLinkXMax = _nMaxWidth - 1;	\
		int _nLinkZMax = ( ( _nLinkZ + _nRange ) / _nUnit ) + _nZ;	if( _nLinkZMax >= _nMaxHeight ) _nLinkZMax = _nMaxHeight - 1;	\
		for( int _j = _nLinkZMin; _j <= _nLinkZMax; _j++ )	\
		{	\
			for( int _k = _nLinkXMin; _k <= _nLinkXMax; _k++ ) \
			{	\
				int _nPos = _j * _nMaxWidth + _k;	\
				_pObj = _pObjs[ _nPos ];	\
				int __limit = 1000;  \
				while( _pObj && __limit-- ) { 


#define END_LINKMAP	\
	pObj = pObj->GetNextNode(); } } } } }

//////////////////////////////////////////////////////////////////////////
//=> Includes

#include "targetver.h"
#include <WinSock2.h>
#include <windows.h>

#if defined(DEBUG) || defined(_DEBUG)
#include <crtdbg.h>
#endif

#include "resource.h"

#include <math.h>
#include <map>
#include <vector>
#include <fcntl.h>
#include <stdio.h>
#include <io.h>
#include <iostream>
#include <stdio.h> 
#include <stdarg.h>
#include <tlhelp32.h>
#include <process.h>
#include <time.h>
#include <wtypes.h>
#include <wchar.h>
#include <assert.h>
#include <queue>
#include <shellapi.h>

#include <d3dx9math.h>
#include <d3dx9math.inl>

#include "detours.h"

#include <tbb/tbb.h>
#include <tbb/concurrent_hash_map.h>
#include <tbb/tbb_profiling.h>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "define.h"
#include "defineAttribute.h"
#include "defineEvent.h"
#include "defineEventArena.h"
#include "defineHonor.h"
#include "defineItem.h"
#include "defineItemGrade.h"
#include "defineItemkind.h"
#include "defineItemType.h"
#include "defineJob.h"
#include "definelordskill.h"
#include "defineMapComboBoxData.h"
#include "defineNeuz.h"
#include "defineObj.h"
#include "definequest.h"
#include "defineSkill.h"
#include "defineSound.h"
#include "defineText.h"
#include "defineWorld.h"
#include "LuaBase.h"

#include "MsgHdr.h"
#include <CommCtrl.h>
#include <atlbase.h>
#include <atlcom.h>
#include <initguid.h>
#include <uiribbon.h>
#include <UIRibbonPropertyHelpers.h>


//////////////////////////////////////////////////////////////////////////
//=> MyWorld specific includes

#include "vCommon.h"
#include "vStruct.h"
#include "vScanner.h"
#include "vGameEvent.h"

#include "vProperties.h"
#include "vPvpCombat.h"
#include "vTextCmd.h"

#include "vProject.h"



//////////////////////////////////////////////////////////////////////////
//=> Namespaces

using namespace std;
using namespace tbb;

//////////////////////////////////////////////////////////////////////////
//=> External



extern vProject			g_prj;
extern vPvPCombat		g_pPvPCombat;
extern vGameEvent		g_gameEvent;


extern IUIFramework*	g_pFramework;
extern HMODULE			g_hModule;
extern HMODULE			g_hModuleSrv;
extern ULONG			g_uKey;
extern ULONG			g_uIdofMulti;



//////////////////////////////////////////////////////////////////////////
//=> Libs

#pragma comment( lib, "lua52.lib" )
#pragma comment( lib, "detours.lib")
#pragma comment( lib, "propsys.lib")

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")



//////////////////////////////////////////////////////////////////////////
//=> Typedefs

typedef DWORD			OBJID;
typedef	__int64			EXPINTEGER;
typedef DWORD			UserID;
typedef unsigned char   u_char;
typedef unsigned short  u_short;
typedef unsigned int    u_int;
typedef unsigned long   u_long;
typedef DWORD			idPlayer;
typedef	DWORD			idParty;

