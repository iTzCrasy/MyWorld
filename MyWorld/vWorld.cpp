#include "stdafx.h"

#include "vWorld.h"


bool vWorld::AddObj( vCtrl* pObj, BOOL bAddItToGlobalId, int nLayer )
{
	static const Address addrCall = 0x005F4EC0;
	BOOL bRet = FALSE;
	__asm
	{
		push	nLayer;
		push	bAddItToGlobalId;
		push	pObj;

		mov  ecx, this;
		call addrCall;

		mov bRet, eax;
	}

	return bRet == TRUE;
}

float vWorld::GetLandHeight( float x, float z )
{
	static const Address addrCall = 0x005F57C0;

	float fRet = 0.0f;
	__asm
	{
		push	z;
		push	x;

		mov		ecx, this;
		call	addrCall;

		mov		fRet, eax;
	}
	return fRet;
}

void vWorld::SendDamageAround( D3DXVECTOR3* vPos, int nDmgType, vMover* pAttacker, int nApplyType, int nAttackID, float fRange )
{
	static const Address addrCall = 0x005F8130;
	__asm
	{
		push	fRange;
		push	nAttackID;
		push	nApplyType;
		push	pAttacker;
		push	nDmgType;
		push	vPos;

		mov		ecx, this;
		call	addrCall;
	}
}

bool vWorld::VecInWorld( float x, float z )
{
	float inv_mpu = 1.0f / (float)m_iMPU;

	if( _isnan( x ) )
		return false;
	if( x < 0.0f )
		return false;
	if( (x * inv_mpu) >= ( WORLD_WIDTH -1 ) )	
		return false;

	if( _isnan( z ) )
		return false;
	if( z < 0.0f )
		return false;
	if( (z * inv_mpu) >= ( WORLD_HEIGHT -1 ) )		
		return false;

	return true;
}

