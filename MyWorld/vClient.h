#pragma once
#include "vCtrl.h"
#include "vMover.h"
#include "vUser.h"

class vCtrl;
class vMover;
class vUser;

typedef vCommonCtrl* (__stdcall* tCreateExpBox)(vUser* pUser);


class vClient
{
public:

	void Inject();

	void SendSystem( char* szStr, ... );
	void SendPlayMusic( DWORD dwWorldId, DWORD dwMusicId);

	void SendGetPlayer( DWORD idOperator );
	void SendWCWantedGold( char* szPlayer, u_long idPlayer, int nGold, char* szMsg );
	void SendWCWantedReward(u_long idPlayer, u_long idAttacker, char* szFormat, DWORD dwWorldID, const D3DXVECTOR3& vPos, int nLayer);

	tCreateExpBox m_pCreateExpBox;
};

static BOOL SendPacket( void* pThis, LPVOID lpData, DWORD dwDataSize, DWORD dpId)
{
	static const Address addrCall = 0x0041FEC0;
	BOOL _bRet = FALSE;
	__asm
	{
		push	dpId;
		push	dwDataSize;
		push	lpData;
		mov		ecx, pThis;
		call	addrCall;
		mov		_bRet, eax;
	}
	return _bRet;
}

vCommonCtrl* CreateExpBox(vUser* pUser);
void vCreateExpBox();