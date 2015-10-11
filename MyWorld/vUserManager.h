#pragma once
#include "vUser.h"

static const Address addrUserMng	= 0x00869D54;

static long GetCCU()	{ return *(long*)(addrUserMng + 4);	 }


//////////////////////////////////////////////////////////////////////////
//=> Forward declaration's

class vCtrl;
class vMover;
class vUser;

class vUserManager
{
public:
	void Inject();
	void RemoveAllUsers();

	
	inline	bool IsValid(vMover* pMover);

	DWORD		GetUserId(char* szName);
	vUser*		GetUserById(DWORD dwId);
	char*		GetPlayerString( DWORD dwId );

	void	DestroyUser(vUser* pUser);
	void	AddWorldCreateSfxObj( DWORD dwSfxObj, float x, float y, float z, BOOL bFlag, DWORD dwWorldId );
	void	AddCreateSfxObj(vCtrl* pCtrl, DWORD dwSfxObj, float x = 0, float y = 0, float z = 0, BOOL bFlag = FALSE);
	void	AddPushPower(vMover* pMover, float x, float y, float z, float fAngle, float fPushAngle, float fPower);
	void	AddDamage( vMover* pMover, DWORD objidAttacker, DWORD dwHit, DWORD dwAtkFlags, DWORD dwAdd = 0 );
	void	AddSetPointParam( vMover* pMover, int nDstParam, int nValue );
	void	AddSetDestParam( vMover* pMover, int nDstParameter, int nAdjParameterValue, int nChgParameterValue);
	void	AddResetDestParamSync( vMover* pMover, int nDstParameter,int nAdjParameterValue, int nParameterValue );
	void	AddResetDestParam( vMover* pMover, int nDstParameter, int nAdjParameterValue );
	void	AddSetStun( vMover* pMover, int nMaxTime );

public:
	tbb::concurrent_hash_map<DWORD,	vUser*>	m_mapPlayers;
	tbb::concurrent_hash_map<DWORD, vUser*>	m_mapGms;
};

