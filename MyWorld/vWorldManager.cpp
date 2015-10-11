#include "stdafx.h"
#include "vWorld.h"
#include "vWorldManager.h"

static const Address addrThisPtr = 0x00894DE0;

void vWorldManager::Inject()
{
	SafeDetour( 0x006017F6, CheckAdminMapKey);
	SafeDetour( 0x005FAE6F, 0x005FAEFE );

	m_aRevivalPos = *(vRegionElemArray**)(addrThisPtr + 12);
	m_aRevivalRgn = *(vRegionElemArray**)(addrThisPtr + 193552);
}

vWorld* vWorldManager::GetWorld( DWORD dwWorldId )
{
	vWorld* pWorld = GetFirstActive();

	while(pWorld)
	{
		if( pWorld->m_dwWorldID == dwWorldId )
			return pWorld;

		pWorld	= pWorld->GetNextPtr();
	}
	return nullptr;
}


RegionElem*	vWorldManager::GetRevivalPosChao( DWORD dwWorldId, char* sKey )
{
	for( DWORD i = 0; i < m_aRevivalPos->GetSize(); i++ )
	{
		RegionElem* pRgnElem = m_aRevivalPos->GetAt( i );

		if( dwWorldId == pRgnElem->m_dwWorldId && strcmp( sKey, pRgnElem->m_szKey ) == 0 && pRgnElem->m_bChaoKey )
			return pRgnElem;
	}
	return nullptr;
}

RegionElem* vWorldManager::GetNearRevivalPosChao( DWORD dwWorldId, D3DXVECTOR3 & vPos )
{
	RegionElem* pReg = nullptr;

	long  d = INT_MAX;
	for( DWORD i = 0; i < m_aRevivalPos->GetSize(); i++ )
	{
		RegionElem* pRgnElem = m_aRevivalPos->GetAt( i );

		if( dwWorldId == pRgnElem->m_dwWorldId && pRgnElem->m_bChaoKey )
		{
			D3DXVECTOR3 vd	= vPos - pRgnElem->m_vPos;
			long temp = (long)D3DXVec3LengthSq( &vd );

			if( temp < d )
			{
				pReg = pRgnElem;
				d = temp;
			}

		}
	}

	if( pReg == NULL )
	{
		for( DWORD i = 0; i < m_aRevivalPos->GetSize(); i++ )
		{
			RegionElem* pRgnElem	= m_aRevivalPos->GetAt( i );
			if( dwWorldId != pRgnElem->m_dwWorldId && pRgnElem->m_bChaoKey )
			{
				pReg = pRgnElem;
				break;
			}
		}
	}

	return pReg;
}
// 00600EC5
RegionElem* vWorldManager::GetRevivalPos( DWORD dwWorldId, char* szKey)
{
	for( DWORD i = 0; i < m_aRevivalPos->GetSize(); i++ )
	{
		RegionElem* pRgnElem = m_aRevivalPos->GetAt( i );

		if( dwWorldId == pRgnElem->m_dwWorldId && strcmp( szKey, pRgnElem->m_szKey ) == 0 && pRgnElem->m_bChaoKey == FALSE )
			return pRgnElem;
	}

	return nullptr;
}

PRegionElem vWorldManager::GetNearRevivalPos( DWORD dwWorldId, D3DXVECTOR3 & vPos )
{
	for( DWORD i = 0; i < m_aRevivalRgn->GetSize(); i++ )
	{
		RegionElem* pRgnElem = m_aRevivalRgn->GetAt( i );
		if( dwWorldId == pRgnElem->m_dwWorldId && pRgnElem->m_dwIndex == RI_REVIVAL && pRgnElem->m_bChaoKey == FALSE )
		{
			POINT point;
			point.x	= (long)( vPos.x );
			point.y	= (long)( vPos.z );

			if( PtInRect( &pRgnElem->m_rect, point ) )
				return GetRevivalPos( dwWorldId, pRgnElem->m_szKey );
		}
	}

	long d = INT_MAX;
	RegionElem* ptr = nullptr;
	for( DWORD i = 0; i < m_aRevivalPos->GetSize(); i++ )
	{
		RegionElem* pRgnElem = m_aRevivalPos->GetAt( i );

		if( dwWorldId == pRgnElem->m_dwWorldId && pRgnElem->m_bChaoKey == FALSE )
		{
			D3DXVECTOR3 vd	= vPos - pRgnElem->m_vPos;
			long tmp	= (long)D3DXVec3LengthSq( &vd );
			if( tmp < d )
			{
				ptr	= pRgnElem;
				d	= tmp;
			}

		}
	}
	return ptr;
}



NAKED void CheckAdminMapKey()
{
	static const Address addrCall = 0x00405B70;
	static const Address addrExitCall = 0x00601834;
	static const Address addrExitCall01 = 0x006016F2;
	static char* szText = "vWorld debug: invalid mapkey! [Land : %s%02d-%02d]";

	__asm
	{
		mov     ecx, eax

		mov		ecx, [ebp + (0x658 + 0x8)];
		cmp		ecx, AUTH_ADMINISTRATOR;
		je		__jmp_admin__;

		mov     ecx, [ebp + 0x8];
		call    addrCall;

		jmp		addrExitCall01;
__jmp_admin__:
		
		mov     ecx, [ebp - 0x2C];
		push    ecx;
		mov     ecx, [ebp - 0x28];
		push    ecx;
		lea     ecx, [ebp - 0x134];
		push    ecx;

		push	szText;
		mov		ecx, [ebp + 0x8];
		call	vUser::AddText;


		jmp		addrExitCall;
	}
}

vWorldManager g_pWorldMng;