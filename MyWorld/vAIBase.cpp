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
// // pObjCenter�� �߽����� nRangeMeter�ݰ泻�� �����³ѵ��� ������� �ɸ��� �� ���/
// // nJobCond : �ش� ������ ������. �����˻� ����.
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
// 	float fRadius = (float)( nRangeMeter * nRangeMeter );	// �Ÿ� 
// 
// 	FOR_LINKMAP( pObjCenter->GetWorld(), vPos, pObj, nRangeMeter, CObj::linkPlayer, GetMover()->GetLayer() )
// 	{
// 		ASSERT( pObj->GetType() == OT_MOVER && ((CMover *)pObj)->IsPlayer() );
// 		pTarget = (CMover *)pObj;
// 
// 		// ���� ������ �ƴ϶�� �� �����ϴ�.
// 		nAble = 0;
// 		// ���� �����̶�� ������ ��ġ�ϴ� �� �����ϴ�.
// 		if( bCondScan == TRUE && pTarget->IsLive() ) 
// 		{
// 			// 1. ���� ���� üũ    
// 			if( nJobCond == 0 )
// 				nAble++;
// 			else if( nJobCond == JOB_ALL || pTarget->GetJob() == nJobCond )		// JOB_ALL : �������
// 				nAble++;
// 			// 2. ������ ���� üũ  
// 			if( dwItem == 0 )
// 				nAble++;
// 			else if( pTarget->GetItemNum( dwItem ) != 0 )	
// 				nAble++;
// 			// 3. ����Ʈ ���� üũ 
// 			if( dwQuest == 0 )
// 				nAble++;
// 			else if( pTarget->GetQuest( dwQuest ) != NULL )
// 				nAble++;	
// 			//4. ī�� ���� üũ  
// 			if( nChao == 0 )
// 				nAble++;
// 			else
// 			{
// 				// 100 = ī������, 101 = ��ī��
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
// 			// ����� ������ ����			
// 			// ������� �����÷��̾ ����, ������� �����÷��̾�� ���� - 1. true true  2. false false
// 
// #ifdef __JHMA_VER_8_6     // 8�� ������Ͱ� �������������� ���ݰ����ϰ���   World
// 			if( bGuard || bFlyMob == pTarget->IsFly() || bFlyMob == FALSE  )		
// #else	// __VER >= 8  
// 			if( bGuard || bFlyMob == pTarget->IsFly() )		
// #endif	// __VER >= 8  
// 			{
// 				vDist = pTarget->GetPos() - vPos;				
// 				if( D3DXVec3LengthSq( &vDist ) < fRadius )	// �� ��ü���� �Ÿ��� ���� �̳��̸� 
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
// // �ݰ泻���� ���� ���ѳ�(������)�� ���.
// CMover* CAIInterface::ScanTargetStrong( CObj* pObjCenter, FLOAT fRangeMeter  )
// {
// 	CObj *pObj;
// 	CObj *pObjMax = NULL;	// ������ ������.
// 	D3DXVECTOR3 vPos = pObjCenter->GetPos();
// 	D3DXVECTOR3 vDist;
// 
// 	// ���� 
// 	FLOAT fRadius = fRangeMeter * fRangeMeter;
// 
// 	FOR_LINKMAP( pObjCenter->GetWorld(), vPos, pObj, (int)( fRangeMeter / MPU ), CObj::linkPlayer, GetMover()->GetLayer() )
// 	{
// 		vDist = pObj->GetPos() - vPos;	// ����ǥ�� ����
// 		float fDistSq = D3DXVec3LengthSq( &vDist );		// �ο�����Ʈ���� �Ÿ�Sq
// 		if( fDistSq < fRadius )	
// 		{
// 			if(  !( ((CMover*)pObj)->IsMode( TRANSPARENT_MODE ) ) )
// 			{
// 				if( pObjMax )
// 				{
// 					if( ((CMover *)pObj)->GetLevel() > ((CMover *)pObjMax)->GetLevel() )		// �� ����� ã�Ҵ�.
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
// 					if( ((CUser *)pMover)->m_nOverHeal > 0 )		// ���������� ã�Ҵ�.
// 						return pMover;
// 			}
// 		}
// 	}
// 	END_LINKMAP;
// 
// 	return nullptr;
// }