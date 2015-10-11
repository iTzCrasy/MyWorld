#include "stdafx.h"
#include "vAiTest.h"


#define		EPT_READY			0
#define		EPT_MOVING			1
#define		EPT_ATTACKING		2
#define		EPT_ATTACK_END		3
#define		EPT_TRACKING		4

// 
// enum
// {
// 	STATE_INIT = 1,
// 	STATE_APPEAR,
// 	STATE_IDLE,
// 	STATE_RAGE,
// 	STATE_SUPER_RAGE
// };
// 
// BEGIN_AISTATE_MAP( vAiTest, vAIBase )
// 
// 	ON_STATE( STATE_INIT,		StateInit   )
// 	ON_STATE( STATE_IDLE,		StateIdle   )
// 	ON_STATE( STATE_RAGE,		StateRage   )
// 	ON_STATE( STATE_SUPER_RAGE, StateRage   )
// 
// END_AISTATE_MAP()


// vAiTest::vAiTest()
// {
// 	m_nEvent = EPT_READY;
// }
// 
// 
// vAiTest::~vAiTest()
// {
// }
// 
// void vAiTest::InitAI()
// {
// 	PostAIMsg( AIMSG_SETSTATE, STATE_RAGE, NULL_ID );
// }
// 
// 
// BOOL vAiTest::StateIdle( const AIMSG & msg )
// {
// 	BeginAIHandler( )
// 		OnMessage( AIMSG_INIT )
// 			SendAIMsg( AIMSG_SETSTATE, STATE_RAGE, NULL_ID );
// 		OnMessage( AIMSG_PROCESS ) 
// 			MoveProcessIdle();
// 		OnMessage( AIMSG_DAMAGE ) 
// 			SendAIMsg( AIMSG_SETSTATE, STATE_RAGE, NULL_ID );
// 		OnMessage( AIMSG_DIE ) 
// 			SendAIMsg( AIMSG_EXIT );
// 		OnMessage( AIMSG_COLLISION )
// 		OnMessage( AIMSG_ARRIVAL )
// 		OnMessage( AIMSG_EXIT )	
// 
// 	EndAIHandler( );
// }
// 
// 
// BOOL vAiTest::MoveProcessRage()
// {
// 	vMover* pMover = GetMover();
// 	vWorld* pWorld = GetWorld();
// 	CModelObject *pModel = (CModelObject *)pMover->GetModel();
// 	vMover * pTarget = NULL;
// 	
// 	if( m_bEventFlag[0] == FALSE )
// 	{
// 		pTarget	= ScanTarget( pMover, 60, JOB_ALL );
// 
// 		if( IsValidObj(pTarget) )
// 		{
// 			m_bEventFlag[1] = TRUE;
// 			m_bEventFlag[0] = TRUE;
// 
// 			g_pClient.SendCaption( g_prj.GetText(TID_GAME_BOSS_KRR_MSG_01), pTarget->GetWorld()->GetID() );	
// 
// 			m_idEventTarget	= pTarget->GetId();
// 		}
// 	}
// 
// 	if( m_bEventFlag[1] == TRUE && m_nEventCount )
// 	{
// 		if( xRandom(20) <= 0 )
// 		{
// 			m_nEventCount--;
// 
// 			CMover* pEventTarget	= prj.GetMover( m_idEventTarget );
// 			if( IsValidObj( pEventTarget ) )
// 			{
// 				D3DXVECTOR3 vPos	= pEventTarget->GetPos();
// 				
// 				vPos.x += ( xRandomF( 20.0f ) + -10.0f );
// 				vPos.z += ( xRandomF( 20.0f ) + -10.0f );
// 				
// 				g_pUserMng.AddCreateSfxObj( pEventTarget, XI_SKILL_ELE_MULTI_METEOSHOWER02, vPos.x, vPos.y, vPos.z );
// 				pMover->GetWorld()->SendDamageAround( &vPos, AF_GENERIC, pMover, OBJTYPE_PLAYER, II_WEA_MOB_MONSTER4_ATK2, 2.0f );
// 			}
// 		}
// 		if( m_nEventCount <= 0 )
// 			m_bEventFlag[1]	= FALSE;
// 	}
// 
// 	if( m_nEvent == EPT_READY )
// 	{
// 		if( pMover->m_pActMover->m_bGround == 1 && pMover->m_pActMover->GetActionState() != OBJSTA_APPEAR )
// 			pMover->SendActMsg( OBJMSG_APPEAR );
// 
// 		if( ++m_nAppearCnt >= PROCESS_COUNT * 5 )
// 		{
// 			PostAIMsg( AIMSG_END_APPEAR );
// 			pMover->m_pActMover->ResetState( OBJSTA_ACTION_ALL );
// 			m_nAppearCnt = 0;
// 		}
// 	} 
// 	else if( m_nEvent == EPT_ATTACKING )
// 	{
// 
// 		BOOL bEnd = FALSE;
// 		if( pMover->m_dwMotion == MTI_STAND || pModel->IsEndFrame()	)
// 		{
// 			bEnd = TRUE;
// 		}
// 		if( timeGetTime() >= m_tmTimeOver + SEC(15) )
// 			bEnd = TRUE;
// 		if( bEnd )
// 		{
// 			m_nEvent = EPT_MOVING;
// 			m_tmReattack = timeGetTime();
// 			m_tmAddReattack = 2000;
// 			m_idTarget = NULL_ID;
// 		} 
// 	}
// 	else if( m_nEvent == EPT_ATTACK_END )
// 	{
// 		m_nEvent = EPT_MOVING;
// 		m_tmReattack = timeGetTime();
// 		m_tmAddReattack = 2000;
// 		m_idTarget = NULL_ID;
// 	} 
// 	else if( m_nEvent == EPT_TRACKING )
// 	{
// 		if( timeGetTime() >= m_tmTrace + 3000 )
// 		{
// 			m_nEvent = EPT_MOVING;
// 			m_idTarget = NULL;
// 			m_vTarget.x = m_vTarget.y = m_vTarget.z = 0;
// 		}
// 	} 
// 	else	
// 	{
// 
// 		if( timeGetTime() >= m_tmReattack + (2000 - m_tmAddReattack) )
// 		{
// 			FLOAT fRadius = pMover->GetRadiusXZ();
// 			FLOAT fRadiusSq = fRadius * fRadius;
// 
// 			if( m_idTarget == NULL_ID && (m_vTarget.x == 0 && m_vTarget.y == 0 && m_vTarget.z == 0) )
// 			{
// 				if( SelectTarget() == FALSE )
// 					return FALSE;
// 			}
// 
// 			D3DXVECTOR3	vTarget;
// 			FLOAT	fDistSq = 0;
// 			vMover *pTarget = NULL;
// 			if( m_idTarget != NULL_ID )
// 			{
// 				pTarget = g_prj.GetMover( m_idTarget );
// 				if( IsValidObj(pTarget) )
// 					vTarget = pTarget->GetPos();
// 				else
// 				{
// 					m_idTarget = NULL_ID;
// 					return FALSE;
// 				}
// 			} 
// 			else if( m_vTarget.x && m_vTarget.y && m_vTarget.z )
// 			{
// 				vTarget = m_vTarget;
// 			} 
// 			else
// 			{
// 				return FALSE;
// 			}
// 
// 			D3DXVECTOR3 vDist = vTarget - pMover->GetPos();
// 			fDistSq = D3DXVec3LengthSq( &vDist );		// ��ǥ���������� �Ÿ�.
// 			FLOAT fArrivalRange = fRadius;			// �󸶳� �����ؾ��ϴ°�? ����Ʈ�� ������ ����.
// 
// 			if( fDistSq < fRadiusSq * 32.0f )		// �ٰŸ���.
// 			{
// 				DWORD dwNum = xRandom( 100 );		// 0 ~ 99������ ����.
// 				
// 				if( dwNum <= 9 )
// 				{
// 					m_nAttackType = CAT_SUMMONS;	// �μ����� ����ġ�� - ����
// 					fArrivalRange = 0.0f;			// ������ ���̸�ŭ ��������.
// 				}
// 				else
// 				if( dwNum <= 30 )
// 				{
// 					m_nAttackType = CAT_DOUBLE_CRASH;	// �μ����� ����ġ�� - ����
// 					fArrivalRange = 10.0f;			// ������ ���̸�ŭ ��������.
// 				}
// 				else
// 				if( dwNum <= 100 )
// 				{
// 					m_nAttackType = CAT_NORMAL;		// �չ߷� ���.
// 					fArrivalRange = 7.0f;				// ���پ ��ƾ� �Ѵ�.
// 				}
// 			} 
// 			else
// 			{
// 				m_nAttackType = CAT_SUMMONS;		// ��û �ָ� �������ִ³��� ��ȯ.
// 				fArrivalRange = 0.0f;
// 			}
// 						
// 			m_tmTrace = timeGetTime();		// ���� ������ �ð�.
// 			m_nEvent = EPT_TRACKING;		// �����߰ݻ��� ��ȯ.
// 			pMover->CMD_SetMeleeAttack( m_idTarget, fArrivalRange );		// ���ݹݰ��� this�� ������ ũ�������� �����ϴ�.
// 		}
// 	}
// 
// 	return TRUE;
// }