#include "stdafx.h"
#include "vLayeredLinkMap.h"

void vLayeredLinkMap::DeleteLinkMap( int nLayer )
{
	static const Address addrCall = 0x004F0B50;
	__asm
	{
		push	nLayer;
		mov		ecx, this;
		call	addrCall;
	}
}

vLinkMap* vLayeredLinkMap::GetLinkMap( int nLayer )
{
	static const Address addrCall = 0x004F0AB0;

	vLinkMap* _pLinkMap = nullptr;
	__asm
	{
		push	nLayer;
		mov		ecx, this;
		call	addrCall;
		mov		_pLinkMap, eax;
	}
	return _pLinkMap;
}