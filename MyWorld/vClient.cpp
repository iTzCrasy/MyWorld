#include "stdafx.h"
#include "vAr.h"
#include "vClient.h"

static const Address addrDPSrrvr = 0x00903058;
static const Address addrCoreClient = 0x00781AA8;

extern vProject			g_prj;

void vClient::Inject()
{
	SafeDetour(0x004C260B, vCreateExpBox);
}



void vClient::SendSystem( char* szStr, ... )
{
	static const Address addrCall = 0x00494910;

	char szBuff[512] = {0,};
	va_list arg;
	va_start(arg, szStr);
	vsnprintf_s(szBuff, 512, szStr, arg);
	va_end(arg);

	__asm
	{
		lea		ecx, szBuff;
		push	ecx;

		mov		ecx, addrCoreClient;
		call	addrCall;
	}
}

void vClient::SendPlayMusic( DWORD dwWorldId, DWORD dwMusicId)
{ 
	static const Address addrCall = 0x00494310;
	__asm
	{
		push	dwMusicId;
		push	dwWorldId;

		mov		ecx, addrCoreClient;
		call	addrCall;
	}
}

void vClient::SendGetPlayer( DWORD idOperator )
{
	static const Address addrCall = 0x004947F0;
	__asm
	{
		push	idOperator;
		mov		ecx, addrCoreClient;
		call	addrCall;
	}
}


vCommonCtrl* CreateExpBox(vUser* pUser)
{
	vCommonCtrl* pCtrl = (vCommonCtrl*)CreateObj(OT_CTRL, CI_EXPBOX);
	if( !pCtrl )
		return nullptr;


	float fRate = 0.1f, fDecExp = 0.0f;
	bool  bPxpClear = false, bLvDown = false;
	int   nLevel	= pUser->GetLevel();
	pUser->GetDieDecExp( nLevel, fRate, fDecExp, bPxpClear, bLvDown );

	if( fDecExp )
		pUser->GetDieDecExpRate( fDecExp, 0, FALSE );


	if( pUser->IsSMMode( SM_REVIVAL ) )
		fDecExp = 0.0f;

	if( pUser->GetExp1() == 0 )
		fDecExp = 0.0f;	

	if( pUser->m_bLastPK || pUser->m_bGuildCombat || pUser->m_bLastDuelParty )
		fDecExp = 0.0f;			

	if( fDecExp == 0.0f )
		return NULL;

	pCtrl->m_CtrlElem.m_dwSet = UA_PLAYER_ID;
	pCtrl->m_idExpPlayer = pUser->GetId();
	pCtrl->m_nExpBox  = (__int64)((float)g_prj.m_pExpCharacter[pUser->GetLevel()+1].nExp1 * fDecExp);
	pCtrl->m_dwDelete = GetTickCount() + MIN( 30 );

	pCtrl->SetPos( pUser->GetPos() );

	
	pUser->AddDefinedText(TID_GAME_EXPBOX_INFO_MSG, "" );
	pUser->AddChatText(   TID_GAME_EXPBOX_INFO_MSG, "");
	
	return pCtrl;
}

NAKED void vCreateExpBox()
{
	static const Address addrJmp = 0x004C2614;
	__asm
	{
		mov		edx, DWORD PTR SS:[ebp - 0x8];
		push	edx;
		call	CreateExpBox;
		jmp		addrJmp;
	}
}


void vClient::SendWCWantedGold( char* szPlayer, u_long idPlayer, int nGold, char* szMsg )
{
	static const Address addrCall = 0x0049BAA0;
	__asm
	{
		push	szMsg;
		push	nGold;
		push	idPlayer;
		push	szPlayer;

		mov		ecx, addrCoreClient;
		call	addrCall;
	}
}


void vClient::SendWCWantedReward(u_long idPlayer, u_long idAttacker, char* szFormat, DWORD dwWorldID, const D3DXVECTOR3& vPos, int nLayer)
{
	BEFORESENDDUAL(ar, 34603162, -1, -1 );
	ar << idPlayer << idAttacker << dwWorldID << vPos;
	ar.WriteString(szFormat);
	ar << nLayer;
	SEND( ar, addrCoreClient, 1 );
}




vClient g_pClient;