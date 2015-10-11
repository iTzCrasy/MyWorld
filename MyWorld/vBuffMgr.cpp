#include "stdafx.h"
#include "vBuffMgr.h"


void vBuffMgr::RemoveBuffs( DWORD dwFlags, DWORD dwParam )
{
	static const Address addrCall = 0x00528CE0;

	__asm
	{
		push	dwParam;
		push	dwFlags;

		mov		ecx, this;
		call	addrCall;
	}
}