#pragma once



class vProperties
{
public:
	void Inject();


	void ModifyDropRate(DWORD dwGoldMainProb, DWORD dwGoldMin, DWORD dwGoldMax, DWORD dwMainProb, DWORD dwItemCountMin, DWORD dwItemCountMax );


private:
	CLuaBase	m_pLua;

public:

	float			m_fMonsterExp;
	float			m_fItemDrop;
	float			m_fMonsterHit;
	float			m_fGoldDrop;
	float			m_fPetSpeed;
	bool			m_bPartyLinkShare;

	EXPCHARACTER*	m_aExpCharacter;
	JOB*			m_aJob;
};

void vMonsterDropLoad();