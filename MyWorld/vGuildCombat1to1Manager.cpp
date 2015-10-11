#include "stdafx.h"
#include "vGuildCombat1to1Manager.h"

static const Address addr1to1 = 0x007832F8;


void vGuildCombat1to1Manager::Inject()
{

}

BOOL vGuildCombat1to1Manager::IsPossibleUser( vUser* pUser )
{
	static const Address addrCall = 0x005665C0;
	BOOL _bRet = FALSE;
	__asm
	{
		push	pUser;

		mov		ecx, addr1to1;
		call	addrCall;
		mov		_bRet, eax;
	}
	return _bRet;
}

vGuildCombat1to1Manager g_pGuildCombat1to1Mng;