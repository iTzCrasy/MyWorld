#include "stdafx.h"
#include "vUser.h"
#include "vUserManager.h"

//=> CGuildCombatMng => 0086C9D8

static const Address addrPlayerDataCenter	= 0x008792FC;
static const Address addrCallGetPlayerId	= 0x005A7D40;	

void vUserManager::Inject()
{
}

void vUserManager::RemoveAllUsers()
{
	static const Address addrRemAllUsr	= 0x00504730;

	__asm
	{
		mov ecx, addrUserMng;
		call addrRemAllUsr;
	}
}

DWORD vUserManager::GetUserId(char* szName)
{
	DWORD dwId = 0;
	__asm
	{
		push	szName;
		mov		ecx, addrPlayerDataCenter;

		call    addrCallGetPlayerId;

		mov		dwId, eax;
	}

	return dwId;
}

vUser* vUserManager::GetUserById(DWORD dwId)
{
	static const Address addrCall = 0x00504C40;
	vUser* pUser = nullptr;

	__asm
	{
		push	dwId;
		mov		ecx, addrUserMng;
		call	addrCall;
		mov		pUser, eax;
	}

	return pUser;
}

char* vUserManager::GetPlayerString( DWORD dwId )
{
	static const Address addrCall = 0x005A7CF0;
	char* szRet = nullptr;

	__asm
	{
		push dwId;
		mov ecx, addrPlayerDataCenter;

		call addrCall;
		mov szRet, eax;
	}

	return szRet;
}

bool vUserManager::IsValid( vMover* pMover)
{
	return pMover && !pMover->IsDelete();
}


void vUserManager::AddWorldCreateSfxObj( DWORD dwSfxObj, float x, float y, float z, BOOL bFlag, DWORD dwWorldId )
{
	static const Address addrCall = 0x0050BF30;
	__asm
	{
		push	dwWorldId;
		push	bFlag;
		push	z;
		push	y;
		push	x;
		push	dwSfxObj;

		mov		ecx, addrUserMng;
		call	addrCall;
	}
}

void vUserManager::DestroyUser(vUser* pUser)
{
	static const Address addrCall = 0x00504D40;

	__asm
	{
		push	pUser;

		mov		ecx, addrUserMng;
		call	addrCall;
	}
}

void vUserManager::AddCreateSfxObj(vCtrl* pCtrl, DWORD dwSfxObj, float x, float y, float z, BOOL bFlag)
{
	static const Address addrCall = 0x0050B3A0;
	__asm
	{
		push	bFlag;
		push	z;
		push	y;
		push	x;
		push	dwSfxObj;
		push	pCtrl;

		mov		ecx, addrUserMng;
		call	addrCall;
	}
}

void vUserManager::AddPushPower(vMover* pMover, float x, float y, float z, float fAngle, float fPushAngle, float fPower)
{
	static const Address addrCall = 0x0051FAE0;

	__asm
	{
		push	fPower;
		push	fPushAngle;
		push	fAngle;
		push	z;
		push	y;
		push	x;
		push	pMover;

		mov		ecx, addrUserMng;
		call	addrCall;
	}
}

void vUserManager::AddDamage( vMover* pMover, DWORD objidAttacker, DWORD dwHit, DWORD dwAtkFlags, DWORD dwAdd )
{
	static const Address addrCall = 0x00506810;
	__asm
	{
		push	dwAdd;
		push	dwAtkFlags;
		push	dwHit;
		push	objidAttacker;
		push	pMover;

		mov		ecx, addrUserMng;
		call	addrCall;
	}
}

void vUserManager::AddSetPointParam( vMover* pMover, int nDstParam, int nValue )
{
	static const Address addrCall = 0x005082C0;

	__asm
	{
		push	nValue;
		push	nDstParam;
		push	pMover;
		mov		ecx, addrUserMng;
		call	addrCall;
	}
}

void vUserManager::AddSetDestParam( vMover* pMover, int nDstParameter, int nAdjParameterValue, int nChgParameterValue)
{
	static const Address addrCall = 0x00507BE0;

	__asm
	{
		push	nChgParameterValue;
		push	nAdjParameterValue;
		push	nDstParameter;
		push	pMover;
		mov		ecx, addrUserMng;
		call addrCall;
	}
}


void vUserManager::AddResetDestParamSync( vMover* pMover, int nDstParameter,int nAdjParameterValue, int nParameterValue )
{
	static const Address addrCall = 0x00508070;
	__asm
	{
		push	nParameterValue;
		push	nAdjParameterValue;
		push	nDstParameter;
		push	pMover;
		mov		ecx, addrUserMng;
		call	addrCall;
	}
}


void vUserManager::AddResetDestParam( vMover* pMover, int nDstParameter, int nAdjParameterValue )
{
	static const Address addrCall = 0x00507E30;
	__asm
	{
		push	nAdjParameterValue;
		push	nDstParameter;
		push	pMover;
		mov		ecx, addrUserMng;
		call	addrCall;
	}
}

void vUserManager::AddSetStun( vMover* pMover, int nMaxTime )
{
	static const Address addrCall = 0x0051F3F0;
	__asm
	{
		push	nMaxTime;
		push	pMover;
		mov		ecx, addrUserMng;
		call	addrCall;
	}
}

vUserManager g_pUserMng;
