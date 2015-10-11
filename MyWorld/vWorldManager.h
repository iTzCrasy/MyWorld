#pragma once
#include "Region.h"

class vWorldManager
{
public:
	void Inject();

	vWorld*		GetFirstActive(){ return *(vWorld**)(0x00894DE0 + 4 ); }
	vWorld*		GetWorld( DWORD dwWorldId );

	RegionElem* GetRevivalPos( DWORD dwWorldId, char* szKey);
	RegionElem*	GetRevivalPosChao( DWORD dwWorldId, char* sKey );
	RegionElem* GetNearRevivalPosChao( DWORD dwWorldId, D3DXVECTOR3 & vPos );
	RegionElem* GetNearRevivalPos( DWORD dwWorldId, D3DXVECTOR3 & vPos );

	vRegionElemArray*	m_aRevivalPos;
	vRegionElemArray*	m_aRevivalRgn;	
};

void CheckAdminMapKey();