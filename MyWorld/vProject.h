#pragma once
#include "vCtrl.h"
#include "vMover.h"
#include "vEvents.h"


//=> Public cast's
static DWORD GetIDofMulti(){ return *(DWORD*)0x007831C8; }


//=> Forward declarations

class vCtrl;
class vMover;
class vUser;

class vProject
{
public:

	void		Inject();


	vMover*		GetMover(DWORD idMover);
	vItemProp*	GetSkillProp(int nId);
	int			GetDefineNumber(char* szDefine);
	char*		GetText(int nId);

	MoverProp*			GetMoverProp( int nProp );
	vObjProp*			GetProps( int nType, int nIndex );
	CHAO_PROPENSITY		GetPropensityPenalty( DWORD dwPropensity );
	JobProp*	GetJobProp( int nIndex );

public:
	JOB*			m_pJob;
	EXPCHARACTER*	m_pExpCharacter;

	GET_ACCESSOR			( int,		MoverPropSize,			0x190		);
	GET_SET_ACCESSOR_GLOBAL	( float,	MonsterHitpointRate,	0x008450DC	);
};

