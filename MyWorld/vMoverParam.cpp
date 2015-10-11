#include "stdafx.h"
#include "vClient.h"
#include "vUserManager.h"
#include "vMover.h"


extern vClient g_pClient;
extern vUserManager g_pUserMng;



int vMover::GetMaxOriginHitPoint( bool bOriginal )
{
	if( IsInvalidObj(this) )	
		return 0;

	if( IsPlayer() )
	{
		int nSta;
		if( bOriginal )
			nSta = m_nSta;
		else
			nSta = GetSta();

		JobProp* pProperty = g_prj.GetJobProp( GetJob() ); 
		float b = ( (pProperty->fFactorMaxHP * GetLevel() ) / 2.0f ) * ( ( GetLevel() + 1.0f ) / 4.0f ) * ( 1.0f + nSta / 50.0f ) + ( nSta * 10.0f );
		return (int)b + (int)80.0f;
	}
	else
	{
		MoverProp* pMoverProp = g_prj.GetMoverProp( GetIndex() );
		return int( pMoverProp->dwAddHp * g_prj.GetMonsterHitpointRate() * pMoverProp->m_fHitPoint_Rate ); 
	}

	return 0;
}

int vMover::GetMaxOriginFatiguePoint( bool bOriginal )
{
	int nSta, nStr, nDex;
	if( bOriginal )
	{
		nSta = m_nSta;
		nStr = m_nStr;
		nDex = m_nDex;
	}
	else
	{
		nSta = GetSta();
		nStr = GetStr();
		nDex = GetDex();
	}

	if( IsPlayer() )
	{
		JobProp* pProperty = g_prj.GetJobProp( GetJob() ); 

		float factor = pProperty->fFactorMaxFP;
		return (int)( (((GetLevel()*2.0f) + (nSta*6.0f))*factor) + (nSta*factor) );
	}
	return ( ( GetLevel() * 2 ) + ( nStr * 7 ) + ( nSta *2 ) + ( nDex * 4 ) );
}


int vMover::GetMaxOriginManaPoint( bool bOriginal )
{
	int nInt = 0;
	if( bOriginal )
		nInt = m_nInt;
	else
		nInt = GetInt();

	if( IsPlayer() )
	{
		JobProp* pProperty = g_prj.GetJobProp( GetJob() ); 
		float factor = pProperty->fFactorMaxMP;

		int nMaxMP = (int)( ((((GetLevel()*2.0f) + ( nInt*8.0f))*factor) + 22.0f)+( nInt*factor) );
		return nMaxMP;
	}
	return 	( ( GetLevel() * 2 ) + ( nInt * 8 ) + 22 );
}

int vMover::GetMaxFatiguePoint()
{
	int nResult = GetParam( DST_FP_MAX, GetMaxOriginFatiguePoint( false ) );
	float factor = 1.0f + ( (float)GetParam( DST_FP_MAX_RATE, 0 ) / 100.0f );

	nResult	= (int)( nResult * factor );

	if( nResult < 1 )
		nResult		= 1;

	return nResult; 
}

int vMover::GetMaxHitPoint()
{
	if( IsInvalidObj(this) )	
		return 0;

	float factor = 1.0f;
	int nResult = GetParam( DST_HP_MAX, GetMaxOriginHitPoint( false ) );
	int nFactor = GetParam( DST_HP_MAX_RATE, 0 );

	factor += (float)nFactor/(float)100;
	nResult	= (int)( nResult * factor );


	if( nResult < 1 )
		nResult		= 1;

	return nResult; 
}

int vMover::GetMaxManaPoint()
{
	float factor = 1.0f;
	int nResult = GetParam( DST_MP_MAX, GetMaxOriginManaPoint( false ) );
	int nFactor = GetParam( DST_MP_MAX_RATE, 0 );

	factor += (float)nFactor/(float)100;
	nResult	= (int)( nResult * factor );

	if( nResult < 1 )
		nResult	= 1;

	return nResult; 
}

void vMover::SetPointParam( int nDstParameter, int nValue, bool bTrans )
{
	int nMax = nValue;
	if( nValue < 0 )	
		nValue	= 0;

	bool bTransfer = bTrans;

	switch( nDstParameter )
	{
	case DST_HP:
		if( nValue > GetMaxHitPoint() || nMax == 999999999 )	
			nValue = GetMaxHitPoint();

		if( GetHitPoint() != nValue )
		{
			bTransfer = true;
			SetHitPoint( nValue );
		}
		break;
	case DST_MP:
		if( nValue > GetMaxManaPoint() || nMax == 999999999 )	
			nValue = GetMaxManaPoint();

		if( GetManaPoint() != nValue )
		{
			bTransfer	= true;
			m_nManaPoint = nValue;
		}
		break;
	case DST_FP:
		if( nValue > GetMaxFatiguePoint() || nMax == 999999999 )	
			nValue	= GetMaxFatiguePoint();

		if( GetFatiguePoint() != nValue )
		{
			bTransfer	= true;
			m_nFatiguePoint = nValue;
		}
		break;
	}
	if( bTransfer )
		g_pUserMng.AddSetPointParam( this, nDstParameter, nValue );
}

void vMover::SetDestParam( int nDstParameter, int nAdjParameterValue, int nChgParameterValue, bool bSend )
{
	bool fSuccess	= FALSE;

	if( (nDstParameter < 0 ) && ( nDstParameter != DST_ADJDEF_RATE && nDstParameter != DST_ADJDEF ) )
		return;

	switch( nDstParameter )
	{
	case DST_HP:
		{
			if( nAdjParameterValue == -1 )
				SetPointParam( nDstParameter, GetMaxHitPoint() );
			else
				SetPointParam( nDstParameter, GetHitPoint() + nAdjParameterValue );
		}
		return;
	case DST_MP:
		{
			if( nAdjParameterValue == -1 )
				SetPointParam( nDstParameter, GetMaxManaPoint() );
			else
				SetPointParam( nDstParameter, GetManaPoint() + nAdjParameterValue );
		}
		return;
	case DST_FP:
		{
			if( nAdjParameterValue == -1 )
				SetPointParam( nDstParameter, GetMaxFatiguePoint() );
			else
				SetPointParam( nDstParameter, GetFatiguePoint() + nAdjParameterValue );
		}
		return;

	case DST_GOLD:	
		Log( LOG_ERROR, "SetDestParam( DST_GOLD ) - [User:%s(%07d)], [Value:%d]", ((vUser*)(this))->GetName(), ((vUser*)(this))->m_idPlayer, nAdjParameterValue );
		return;

		if( AddGold( nAdjParameterValue ) == FALSE )	
			SetGold( 0 );
		return;

	case DST_RESIST_ALL:
		SetDestParam( DST_RESIST_ELECTRICITY,	nAdjParameterValue, nChgParameterValue, bSend );
		SetDestParam( DST_RESIST_FIRE,			nAdjParameterValue, nChgParameterValue, bSend );
		SetDestParam( DST_RESIST_WIND,			nAdjParameterValue, nChgParameterValue, bSend );
		SetDestParam( DST_RESIST_WATER,			nAdjParameterValue, nChgParameterValue, bSend );
		SetDestParam( DST_RESIST_EARTH,			nAdjParameterValue, nChgParameterValue, bSend );
		return;
	case DST_STAT_ALLUP:
		SetDestParam( DST_STR,	nAdjParameterValue, nChgParameterValue, bSend );
		SetDestParam( DST_DEX,	nAdjParameterValue, nChgParameterValue, bSend );
		SetDestParam( DST_INT,	nAdjParameterValue, nChgParameterValue, bSend );
		SetDestParam( DST_STA,	nAdjParameterValue, nChgParameterValue, bSend );
		return;
	case DST_HPDMG_UP:
		SetDestParam( DST_HP_MAX, nAdjParameterValue, nChgParameterValue, bSend );
		SetDestParam( DST_CHR_DMG, nAdjParameterValue, nChgParameterValue, bSend );
		return;
	case DST_DEFHITRATE_DOWN:
		SetDestParam( DST_ADJDEF, nAdjParameterValue, nChgParameterValue, bSend );
		SetDestParam( DST_ADJ_HITRATE, nAdjParameterValue, nChgParameterValue, bSend );
		return;
	case DST_LOCOMOTION:
		SetDestParam( DST_SPEED,	nAdjParameterValue, nChgParameterValue, bSend );
		SetDestParam( DST_JUMPING,	( nAdjParameterValue * 3 ), nChgParameterValue, bSend );
		return;
	case DST_HP_RECOVERY_RATE:
		{
			int nMax	= GetMaxOriginHitPoint();
			int nRecv	= (int)( (nMax * (nAdjParameterValue / 100.0f)) );
			SetDestParam( DST_HP_RECOVERY, nRecv, NULL_CHGPARAM, bSend );
		}
		return;
	case DST_MP_RECOVERY_RATE:
		{
			int nMax	= GetMaxOriginManaPoint();
			int nRecv	= (int)( (nMax * (nAdjParameterValue / 100.0f)) );
			SetDestParam( DST_MP_RECOVERY, nRecv, NULL_CHGPARAM, bSend );
		}
		return;
	case DST_FP_RECOVERY_RATE:
		{
			int nMax	= GetMaxOriginFatiguePoint();
			int nRecv	= (int)( (nMax * (nAdjParameterValue / 100.0f)) );
			SetDestParam( DST_FP_RECOVERY, nRecv, NULL_CHGPARAM, bSend );
		}
		return;
	case DST_ALL_RECOVERY:
		{
			SetDestParam( DST_HP_RECOVERY, nAdjParameterValue, NULL_CHGPARAM, bSend );
			SetDestParam( DST_MP_RECOVERY, nAdjParameterValue, NULL_CHGPARAM, bSend );
			SetDestParam( DST_FP_RECOVERY, nAdjParameterValue, NULL_CHGPARAM, bSend );
		}
		return;
	case DST_ALL_RECOVERY_RATE:
		{
			int nMax	= GetMaxOriginHitPoint();
			int nRecv	= (int)( (nMax * (nAdjParameterValue / 100.0f)) );
			SetDestParam( DST_HP_RECOVERY, nRecv, NULL_CHGPARAM, bSend );

			nMax	= GetMaxOriginManaPoint();
			nRecv	= (int)( (nMax * (nAdjParameterValue / 100.0f)) );
			SetDestParam( DST_MP_RECOVERY, nRecv, NULL_CHGPARAM, bSend );

			nMax	= GetMaxOriginFatiguePoint();
			nRecv	= (int)( (nMax * (nAdjParameterValue / 100.0f)) );
			SetDestParam( DST_FP_RECOVERY, nRecv, NULL_CHGPARAM, bSend );
		}
		return;
	case DST_KILL_ALL:	
		{
			SetDestParam( DST_KILL_HP, nAdjParameterValue, NULL_CHGPARAM, bSend );
			SetDestParam( DST_KILL_MP, nAdjParameterValue, NULL_CHGPARAM, bSend );
			SetDestParam( DST_KILL_FP, nAdjParameterValue, NULL_CHGPARAM, bSend );
		}
		return;
	case DST_KILL_HP_RATE:
		{
			int nMax	= GetMaxOriginHitPoint();
			int nRecv	= (int)( (nMax * (nAdjParameterValue / 100.0f)) );
			SetDestParam( DST_KILL_HP, nRecv, NULL_CHGPARAM, bSend );
		}
		return;
	case DST_KILL_MP_RATE:
		{
			int nMax	= GetMaxOriginManaPoint();
			int nRecv	= (int)( (nMax * (nAdjParameterValue / 100.0f)) );
			SetDestParam( DST_KILL_MP, nRecv, NULL_CHGPARAM, bSend );
		}
		return;
	case DST_KILL_FP_RATE:
		{
			int nMax	= GetMaxOriginFatiguePoint();
			int nRecv	= (int)( (nMax * (nAdjParameterValue / 100.0f)) );
			SetDestParam( DST_KILL_FP, nRecv, NULL_CHGPARAM, bSend );
		}
		return;
	case DST_KILL_ALL_RATE:
		{
			int nMax	= GetMaxOriginHitPoint();
			int nRecv	= (int)( (nMax * (nAdjParameterValue / 100.0f)) );
			SetDestParam( DST_KILL_HP, nRecv, NULL_CHGPARAM, bSend );

			nMax	= GetMaxOriginManaPoint();
			nRecv	= (int)( (nMax * (nAdjParameterValue / 100.0f)) );
			SetDestParam( DST_KILL_MP, nRecv, NULL_CHGPARAM, bSend );

			nMax	= GetMaxOriginFatiguePoint();
			nRecv	= (int)( (nMax * (nAdjParameterValue / 100.0f)) );
			SetDestParam( DST_KILL_FP, nRecv, NULL_CHGPARAM, bSend );
		}
		return;
	case DST_ALL_DEC_RATE:
		{
			SetDestParam( DST_MP_DEC_RATE, nAdjParameterValue, NULL_CHGPARAM, bSend );
			SetDestParam( DST_FP_DEC_RATE, nAdjParameterValue, NULL_CHGPARAM, bSend );
		}
		return;
	}

	if( nDstParameter >= MAX_ADJPARAMARY)
		return;

	if( nAdjParameterValue != 0 )
	{
		fSuccess = true;

		switch( nDstParameter )
		{
		case DST_CHRSTATE:
		case DST_IMMUNITY:
			if( nAdjParameterValue != NULL_ID )
			{
				if( nAdjParameterValue == 0xffffffff )
				{
					Log( LOG_ERROR, "SetDestParam : Adj == -1, %s", GetName() );
					return;
				}
				m_adjParamAry[nDstParameter] |= nAdjParameterValue;
			} else
				fSuccess = false;
			break;
		case DST_CURECHR:
			ResetDestParam( DST_CHRSTATE, nAdjParameterValue, bSend );
			return;
		case DST_REFLECT_DAMAGE:
			m_adjParamAry[nDstParameter] += nAdjParameterValue;
			m_chgParamAry[nDstParameter] = nChgParameterValue;
			break;
		case DST_CHR_CHANCEBLEEDING:
		case DST_CHR_CHANCESTEALHP:
		case DST_CHR_CHANCEPOISON:
		case DST_CHR_CHANCEDARK:
		case DST_CHR_CHANCESTUN:
		case DST_AUTOHP:
			m_adjParamAry[nDstParameter] += nAdjParameterValue;
			m_chgParamAry[nDstParameter] = nChgParameterValue;
			break;
		case DST_HEAL:
			m_nHealCnt	= (short)( PROCESS_COUNT * 6.0f );
			m_adjParamAry[nDstParameter]	+= nAdjParameterValue;	
			break;

		default:
			m_adjParamAry[nDstParameter] += nAdjParameterValue;
			break;
		}
	}

	else if( nChgParameterValue != 0x7FFFFFFF ) 
	{
		fSuccess = true;

		if( nDstParameter == DST_SPEED )
		{
			if( m_chgParamAry[nDstParameter] == 0x7FFFFFFF )
				m_chgParamAry[nDstParameter]	= 0;
			m_chgParamAry[nDstParameter]++;
		}
		else
			m_chgParamAry[nDstParameter] = nChgParameterValue;
	}

	if( ( fSuccess & bSend ) == TRUE ) 
		g_pUserMng.AddSetDestParam( this, nDstParameter, nAdjParameterValue, nChgParameterValue );
	


// 	if ( nAdjParameterValue == -1 )
// 	{
// 		v6 = GetMaxHitPoint();
// 		SetPointParam( nDstParameter, v6, 0);
// 	}
// 	else
// 	{
// 		v7 = sub_646450(pThis);
// 		CMover::SetPointParam(pThis, nDstParameter, nAdjParameterValue + v7, 0);
// 	}
// 	v5 = CMover::GetAdjParam(pThis, 94);
// 	if ( v5 > 0 )
// 	{
// 		CMover::ResetDestParam(pThis, 94, 0, 1);
// 		v5 = sub_6396C0(pThis, 94);
// 	}
}

void vMover::ResetDestParam( int nDstParameter, int nAdjParameterValue, bool fSend )
{
	switch( nDstParameter )
	{
	case DST_RESIST_ALL:
		ResetDestParam( DST_RESIST_ELECTRICITY,	nAdjParameterValue, true );
		ResetDestParam( DST_RESIST_FIRE,		nAdjParameterValue, true );
		ResetDestParam( DST_RESIST_WIND,		nAdjParameterValue, true );
		ResetDestParam( DST_RESIST_WATER,		nAdjParameterValue, true );
		ResetDestParam( DST_RESIST_EARTH,		nAdjParameterValue, true );
		return;
	case DST_STAT_ALLUP:
		ResetDestParam( DST_STR,			nAdjParameterValue,		true );
		ResetDestParam( DST_DEX,			nAdjParameterValue,		true );
		ResetDestParam( DST_INT,			nAdjParameterValue,		true );
		ResetDestParam( DST_STA,			nAdjParameterValue,		true );
		return;
	case DST_HPDMG_UP:
		ResetDestParam( DST_HP_MAX,			nAdjParameterValue,		true );
		ResetDestParam( DST_CHR_DMG,		nAdjParameterValue,		true );
		return;
	case DST_DEFHITRATE_DOWN:
		ResetDestParam( DST_ADJDEF,			nAdjParameterValue,		true );
		ResetDestParam( DST_ADJ_HITRATE,	nAdjParameterValue,		true );
		return;
	case DST_LOCOMOTION:
		ResetDestParam( DST_SPEED,	nAdjParameterValue,		true );
		ResetDestParam( DST_JUMPING,	( nAdjParameterValue * 3 ), true );
		return;

	case DST_HP_RECOVERY_RATE:
		{
			int nMax	= GetMaxOriginHitPoint();
			int nRecv	= (int)( (nMax * (nAdjParameterValue / 100.0f)) );
			ResetDestParam( DST_HP_RECOVERY, nRecv, true );
		}
		return;
	case DST_MP_RECOVERY_RATE:
		{
			int nMax	= GetMaxOriginManaPoint();
			int nRecv	= (int)( (nMax * (nAdjParameterValue / 100.0f)) );
			ResetDestParam( DST_MP_RECOVERY, nRecv, true );
		}
		return;
	case DST_FP_RECOVERY_RATE:
		{
			int nMax	= GetMaxOriginFatiguePoint();
			int nRecv	= (int)( (nMax * (nAdjParameterValue / 100.0f)) );
			ResetDestParam( DST_FP_RECOVERY, nRecv, true );
		}
		return;
	case DST_ALL_RECOVERY:
		{
			ResetDestParam( DST_HP_RECOVERY, nAdjParameterValue, true );
			ResetDestParam( DST_MP_RECOVERY, nAdjParameterValue, true );
			ResetDestParam( DST_FP_RECOVERY, nAdjParameterValue, true );
		}
		return;
	case DST_ALL_RECOVERY_RATE:
		{
			int nMax	= GetMaxOriginHitPoint();
			int nRecv	= (int)( (nMax * (nAdjParameterValue / 100.0f)) );
			ResetDestParam( DST_HP_RECOVERY, nRecv, true );


			nMax	= GetMaxOriginManaPoint();
			nRecv	= (int)( (nMax * (nAdjParameterValue / 100.0f)) );
			ResetDestParam( DST_MP_RECOVERY, nRecv, true );

			nMax	= GetMaxOriginFatiguePoint();
			nRecv	= (int)( (nMax * (nAdjParameterValue / 100.0f)) );
			ResetDestParam( DST_FP_RECOVERY, nRecv, true );
		}
		return;
	case DST_KILL_ALL:	
		{
			ResetDestParam( DST_KILL_HP, nAdjParameterValue, true );

			SetDestParam( DST_KILL_MP, nAdjParameterValue, true );
			SetDestParam( DST_KILL_FP, nAdjParameterValue, true );
		}
		return;
	case DST_KILL_HP_RATE:
		{
			int nMax	= GetMaxOriginHitPoint();
			int nRecv	= (int)( (nMax * (nAdjParameterValue / 100.0f)) );
			ResetDestParam( DST_KILL_HP, nRecv, true );
		}
		return;
	case DST_KILL_MP_RATE:
		{
			int nMax	= GetMaxOriginManaPoint();
			int nRecv	= (int)( (nMax * (nAdjParameterValue / 100.0f)) );
			ResetDestParam( DST_KILL_MP, nRecv, true );
		}
		return;
	case DST_KILL_FP_RATE:
		{
			int nMax	= GetMaxOriginFatiguePoint();
			int nRecv	= (int)( (nMax * (nAdjParameterValue / 100.0f)) );
			ResetDestParam( DST_KILL_FP, nRecv, true );
		}
		return;
	case DST_KILL_ALL_RATE:
		{
			int nMax	= GetMaxOriginHitPoint();
			int nRecv	= (int)( (nMax * (nAdjParameterValue / 100.0f)) );
			ResetDestParam( DST_KILL_HP, nRecv, true );

			nMax	= GetMaxOriginManaPoint();
			nRecv	= (int)( (nMax * (nAdjParameterValue / 100.0f)) );
			ResetDestParam( DST_KILL_MP, nRecv, true );

			nMax	= GetMaxOriginFatiguePoint();
			nRecv	= (int)( ( nMax * ( nAdjParameterValue / 100.0f ) ) );
			ResetDestParam( DST_KILL_FP, nRecv, true );
		}
		return;
	case DST_ALL_DEC_RATE:
		{
			SetDestParam( DST_MP_DEC_RATE, nAdjParameterValue, true );
			SetDestParam( DST_FP_DEC_RATE, nAdjParameterValue, true );
		}
	}

	if( nDstParameter >= MAX_ADJPARAMARY || nDstParameter < 0 )
		return;

	if( nAdjParameterValue != 0 ) 
	{
		if( nDstParameter == DST_CHRSTATE )
			m_adjParamAry[nDstParameter] &= (~nAdjParameterValue);
		else
			m_adjParamAry[nDstParameter] += (-nAdjParameterValue);
	}


	if( nAdjParameterValue == 0 )
	{
		if( nDstParameter == DST_SPEED && m_chgParamAry[nDstParameter] != 0x7FFFFFFF && m_chgParamAry[nDstParameter] > 0 )
		{
			if( --m_chgParamAry[nDstParameter] == 0 )
				m_chgParamAry[nDstParameter] = 0x7FFFFFFF;
		}
		else
		{
			m_chgParamAry[nDstParameter] = 0x7FFFFFFF;
		}
	}

	if( fSend ) 
	{
		if( nDstParameter == DST_SPEED )
			g_pUserMng.AddResetDestParamSync( this, nDstParameter, nAdjParameterValue, (int)m_adjParamAry[nDstParameter] );
		else
			g_pUserMng.AddResetDestParam( this, nDstParameter, nAdjParameterValue );
	}
}


bool vMover::SetStun(bool bApply, DWORD dwMaxTime)
{
	if( bApply )
	{
		MoverProp* pMoverProp = GetProperty();
		if( pMoverProp->dwClass == RANK_SUPER || pMoverProp->dwClass == RANK_MIDBOSS )
			return false;

		if( GetAdjParam( DST_IMMUNITY ) & CHS_STUN ) 
			return false;

		SetDestParam( DST_CHRSTATE, CHS_STUN, NULL_CHGPARAM, FALSE );
		SendActMsg( OBJMSG_STUN );
		m_wStunCnt = (short)( (dwMaxTime / 1000.0f) * PROCESS_COUNT );
	}
	else
	{
		if( GetAdjParam( DST_CHRSTATE ) & CHS_STUN )
			ResetDestParam( DST_CHRSTATE, CHS_STUN, false);

		m_wStunCnt = 0;
		m_dwFlag &= (~MVRF_NOACTION);
	}

	g_pUserMng.AddSetStun( this, dwMaxTime );
	return true;
}

bool vMover::SetPoison( bool bApply, OBJID idAttacker, DWORD tmMaxTime, DWORD tmUnit, short wDamage )
{
	if( bApply )
	{
		if( GetAdjParam( DST_IMMUNITY ) & CHS_POISON ) 
			return false;

		SetDestParam( DST_CHRSTATE, CHS_POISON, NULL_CHGPARAM );

		m_wPoisonCnt = (short)( (tmMaxTime / 1000.0f) * PROCESS_COUNT );
		m_wPoisonDamage = wDamage;
		m_tmPoisonUnit = tmUnit;
		m_idPoisonAttacker = idAttacker;
	} 
	else
	{
		if( GetAdjParam( DST_CHRSTATE) & CHS_POISON )
			ResetDestParam( DST_CHRSTATE, CHS_POISON, true );

		m_wPoisonCnt = 0;
		m_wPoisonDamage = 0;
		m_tmPoisonUnit = 0;
	}
	return true;
}

bool vMover::SetDarkCover( bool bApply, DWORD tmMaxTime )
{
	if( bApply )
	{
		if( GetAdjParam( DST_IMMUNITY ) & CHS_INVISIBILITY )
			return false;

		SetDestParam( DST_CHRSTATE, CHS_INVISIBILITY, NULL_CHGPARAM );
		m_wDarkCover = (short)( (tmMaxTime / 1000.0f) * PROCESS_COUNT );
	} 
	else
	{
		if( GetAdjParam( DST_CHRSTATE) & CHS_INVISIBILITY )
			ResetDestParam( DST_CHRSTATE, CHS_INVISIBILITY, true );
		m_wDarkCover = 0;
	}

	return true;
}

bool vMover::SetDark( bool bApply, DWORD tmMaxTime, int nAdjHitRate )
{
	if( bApply )
	{
		if( GetAdjParam( DST_IMMUNITY ) & CHS_DARK ) 
			return false;

		SetDestParam( DST_CHRSTATE, CHS_DARK, NULL_CHGPARAM );
		SetDestParam( DST_ADJ_HITRATE, nAdjHitRate, NULL_CHGPARAM );
		m_wDarkCnt = (short)( (tmMaxTime / 1000.0f) * PROCESS_COUNT );

		if( nAdjHitRate == -1 )
			Log( LOG_ERROR, "SetDark : %s", GetName() );

		m_wDarkVal = nAdjHitRate;
	} 
	else
	{
		if( GetAdjParam( DST_CHRSTATE) & CHS_DARK )
		{
			ResetDestParam( DST_CHRSTATE, CHS_DARK, TRUE );
			ResetDestParam( DST_ADJ_HITRATE, m_wDarkVal, TRUE );
		}

		m_wDarkCnt = 0;
		m_wDarkVal = 0;
	}
	return true;
}

bool vMover::SetBleeding( bool bApply, DWORD idAttacker, DWORD tmMaxTime, DWORD tmUnit, short wDamage )
{
	if( bApply )
	{
		if( GetAdjParam( DST_IMMUNITY ) & CHS_BLEEDING ) 
			return false;

		SetDestParam( DST_CHRSTATE, CHS_BLEEDING, NULL_CHGPARAM );

		m_wBleedingCnt = (short)( (tmMaxTime / 1000.0f) * PROCESS_COUNT );
		m_wBleedingDamage = wDamage;
		m_tmBleedingUnit = tmUnit;
		m_idBleedingAttacker = idAttacker;
	} 
	else
	{
		if( GetAdjParam( DST_CHRSTATE) & CHS_BLEEDING )
			ResetDestParam( DST_CHRSTATE, CHS_BLEEDING, TRUE );

		m_wBleedingCnt = 0;
		m_wBleedingDamage = 0;
		m_tmBleedingUnit = 0;
	}
	return true;
}

BOOL vMover::SetSleeping(BOOL bApply, DWORD tmMaxTime)
{
	static const Address addrCall = 0x00648BA0;

	BOOL _bRet = FALSE;
	__asm
	{
		push	tmMaxTime;
		push	bApply;

		mov		ecx, this;
		call	addrCall;
		mov		_bRet, eax;
	}

	return _bRet;
}


void vMover::RemoveDebuff( DWORD dwState )
{
	__debugbreak();
	//RemoveChrStateBuffs( dwState );

	if( dwState & CHS_DARK )
		SetDark( FALSE );
	if( dwState & CHS_POISON )
		SetPoison( FALSE );
	if( dwState & CHS_STUN )
		SetStun( FALSE );
	if( dwState & CHS_BLEEDING )
		SetBleeding( FALSE );


	SetDestParam( DST_CURECHR, dwState, NULL_CHGPARAM );
}