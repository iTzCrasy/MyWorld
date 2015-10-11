#pragma once
#include "vCtrl.h"
#include "vMover.h"
#include "vUser.h"

static const Address addrAIBase = 0x0072E754;


class AIBase;
class vCtrl;
class vMover;


struct AIMSG
{
	DWORD dwMessage;
	DWORD dwParam1;
	DWORD dwParam2;
};

typedef BOOL (AIBase::*FUNCAISTATE)( const AIMSG & );


struct STATEMAP_ENTRIES
{
	DWORD dwAIStateId;
	FUNCAISTATE pStateFunc;
};

struct STATEMAP
{
	STATEMAP* lpBaseStateMap;
	STATEMAP_ENTRIES* lpStateMapEntries;
};



#define BeginAIHandler() if( 0 ) { 
#define OnMessage( x ) return TRUE; } else if( msg.dwMessage == x )	{
#define EndAIHandler() return TRUE; }

#define BEGIN_AISTATE_MAP( theClass, baseClass ) \
	const STATEMAP* theClass::GetStateMap() const  \
{ return (STATEMAP*)&theClass::stateMap; } \
	const STATEMAP theClass::stateMap = \
{ (STATEMAP*)&baseClass::stateMap, (STATEMAP_ENTRIES*)&theClass::stateMapEntries[0] }; \
	const STATEMAP_ENTRIES theClass::stateMapEntries[] = { \


#define ON_STATE( id, pStateFunc ) id, (FUNCAISTATE)pStateFunc, 

#define DECLARE_AISTATE() \
	static const STATEMAP_ENTRIES stateMapEntries[]; \
	static const STATEMAP stateMap; \
	virtual const STATEMAP* GetStateMap() const; 

#define END_AISTATE_MAP() 0, nullptr };

////////////////////////////////////////////////////////////////////////////
//0064D338 //  	// ScanTargetNext 0064C492

class vAIBase
{
	FUNCAISTATE GetAIStateFunc( DWORD dwState );

protected:
	std::queue< AIMSG >	m_MsgQueue;
	FUNCAISTATE			m_pStateFunc;
	vCtrl*				m_pObj;
	DWORD				m_uParty;
	 
	//56 b
public:
//	DECLARE_AISTATE()

// 	vAIBase();
// 	vAIBase( vCtrl* pObj );
//  	virtual	~vAIBase();
//  
// 	virtual void	RouteMessage();
// 	virtual void	SendAIMsg( DWORD dwMessage, DWORD dwParam1 = 0, DWORD dwParam2 = 0 );
// 	virtual void	PostAIMsg( DWORD dwMessage, DWORD dwParam1 = 0, DWORD dwParam2 = 0 );
// 	virtual void	InitAI()					{ }
// 	virtual	BOOL	IsReturnToBegin( void )		{	return FALSE;	}

protected:
 	inline vMover* GetMover() {		return (vMover*)m_pObj;			} 
 	inline vWorld* GetWorld() {		return m_pObj->GetWorld();		}

// 
// 	vMover* ScanTarget( vCtrl* pObjCenter, int nRangeMeter = 5, int nJobCond = 0, DWORD dwQuest = 0, DWORD dwItem = 0, int nChao = 0 );
// 	vMover* ScanTargetStrong( vCtrl* pObjCenter, FLOAT fRangeMeter );
// 	vMover* ScanTargetOverHealer( vCtrl* pObjCenter, FLOAT fRangeMeter  );
 	//vMover*	ScanTargetNext( vCtrl* pObjCenter, int nRange,  DWORD dwIdTarget, DWORD uParty );
	
};
