#include "stdafx.h"
#include "vPartyManager.h"

static const Address addrPartyMng = 0x00875E94;



void vPartyManager::Inject()
{
}


BOOL vPartyManager::DeleteParty(idParty id)
{
	static const Address addrCall = 0x005A1750;
	BOOL _bRet = FALSE;
	__asm
	{
		push	id;
		mov		ecx, addrPartyMng;
		call	addrCall;
		mov		_bRet, eax;
	}
	return _bRet;
}

vParty* vPartyManager::GetParty(idParty id )
{
	static const Address addrCall = 0x005A18F0;

	vParty* _ret = nullptr;
	__asm
	{
		push	id;

		mov		ecx, addrPartyMng;
		call	addrCall;
		mov		_ret, eax;
	}
	return _ret;
}


vPartyManager g_pPartyMng;