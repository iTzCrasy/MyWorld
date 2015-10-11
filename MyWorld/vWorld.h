#pragma once
#include "vLayeredLinkMap.h"

typedef struct WATERHEIGHT
{
	byte byWaterHeight;
	byte byWaterTexture;

}WATERHEIGHT;

class vWorld
{
public:
	float	GetLandHeight( float x, float z );
	bool	AddObj( vCtrl* pObj, BOOL bAddItToGlobalId, int nLayer );
	bool	VecInWorld( float x, float z );

	
	void	SendDamageAround( D3DXVECTOR3* pvPos, int nDmgType, vMover* pAttacker, int nApplyType, int nAttackID, float fRange );

	inline	bool	IsArena()	{ return m_dwWorldID == WI_WORLD_ARENA; }
	inline	DWORD	GetId()		{ return m_dwWorldID;					}

public:
	DWORD			m_dwWorldID;
	int				m_nLandWidth;
	int				m_nLandHeight;
	int				WORLD_WIDTH;
	int				WORLD_HEIGHT;
	int				m_iMPU;
	int				m_cbRunnableObject;
	float*			m_apHeightMap;	
	void*			m_apWaterHeight;

	vLayeredLinkMap m_linkMap;
	
	//0x24

	GET_ACCESSOR( vWorld*,		NextPtr,		0x840BC );
	GET_ACCESSOR( float,		MaxHeight,		0x86128	);
	GET_ACCESSOR( float,		MinHeight,		0x8612C	);
	GET_ACCESSOR( BOOL,			Indoor,			0x8A320	);
	GET_ACCESSOR( DWORD,		Diffuse,		0x8A324	);
	GET_ACCESSOR( int,			chAddObjs,		0x17019 );
	GET_ACCESSOR( int,			chReplaceObj,	0x5405C	);

	GET_SET_ACCESSOR( BOOL,			Fly,		0x8A31C	);
};

