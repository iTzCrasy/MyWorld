#pragma once
#include "vCtrl.h"

class vCtrl;

#define	MAX_LINKTYPE	4

struct LINKMAP_INFO
{
	int			nMaxLevel;
	int			nWidth;
	vCtrl**		apObj;
};


class vLinkMap
{
private:
	LINKMAP_INFO	m_infos[MAX_LINKTYPE];	
	int			m_nLandWidth;
	int			m_nLandHeight;
	BOOL*		m_apfMask;
	int			m_nVisibilityRange;

	int			m_iMPU;

public:
	void		Release();

	int			GetLinkWidth( DWORD dwLinkType, int dwLinkLevel );
	vCtrl**		GetObj( DWORD dwLinkType, DWORD dwLinkLevel );
	DWORD		CalcLinkLevel( vCtrl* pObj, float fObjWidth );

	int			GetMaxLinkLevel( DWORD dwLinkType );
	void		SetMaxLinkLevel( DWORD dwLinkType, int nLevel );

	BOOL		InsertObjLink( vCtrl* pObj );
	BOOL		RemoveObjLink2( vCtrl* pObj );
	BOOL		RemoveObjLink( vCtrl* pObj );
	vCtrl*		GetObjInLinkMap( const D3DXVECTOR3 & vPos, DWORD dwLinkType, int nLinkLevel );
	BOOL		SetObjInLinkMap( const D3DXVECTOR3 & vPos, DWORD dwLinkType, int nLinkLevel, vCtrl* pObj );

	void		AddItToView( vCtrl* pCtrl );
	void		ModifyView( vCtrl* pCtrl );


	void		Invalidate( BOOL bInvalid )	{ m_bInvalid = bInvalid; }

private:
	int			IsOverlapped( int c, int p, int r, int w );
	vCtrl**		GetObjPtr( const D3DXVECTOR3 & vPos, DWORD dwLinkType, int nLinkLevel );

private:
	BOOL	m_bInvalid;
};


class vLayeredLinkMap
{
public:
	void	DeleteLinkMap( int nLayer );
	int		GetMaxLinkLevel( int nLayer );
	int		GetLinkWidth( int nLinkLevel, int nLayer );
	vCtrl**	GetObj( DWORD dwLinkLevel, int nLayer );
	vLinkMap* GetLinkMap( int nLayer );

public:
//	map<int, CLinkMap*>		m_mapLinkMap;
	int	m_nLandWidth;
	int	m_nLandHeight;
	int	m_nView;

	int m_iMPU;
};

