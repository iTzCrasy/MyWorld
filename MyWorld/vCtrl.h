#pragma once

#define		MAX_LINKLEVEL	7	

class vWorld;
class vCtrl
{

public:
	void		SetPos( D3DXVECTOR3& vPos );
	void		UpdateLocalMatrix();
	bool		InitMotion( DWORD dwMotion );


	//	void		UpdateAI( AIBase* pAi, DWORD dwAiState = 2 );
	void		SetAngle( float fAngle );

	inline void SetFlag( bool bUpdate, DWORD dwValue )
	{
		if( bUpdate )
			m_dwFlags |= dwValue;
		else
			m_dwFlags &= (~dwValue);
	}

	inline BOOL				IsUpdateMatrix()				{ 	return (m_dwFlags & OBJ_FLAG_UPDATEMATRIX);			}
	inline BOOL				IsVisible()						{	return (m_dwFlags & OBJ_FLAG_VISIBLE);				}
	inline BOOL				IsVirtual()						{	return (m_dwFlags & OBJ_FLAG_VIRTUAL);				} 
	inline BOOL				IsDelete()						{	return (m_dwFlags & OBJ_FLAG_DELETE);				}
	inline BOOL				IsPosChanged()					{	return (m_dwFlags & OBJ_FLAG_POSCHANGED);			}

	inline void				SetUpdateMatrix( bool bUpdate ) {	SetFlag( bUpdate, OBJ_FLAG_UPDATEMATRIX );			}
	inline void				SetVisible( bool bUpdate )		{	SetFlag( bUpdate, OBJ_FLAG_VISIBLE );				}
	inline void				SetVirtual( bool bUpdate )		{	SetFlag( bUpdate, OBJ_FLAG_VIRTUAL );				}
	inline void				SetDelete( bool bUpdate )		{	SetFlag( bUpdate, OBJ_FLAG_DELETE );				}
	inline void				SetPosChanged( bool bUpdate)	{	SetFlag( bUpdate, OBJ_FLAG_POSCHANGED );			}

	inline float			GetAngle()						{	return m_fAngle;									}
	inline float			GetAngleX()						{	return m_fAngX;										}
	inline D3DXVECTOR3		GetPos()						{	return m_vPos;										}
	inline vWorld*			GetWorld()						{	return m_pWorld;									}
	inline DWORD			GetLinkLevel()					{	return m_dwLinkLevel;								}
	inline bool				IsDynamicObj()					{	return m_dwType != OT_OBJ && m_dwType != OT_SFX;	}

	inline D3DXMATRIX		GetMatrixTrans()	const		{	return m_matTrans;									}
	inline D3DXMATRIX		GetMatrixScale()	const		{	return m_matScale;									}
	inline D3DXMATRIX		GetMatrixRotation()	const		{	return m_matRotation;								}
	inline D3DXMATRIX		GetMatrixWorld()	const		{	return m_matWorld;									}
	inline D3DXMATRIX*		GetMatrixWorldPtr()				{	return &m_matWorld;									} 
	inline D3DXVECTOR3		GetLinkPos()					{	return m_vLink;										}
	inline D3DXVECTOR3		GetRemovalPos()					{	return m_vRemoval;									}
	inline int				GetLayer()						{	return m_nLayer;									}
	inline DWORD			GetType()						{	return m_dwType;									}
	inline DWORD			GetIndex()						{	return m_dwIndex;									}
	inline DWORD			GetId()							{	return m_objid;										}
	inline D3DXMATRIX*		GetInvTM()						{	return &m_mInvTM;									}
	inline vCtrl*			GetNextNode()					{	return (vCtrl*)bUNKN2;								} //(vCtrl*)((DWORD)this + 8 );

	enum	{	linkStatic	= 0, linkDynamic	= 1, linkPlayer	= 2,	linkAirShip		= 3,	};

public:
	DWORD			bUNKN0; //0x0000 
	DWORD			bUNKN1; //0x0004 
	DWORD			bUNKN2; //0x0008 

	DWORD			m_dwFlags;
private:
	DWORD			m_dwLinkLevel;
	D3DXVECTOR3		m_vScale;
	float			m_fAngle;
	float			m_fAngX;
	float			m_fAngZ;

protected:
	D3DXMATRIX		m_matTrans;
	D3DXMATRIX		m_matScale;
	D3DXMATRIX		m_matRotation;
	D3DXMATRIX		m_matWorld;

public:
	BBOX			m_OBB;

	D3DXVECTOR3		m_vPos;	
	vWorld*			m_pWorld;
	DWORD			m_dwType;
	DWORD			m_dwIndex;
	void*			m_pModel;

	DWORD			m_dwObjAryIdx;

	void*			m_pAIInterface;
	DWORD			m_dwAIInterface;
	DWORD			m_dwAIInterfaceState;

	DWORD			m_dwPatrolIndex;
	int				m_nPatrolIndexCount;
	BYTE            m_bPatrolCycle: 1;
	BYTE            m_bPatrolReverse: 1;
	D3DXVECTOR3		m_vRemoval;
	D3DXVECTOR3		m_vLink;

	DWORD			xUnkW01;
	int				m_nLayer;

	DWORD			m_objid;
	void*			m_pIAObjLink;
	D3DXMATRIX		m_mInvTM;
	LONG			m_lRespawn;
	int	            m_nRespawnType;
	int				m_nOldCenter;
};

inline bool IsValidObj( vCtrl* pObj ) 
{ 
	return pObj && ( pObj->IsDelete() == FALSE ); 
}

inline bool IsInvalidObj( vCtrl* pObj ) 
{ 
	return !IsValidObj( pObj ); 
}

class vCommonCtrl : public vCtrl
{
public:
	DWORD		m_dwMoverId;
	vCtrlElem	m_CtrlElem;//@0x218

	BOOL		 m_bTrap;
	BOOL		 m_bAniPlay;
	BOOL		 m_bAlpha;
	int			 m_nBlendFactorLocal;
	DWORD		 m_dwTrapProcessTime;

	float		 m_fFrameCount;
	BOOL		 m_bAniDelay;
	DWORD		 m_dwAniDelay;

public:
	void* m_pSkillProp;
	void* m_pAddSkillProp;

	DWORD	m_idAttacker;
	BOOL	m_bControl;
	int		m_nCount;
	int		m_nEvent;
	DWORD	m_tmStart;
	int		m_nLife;
	BOOL	m_bAction;
	DWORD   m_dwCtrlReadyTime;

	DWORD		m_dwDelete;
	__int64		m_nExpBox;
	u_long      m_idExpPlayer;		
};

vCtrl*	CreateObj( DWORD dwObjType, DWORD dwObjIndex, BOOL bInitProp = TRUE );

