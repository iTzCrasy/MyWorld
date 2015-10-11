#include "stdafx.h"
#include "vCtrl.h"
#include "vAIBase.h"

// BEGIN_AISTATE_MAP( vAIBase, vAIBase )
// END_AISTATE_MAP()

// vAIBase::vAIBase()
// {
// 	m_pObj = nullptr;
// 	m_pStateFunc = nullptr;
// 	m_uParty = 0;
// }

// vAIBase::vAIBase( vCtrl* pObj )
// {
// 	m_pObj = pObj;
// 	m_pStateFunc = nullptr;
// 	m_uParty = 0;
// }
// 
// vAIBase::~vAIBase(void)
// {
// 
// }
// 
// FUNCAISTATE vAIBase::GetAIStateFunc( DWORD dwState)
// {
// 	const STATEMAP* lpCurrentStateMap = GetStateMap();
// 	const STATEMAP_ENTRIES* lpEntries = lpCurrentStateMap->lpStateMapEntries;
// 
// 	while( lpCurrentStateMap->lpBaseStateMap->lpStateMapEntries != lpEntries )
// 	{
// 		int i = 0;
// 		while(  lpEntries[ i ].pStateFunc )
// 		{
// 			if( lpEntries[ i ].dwAIStateId == dwState )
// 				return lpEntries[ i ].pStateFunc;
// 			i++;
// 		}
// 
// 		lpCurrentStateMap = lpCurrentStateMap->lpBaseStateMap;
// 		lpEntries = lpCurrentStateMap->lpStateMapEntries;
// 	}
// 	return nullptr;
// }
// 
// 
// void vAIBase::RouteMessage()
// {
// 	AIMSG msg;
// 
// 	while( !m_MsgQueue.empty() )
// 	{
// 		msg	= m_MsgQueue.front();
// 		m_MsgQueue.pop();
// 		if( msg.dwMessage == AIMSG_SETSTATE )
// 		{
// 			msg.dwMessage	= AIMSG_INIT;
// 			m_pStateFunc	= GetAIStateFunc( msg.dwParam1 );
// 		}
// 		if( m_pStateFunc )
// 			( this->*( m_pStateFunc ) ) ( msg );
// 	}
// 	if( m_pStateFunc )
// 	{
// 		msg.dwMessage	= AIMSG_PROCESS;
// 		msg.dwParam1	= 0;
// 		msg.dwParam2	= 0;
// 		( this->*( m_pStateFunc ) ) ( msg );
// 	}
// }
// 
// void vAIBase::SendAIMsg( DWORD dwMessage, DWORD dwParam1, DWORD dwParam2 )
// {
// 	AIMSG msg;
// 	msg.dwMessage	= dwMessage;
// 	msg.dwParam1	= dwParam1;
// 	msg.dwParam2	= dwParam2;
// 	if( dwMessage == AIMSG_SETSTATE )
// 	{
// 		msg.dwMessage	= AIMSG_INIT;
// 		m_pStateFunc	= GetAIStateFunc( dwParam1 );
// 	}
// 	if( m_pStateFunc )
// 		( this->*( m_pStateFunc ) ) ( msg );
// }
// 
// void vAIBase::PostAIMsg( DWORD dwMessage, DWORD dwParam1, DWORD dwParam2 )
// {
// 	switch( dwMessage )
// 	{
// 	case AIMSG_ARRIVAL:
// 		{
// 			AIMSG msg;
// 			msg.dwMessage	= dwMessage;
// 			msg.dwParam1	= dwParam1;
// 			msg.dwParam2	= dwParam2;
// 			m_MsgQueue.push( msg );
// 			break;
// 		}
// 	default:	SendAIMsg( dwMessage, dwParam1, dwParam2 );	break;
// 	}
// }
// 
// 
// vMover* vAIBase::ScanTargetNext( vCtrl* pObjCenter, int nRange, OBJID dwIdTarget, DWORD uParty )
// {
// 	if( uParty == 0 || nRange <= 0 || GetMover()->GetProperty()->dwClass == RANK_GUARD )
// 		return NULL;
// 
// 	vCtrl* pObj;
// 	D3DXVECTOR3 vPos = pObjCenter->GetPos();
// 	D3DXVECTOR3 vDist;
// 	vMover *pTarget	= NULL;
// 
// 	BOOL bFlyMob	= GetMover()->IsFlyingNPC();
// 	float fRadius	= (float)( nRange * nRange );
// 
// 	FOR_LINKMAP( pObjCenter->GetWorld(), vPos, pObj, nRange, vCtrl::linkPlayer, GetMover()->GetLayer() )
// 	{
// 		pTarget	= (vMover*)pObj;
// 		if( pTarget->IsLive() && pTarget->GetId() != dwIdTarget ) 
// 		{
// 			if( bFlyMob == pTarget->IsFly() || bFlyMob == FALSE  )
// 			{
// 				vDist	= pTarget->GetPos() - vPos;				
// 				if( D3DXVec3LengthSq( &vDist ) < fRadius && pTarget->m_idparty == uParty )
// 				{
// 					if( pTarget->IsMode( TRANSPARENT_MODE ) == FALSE )
// 						if( pTarget->HasBuffByIk3( IK3_TEXT_DISGUISE ) == FALSE )
// 							return pTarget;
// 				}
// 			}
// 		}
// 	}
// 	END_LINKMAP
// 		return NULL;
// }

// 
// // pObjCenter를 중심으로 nRangeMeter반경내에 들어오는넘들중 가장먼저 걸리는 넘 골라냄/
// // nJobCond : 해당 직업만 감시함. 직업검사 안함.
// CMover* CAIInterface::ScanTarget( CObj* pObjCenter, int nRangeMeter, int nJobCond, DWORD dwQuest, DWORD dwItem, int nChao )
// {
// 	CObj* pObj;
// 	D3DXVECTOR3 vPos = pObjCenter->GetPos();
// 	D3DXVECTOR3 vDist;
// 	CMover *pTarget = NULL;
// 	int nAble = 0;
// 	BOOL bCondScan = FALSE;
// 	if( nJobCond || dwQuest || dwItem || nChao )
// 		bCondScan = TRUE;
// 
// 	BOOL bGuard = ( GetMover()->GetProp()->dwClass == RANK_GUARD );
// 	BOOL bFlyMob = GetMover()->IsFlyingNPC();
// 
// 	float fRadius = (float)( nRangeMeter * nRangeMeter );	// 거리 
// 
// 	FOR_LINKMAP( pObjCenter->GetWorld(), vPos, pObj, nRangeMeter, CObj::linkPlayer, GetMover()->GetLayer() )
// 	{
// 		ASSERT( pObj->GetType() == OT_MOVER && ((CMover *)pObj)->IsPlayer() );
// 		pTarget = (CMover *)pObj;
// 
// 		// 조건 스켄이 아니라면 늘 가능하다.
// 		nAble = 0;
// 		// 조건 스켄이라면 프랍과 일치하는 놈만 가능하다.
// 		if( bCondScan == TRUE && pTarget->IsLive() ) 
// 		{
// 			// 1. 직업 조건 체크    
// 			if( nJobCond == 0 )
// 				nAble++;
// 			else if( nJobCond == JOB_ALL || pTarget->GetJob() == nJobCond )		// JOB_ALL : 모든직업
// 				nAble++;
// 			// 2. 아이템 조건 체크  
// 			if( dwItem == 0 )
// 				nAble++;
// 			else if( pTarget->GetItemNum( dwItem ) != 0 )	
// 				nAble++;
// 			// 3. 퀘스트 조건 체크 
// 			if( dwQuest == 0 )
// 				nAble++;
// 			else if( pTarget->GetQuest( dwQuest ) != NULL )
// 				nAble++;	
// 			//4. 카오 조건 체크  
// 			if( nChao == 0 )
// 				nAble++;
// 			else
// 			{
// 				// 100 = 카오유저, 101 = 비카오
// 				if( nChao == 100 )
// 				{
// #if __VER >= 8 // __S8_PK
// 					if( pTarget->IsChaotic() )
// #else // __VER >= 8 // __S8_PK
// 					if( pTarget->IsGuardReactionChao() )
// #endif // __VER >= 8 // __S8_PK
// 						nAble++;
// 				}
// 				else if( nChao == 101 )
// 				{
// #if __VER >= 8 // __S8_PK
// 					if( !pTarget->IsChaotic() )
// #else // __VER >= 8 // __S8_PK
// 					if( pTarget->IsGuardReactionNormal() )
// #endif // __VER >= 8 // __S8_PK
// 						nAble++;
// 				}
// 			}
// 		}
// 		if( nAble == 4 )
// 		{
// 			// 가드는 무조건 공격			
// 			// 비행몹은 비행플레이어만 공격, 지상몹은 지상플레이어만만 공격 - 1. true true  2. false false
// 
// #ifdef __JHMA_VER_8_6     // 8차 지상몬스터가 저공비행유저를 공격가능하게함   World
// 			if( bGuard || bFlyMob == pTarget->IsFly() || bFlyMob == FALSE  )		
// #else	// __VER >= 8  
// 			if( bGuard || bFlyMob == pTarget->IsFly() )		
// #endif	// __VER >= 8  
// 			{
// 				vDist = pTarget->GetPos() - vPos;				
// 				if( D3DXVec3LengthSq( &vDist ) < fRadius )	// 두 객체간의 거리가 범위 이내이면 
// 				{
// 					if( pTarget->IsMode( TRANSPARENT_MODE ) == FALSE )
// 						if( pTarget->HasBuffByIk3( IK3_TEXT_DISGUISE ) == FALSE )
// 							return pTarget;
// 				}
// 			}
// 		}
// 	}
// 	END_LINKMAP
// 		return NULL;
// }
// 
// // 반경내에서 가장 강한넘(레벨로)을 골라냄.
// CMover* CAIInterface::ScanTargetStrong( CObj* pObjCenter, FLOAT fRangeMeter  )
// {
// 	CObj *pObj;
// 	CObj *pObjMax = NULL;	// 가장쎈넘 포인터.
// 	D3DXVECTOR3 vPos = pObjCenter->GetPos();
// 	D3DXVECTOR3 vDist;
// 
// 	// 지름 
// 	FLOAT fRadius = fRangeMeter * fRangeMeter;
// 
// 	FOR_LINKMAP( pObjCenter->GetWorld(), vPos, pObj, (int)( fRangeMeter / MPU ), CObj::linkPlayer, GetMover()->GetLayer() )
// 	{
// 		vDist = pObj->GetPos() - vPos;	// 두좌표간 벡터
// 		float fDistSq = D3DXVec3LengthSq( &vDist );		// 두오브젝트간의 거리Sq
// 		if( fDistSq < fRadius )	
// 		{
// 			if(  !( ((CMover*)pObj)->IsMode( TRANSPARENT_MODE ) ) )
// 			{
// 				if( pObjMax )
// 				{
// 					if( ((CMover *)pObj)->GetLevel() > ((CMover *)pObjMax)->GetLevel() )		// 더 쎈넘을 찾았다.
// 						pObjMax = pObj;
// 				} else
// 					pObjMax = pObj;
// 
// 			}
// 		}
// 	}
// 	END_LINKMAP
// 
// 		return (CMover *)pObjMax;
// }
// 
// vMover* vAIBase::ScanTargetOverHealer( vCtrl* pObjCenter, float fRangeMeter  )
// {
// 	vCtrl* pObj;
// 	D3DXVECTOR3 vPos = pObjCenter->GetPos();
// 	D3DXVECTOR3 vDist;
//  
// 	float fRadius = fRangeMeter * fRangeMeter;
// 
// 	FOR_LINKMAP( pObjCenter->GetWorld(), vPos, pObj, (int)( fRangeMeter / MPU ), CObj::linkPlayer, GetMover()->GetLayer() )
// 	{
// 		vDist = pObj->GetPos() - vPos;
// 		float fDistSq = D3DXVec3LengthSq( &vDist );
// 		if( fDistSq < fRadius )	
// 		{
// 			if(  !( ((vMover*)pObj)->IsMode( TRANSPARENT_MODE ) ) )
// 			{
// 				vMover *pMover = (CMover *)pObj;
// 
// 				if( pMover->IsPlayer() )
// 					if( ((CUser *)pMover)->m_nOverHeal > 0 )		// 오버힐러를 찾았다.
// 						return pMover;
// 			}
// 		}
// 	}
// 	END_LINKMAP;
// 
// 	return nullptr;
// }