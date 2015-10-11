#include "stdafx.h"
#include "vInventory.h"


DWORD vInventory::GetAtItemId(DWORD dwItem)
{
	static const Address addrCall = 0x0048A2B0;

	DWORD dwRet = NULL;
	__asm
	{
		push	dwItem;

		mov		ecx, this;
		call	addrCall;
		mov		dwRet, eax;
	}
	return dwRet;
}

vItemElem* vInventory::GetAtId( DWORD dwId )
{
	if( dwId >= GetMax() )
		return nullptr;

	vItemElem* p = GetIndexNum() + (dwId * 4);

	return p->IsEmpty()? nullptr : p;
}

bool vInventory::IsEquip( DWORD dwObjId )
{
	if(!GetpItem())
		return false;

	if( dwObjId >= GetMax() )
		return false;
	return true;
}