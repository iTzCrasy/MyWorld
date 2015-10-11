#include "stdafx.h"
#include "vWorld.h"

#include "vCtrl.h"

void vCtrl::SetPos( D3DXVECTOR3& vPos )
{
	static const Address addrCall = 0x0064C980;

	__asm
	{
		push	vPos;
		mov		ecx, this;
		call	addrCall;
	}
}

void vCtrl::UpdateLocalMatrix()
{
	static const Address addrCall = 0x0064C2A0;
	__asm
	{
		mov		ecx, this;
		call	addrCall;
	}
}

bool vCtrl::InitMotion( DWORD dwMotion )
{
	BOOL _bRet = FALSE;
	__asm
	{
		push	dwMotion;

		mov     eax, this
		mov     edx, [eax]
		mov     ecx, this
		mov     eax, [edx+8]
		call    eax;

		mov		_bRet, eax;
	}

	return _bRet == TRUE;
}



void vCtrl::SetAngle( float fAngle )
{
	static const Address addrConst = 0x0064CDD0;

	__asm
	{
		push	fAngle;

		mov		ecx, this;
		call	addrConst;
	}
}

// void vCtrl::UpdateAI( AIBase* pAi, DWORD dwAiState )
// {
// 	delete GetpAIInterface();
// 
// 	SetpAIInterface( pAi );
// 	SetAIInterfaceState(dwAiState);
// }

// vObjProp* vCtrl::GetProps() 
// { 
// 	return g_prj.GetProps( GetType(), GetIndex() ); 
// }


//////////////////////////////////////////////////////////////////////////
vCtrl* CreateObj( DWORD dwObjType, DWORD dwObjIndex, BOOL bInitProp )
{
	static const Address addrCall = 0x0060C440;


	vCtrl* pObj = nullptr;
	__asm
	{
		push	bInitProp;
		push	dwObjIndex;
		push	dwObjType;
		push	0;

		call	addrCall;
		mov		pObj, eax;
		add     esp, 0x10;
	}

	return pObj;
}
