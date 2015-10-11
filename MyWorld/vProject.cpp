#include "stdafx.h"
#include "vProject.h"



//////////////////////////////////////////////////////////////////////////
//=> Injecting 'n stuff

void vProject::Inject()
{
	m_pJob = *(JOB**)0x00786398;
	m_pExpCharacter = (EXPCHARACTER*)0x00788BB8;
}


static const Address addrPrj	= 0x00783768;

//////////////////////////////////////////////////////////////////////////
//=> Functions

MoverProp* vProject::GetMoverProp( int nProp )
{
	if( nProp < 0 || nProp >= GetMoverPropSize() )
		return nullptr;

	return *(MoverProp**)(this + 0x194) + (0x6D0 * nProp);
}


vObjProp* vProject::GetProps( int nType, int nIndex )
{
	switch( nType )
	{
// 	case OT_CTRL:	return m_aPropCtrl.GetAt( nIndex ); 
// 	case OT_ITEM:	return m_aPropItem.GetAt( nIndex ); 
	case OT_MOVER:	return GetMoverProp( nIndex ); 
	}
	return nullptr;
}

JobProp* vProject::GetJobProp( int nIndex )
{
	if( nIndex < 0 || nIndex >= MAX_JOB )
	{
		Log(LOG_ERROR, "%s : nIndex too high! ( %d ) ", __FUNCTION__, nIndex );
		__debugbreak();
		return nullptr;
	}
	return (JobProp*)((DWORD)this + (100 * nIndex) + 684);
}

vItemProp* vProject::GetSkillProp(int nId)
{
	static const Address addrCall = 0x0041A520;

	vItemProp* pItem = nullptr;
	__asm
	{
		push nId
		mov ecx, addrPrj

		call addrCall
		mov pItem, eax
	}

	return pItem;
}


vMover* vProject::GetMover(OBJID idMover)
{
	static const Address addrCall = 0x005B7E80;

	vMover* pMover = nullptr;

	__asm
	{
		push idMover
		mov ecx, addrPrj

		call addrCall
		mov pMover, eax
	}
	return pMover;
}

int vProject::GetDefineNumber(char* szDefine)
{
	static const Address addCall = 0x006692F0;

	int nRetVal = 0;
	__asm
	{
		push szDefine

		call addCall
		mov nRetVal, eax
	}
	return nRetVal;
}

char* vProject::GetText(int nId)
{
	static const Address addrCall = 0x005C6520;

	char* szOut = nullptr;
	__asm
	{
		push nId

		mov ecx, addrPrj
		call addrCall
		mov szOut, eax
	}

	return szOut;
}


CHAO_PROPENSITY vProject::GetPropensityPenalty( DWORD dwPropensity )
{
	static const Address addrCall = 0x004E7B20;
	CHAO_PROPENSITY _bRet;
	__asm
	{
		push	dwPropensity;

		mov		ecx, addrPrj;
		call	addrCall;
		mov		_bRet, eax;
	}
	return _bRet;
}

