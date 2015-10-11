#pragma once

#define	MAX_PTMEMBER_SIZE	8
#define MAX_PARTYMODE 5

typedef	struct	_PartyMember
{
	u_long	m_uPlayerId;
	time_t	m_tTime;
	BOOL	m_bRemove;

	D3DXVECTOR3	m_vPos;

	_PartyMember()
	{
		m_uPlayerId	= 0;
		m_tTime = _time64(nullptr);
		m_bRemove = FALSE;
	}

}	PartyMember,	*PPartyMember;

class vParty
{
public:
	int		FindMember( idPlayer uPlayerId );
	bool	NewMember( idPlayer uPlayerId );
	bool	DeleteMember( idPlayer uPlayerId );
	void	ChangeLeader( idPlayer uLeaderId );
	void	SwapPartyMember( byte first, byte Second );
	void	SetPartyMode( int nMode, int nSkillTime, int nCachMode );
	


	inline  int		GetPartyModeTime( int nMode )		{ return m_nModeTime[nMode];	}
	inline	bool	IsMember( idPlayer uPlayerId )		{ return FindMember( uPlayerId ) >= 0;	}
	inline	bool	IsLeader( idPlayer uPlayerId )		{ return m_pMember[0].m_uPlayerId == uPlayerId; }

public: //size: 332
	
	int			m_nKindTroup;	//4
	u_long		m_uPartyId;		//8
	char		m_szParty[33];	// 12
	byte		m_bUnknw[3];

	PartyMember m_pMember[MAX_PTMEMBER_SIZE];

	int			m_nSizeofMember; //68
	long		m_nLevel;
	long		m_nPoint;
	long		m_nExp;
	int			m_nTroupeShareItem;
	int			m_nTroupsShareExp;
	int			m_nReferens;
	int			m_nModeTime[MAX_PARTYMODE];
	int			m_nGetItemPlayerId;
	u_long		m_idDuelParty;
	DWORD		m_dwWorldId;
};

