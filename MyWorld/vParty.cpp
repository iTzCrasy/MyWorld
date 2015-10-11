#include "stdafx.h"
#include "vParty.h"


int vParty::FindMember( idPlayer uPlayerId )
{
	for( int i = 0; i < (int)m_nSizeofMember; i++)
	{
		if(m_pMember[i].m_uPlayerId == uPlayerId)
			return i;
	}
	return -1;
}


bool vParty::NewMember( idPlayer uPlayerId )
{
	if( IsMember( uPlayerId ) == false && m_nSizeofMember < MAX_PTMEMBER_SIZE )
	{
		m_pMember[m_nSizeofMember].m_uPlayerId = uPlayerId;
		m_pMember[m_nSizeofMember].m_bRemove	= FALSE;
		m_nSizeofMember++;
		return true;
	}
	return false;
}

bool vParty::DeleteMember( idPlayer uPlayerId )
{
	char Findid = FindMember( uPlayerId );
	if( Findid >= 0)
	{
		for( int i = Findid ; i < m_nSizeofMember-1 ; i++ )
			memcpy( &m_pMember[i], &m_pMember[i+1], sizeof(PartyMember) );

		m_nSizeofMember--;

		//CInstanceDungeonParty::GetInstance()->SetPartyLeaveTime( uPlayerId );

		return true;
	}
	return false;
}

void vParty::ChangeLeader( idPlayer uLeaderId )
{
	int changeIndex = FindMember( uLeaderId );
	SwapPartyMember( 0, changeIndex );
}

void vParty::SwapPartyMember( byte bFirst, byte bSecond )
{
	PartyMember* pTemp = &m_pMember[bFirst];

	m_pMember[bFirst] = m_pMember[bSecond];
	m_pMember[bSecond] = *pTemp;
}

void vParty::SetPartyMode( int nMode, int nSkillTime, int nCachMode )
{
	if( nCachMode == 1)
		m_nModeTime[nMode] += nSkillTime;	
	else
		m_nModeTime[nMode] = nSkillTime;	
}