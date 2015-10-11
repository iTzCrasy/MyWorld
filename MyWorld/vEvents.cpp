#include "stdafx.h"
#include "vUserManager.h"
#include "vTextCmd.h"
#include "vGui.h"
#include "vWorld.h"
#include "vEvents.h"


extern vUserManager g_pUserMng;
extern vTextCmd		g_pTextCmd;
extern vGui			g_vGui;

vEvents g_pEvents;

void vEvents::Inject()
{
	SafeDetour( 0x004F94C7, vProcess );
	SafeDetour( 0x004A3C63, vOnJoin );
	SafeDetour( 0x005048F6, vAdduser );
	SafeDetour( 0x0061A7F7, vDoDie);
	SafeDetour( 0x004C2463, vOnRevival );
	//SafeDetour( 0x004FAA64, vOnNotify );
	AsmPush( (PBYTE)0x00504876, sizeof( vUser ) );

	DWORD addr = 0;
	__asm
	{
		lea		ecx, vMover::SubPK;
		mov		addr, ecx;
		mov		ecx, g_pEvents;
	}

	AsmCall( (PBYTE)0x0061B1D9, (PBYTE)addr);

	
	SafeDetourToVar( m_pDestroyPlayerHook, tDestroyPlayer, 0x00504D40, vOnDestroyPlayer);
}


void OnNotify(vAr* pAr)
{
	Log(LOG_SUCCESS, "Addr %x", pAr);
	pAr->DumpPacket();
}

NAKED void vOnNotify()
{
	static Address add221 = 0x004FAA6E;
	__asm
	{
		push    eax
		mov     ecx, [ebp-4]
		add     ecx, 6236
		
		push	ecx;
		call	OnNotify;
		pop		ecx;

		JMP		add221

	}
}



//////////////////////////////////////////////////////////////////////////
//=> non virtual functions

void OnJoin(vUser* pUser)
{
	Log(LOG_INFO, "%s | User %s @ %x", __FUNCTION__, pUser->GetName(), pUser);
	Log(LOG_SUCCESS, "World: %x | %i [ %i : %i ] %i", pUser->GetWorld(), pUser->GetWorld()->GetId(), pUser->GetWorld()->m_nLandWidth, pUser->GetWorld()->m_nLandHeight, pUser->GetWorld()->m_cbRunnableObject);

	g_pUserMng.m_mapPlayers.insert(concurrent_hash_map<DWORD, vUser*>::value_type( pUser->GetId(), pUser ) );

	g_vGui.AddUser(pUser);
	pUser->ShowLoginInfo();
}

void Process()
{
	g_pPvPCombat.Process();
}

void OnAddUser(vUser* pUser)
{
}

void OnDoDie( vMover* pMover, vCtrl* pAttackerCtrl)
{
	vMover* pAttacker = nullptr;

 	if(pAttacker && pAttacker->GetType() == OT_MOVER)
 		pAttacker = (vMover*)pAttackerCtrl;

	Log(LOG_INFO,"%s | %s", __FUNCTION__, pMover->GetName());

	if( pAttacker )
	{
		Log( LOG_INFO, "User Died [ %s ] Attacked by [ %s ]", pMover->GetName(), pAttacker->GetName() );
	}
}

void OnRevivalResurrection(vUser* pUser)
{
	Log(LOG_INFO, "%s > %s", __FUNCTION__, pUser->GetName());
}


//////////////////////////////////////////////////////////////////////////
//=> virtual functions

void __stdcall vOnDestroyPlayer(vUser* pUser)
{
	concurrent_hash_map<DWORD, vUser*>::accessor a;

	if(!g_pUserMng.m_mapPlayers.find( a, pUser->GetId() ))
		return;

	g_vGui.RemoveUser(pUser);
	g_pUserMng.m_mapPlayers.erase( a );

	g_pEvents.m_pDestroyPlayerHook( pUser );
}


NAKED void vOnJoin()
{
	static const Address addrCall = 0x0047F180;
	static const Address addrExitJmp = 0x004A3CB8;
	__asm
	{
		call	addrCall;
		mov     ecx, [ebp-0x1C];
		push	ecx;
		call	OnJoin;
		pop		ecx;
		jmp		addrExitJmp;
	}
}

NAKED void vProcess()
{
	static const Address addrEveLuaProcess = 0x00535F90;
	static const Address addrPtr01 = 0x00869C0C;
	static const Address addrJmp = 0x004F94D1;

	__asm
	{
		mov		ecx, addrPtr01;
		call	addrEveLuaProcess;
		call	Process;
		jmp		addrJmp;
	}
}

NAKED void vAdduser()
{
	//0x46D0
	static const Address addrJmp =  0x0050493F;
	static const Address addrCall = 0x005AAE50;

	__asm
	{
		add     ecx, 8;
		call    addrCall;

		mov     ecx, [ebp- 0x4C]; //pUser
		push	ecx;

		call	OnAddUser;
		pop		ecx;

		mov		ecx, [ebp - 0x10];

		jmp		addrJmp;
	}
}

NAKED void vDoDie()
{
	static const Address addrCall = 0x00593550;

	static const Address addrJmp = 0x0061A802;
	__asm
	{
		call	addrCall;
		mov     eax, [ebp-0x0C0];

		mov		ecx, [ebp - 0x18];
		push	ecx;

		mov		ecx, [ebp - 0x10]; //=> this
		push	ecx;

		call	OnDoDie;

		pop		ecx;
		pop		ecx;

		jmp		addrJmp;
	}
}


NAKED void vOnRevival()
{
	static const Address addrJmp = 0x004C246D;
	static const Address addrCall = 0x006465A0;
	__asm
	{
		mov		ecx, DWORD PTR SS:[ ebp - 0x8 ];
		push	ecx;
		call	OnRevivalResurrection;
		pop		ecx;


		push	0;
		mov		ecx, DWORD PTR SS:[ ebp - 0x8 ];
		call	addrCall;
		jmp		addrJmp;
	}
}

 