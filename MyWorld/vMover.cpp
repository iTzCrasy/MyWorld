#include "stdafx.h"
#include "vWorld.h"
#include "vEventArena.h"
#include "vGuildCombat1to1Manager.h"
#include "vGuildCombatManager.h"
#include "vGameEvent.h"
#include "vClient.h"
#include "vMover.h"


extern vEventArena				g_pEventArena;
extern vGuildCombat1to1Manager	g_pGuildCombat1to1Mng;
extern vGuildCombatManager		g_pGuildCombatMng;
extern vClient					g_pClient;

void vMover::SetHitPoint(int nVal)
{
	static const Address addrSetHitPoint = 0x006465A0;
	__asm
	{
		push	nVal;
		mov		ecx, this;
		call	addrSetHitPoint;
	}
}

float vMover::SubDieDecExp( BOOL bTransfer, DWORD dwDestParam, BOOL bResurrection )
{
	static const Address addrSubDieDexExp = 0x0061DA00;
	__asm
	{
		push	bResurrection;
		push	dwDestParam;
		push	bTransfer;

		mov		ecx, this;
		call	addrSubDieDexExp;
	}
}


vItemProp* vMover::GetEquipItem(int nParts)
{
	static const Address addrCall = 0x00617DD0;

	vItemProp* pItem = nullptr;
	__asm
	{
		push nParts;

		mov ecx, this; 
		call addrCall;

		mov	pItem, eax;
	}

	return pItem;
}


vItemProp* vMover::GetWeaponItem( int nParts )
{
	static const Address addr = 0x00617CC0;

	vItemProp* pItem = nullptr;
	__asm
	{
		push nParts;
		mov ecx, this;

		call addr;
		mov pItem, eax;
	}

	return pItem;
}

void vMover::RemoveBuff( WORD wType, WORD wId )
{
	static const Address addrCall = 0x00639250;
	__asm
	{
		push	wId;
		push	wType;

		mov		ecx, this;
		call	addrCall;
	}
}

bool vMover::Replace( DWORD dwWorldID, D3DXVECTOR3 & vPos, REPLACE_TYPE rType, int nLayer )
{
	static const Address addrCall = 0x00615D40;
	BOOL _bRet = FALSE;

	__asm
	{
		push	nLayer;
		push	rType;
		push	vPos;
		push	dwWorldID;

		mov		ecx, DWORD PTR DS:[0x7831C8]
		push	ecx;

		push	0; //=>new param?

		mov		ecx, this;
		call	addrCall;

		mov		_bRet, eax;
	}


	return _bRet == TRUE;
}

void vMover::InitNPCProperty()
{
	static const Address addrCall = 0x00612E00;
	__asm
	{
		mov		ecx, this;
		call	addrCall;
	}
}

CHARACTER* vMover::GetCharacter()
{
	static const Address addrCall = 0x00612D70;

	CHARACTER* pChar = nullptr;
	__asm
	{
		mov		ecx, this;
		call	addrCall;
		mov		pChar, eax;
	}

	return pChar;
}

void vMover::InitCharacter(CHARACTER* pChar)
{
	static const Address addrCall = 0x00612EB0;
	__asm
	{
		push	pChar;

		mov		ecx, this;
		call	addrCall;
	}
}

void vMover::DoDie(vCtrl* pAttacker, DWORD dwMsg )
{
	static const Address addrCall = 0x00619C50;
	__asm
	{
		push	dwMsg;
		push	pAttacker;

		mov		ecx, this;
		call	addrCall;
	}
}



char* vMover::GetName(BOOL bNickname)
{
	if( !bNickname )
		return m_szName;

	if( m_dwAuthorization >= AUTH_GAMEMASTER && ( GetIndex() == MI_CROWNIBLIS || GetIndex() == MI_CROWNSHADE || GetIndex() == MI_CROWNBUBBLE ) )
	{
		MoverProp* pMoverProp = GetProperty();
		if( pMoverProp )
			return pMoverProp->szName;
	}
	return m_szName;
}

void vMover::RemoveItem(DWORD bId, int nNum)
{
	static const Address addrCall = 0x006163C0;
	__asm
	{
		push	nNum;
		push	bId;

		mov		ecx, this;
		call	addrCall;
	}
}

vItemBase* vMover::GetItemId(DWORD dwId)
{
	static const Address addrCall = 0x00618FA0;

	vItemBase* pItem = nullptr;
	__asm
	{
		push	dwId;

		mov		ecx, this;
		call	addrCall;
		mov		pItem, eax;
	}
	return pItem;
}

void vMover::UpdateItem(byte nId, char cParam, DWORD dwValue, DWORD dwTime)
{
	static const Address addrCall = 0x00648220;

	__asm
	{
		push	dwTime;
		push	dwValue;
		push	cParam;
		push	nId;

		mov		ecx, this;
		call	addrCall;
	}
}

void vMover::SetGold(int nGold)
{
	static const Address addrCall = 0x0055F180;
	__asm
	{
		push	nGold;

		mov		ecx, this;
		call	addrCall;
	}
}

BOOL vMover::AddExperience( __int64 nExp, BOOL bFirstCall, BOOL bMultiPly, BOOL bMonster )
{
	static const Address addrCall = 0x00643230;
	BOOL _bRet = FALSE;

	__asm
	{
		push	bMonster;
		push	bMultiPly;
		push	bFirstCall;
		push	nExp;

		mov		ecx, this;
		call	addrCall;
		mov		_bRet, eax;
	}
	return _bRet;
}

int vMover::GetChgParam( int nDestParameter )
{
	if( nDestParameter >= 117 )
		return INT_MAX;
	return *(int*)(this + nDestParameter + 1397);
}

int vMover::GetAdjParam( int nDestParameter )
{
	if( nDestParameter >= 117 )
		return NULL;
	return *(int*)(this + nDestParameter + 1280);
}


int vMover::GetParam(int nDest, int nParam)
{
	int nChgParam = GetChgParam( nDest );
	if( nChgParam != INT_MAX ) 
		return nChgParam;

	int nAdjParam = GetAdjParam( nDest );
	if( nAdjParam )	
		return nParam + nAdjParam;
	else
		return nParam;
}

long vMover::GetSta()
{
	return m_nSta + GetParam( DST_STA, 0 );
}

long vMover::GetStr()
{
	return m_nStr + GetParam( DST_STR, 0 );
}

long vMover::GetDex()
{
	return m_nDex + GetParam( DST_DEX, 0 );
}

long vMover::GetInt()
{
	return m_nInt + GetParam( DST_INT, 0);
}

void vMover::GetDieDecExpRate( float& fDecExp, DWORD dwDestParam, bool bResurrection )
{
	if( dwDestParam != 0 )
	{
		float fAddDec = (float)(100 - dwDestParam) / 100.0f;
		fDecExp = fDecExp - (fDecExp * fAddDec);
	}

	if( IsChaotic() && ( IsSMMode( SM_REVIVAL ) || bResurrection ) )
		fDecExp = fDecExp * 0.9f;
	else if( IsSMMode( SM_REVIVAL ) )
		fDecExp = 0.0f;
}

void vMover::GetDieDecExp( int nLevel, float& fRate, float& fDecExp, bool& bPxpClear, bool& bLvDown )
{
	if( nLevel == 1 )		{ fRate	= 0.8f; fDecExp = 0.0f ; bPxpClear = false; bLvDown = false; }
	else if( nLevel == 2 )	{ fRate	= 0.6f; fDecExp = 0.0f ; bPxpClear = false; bLvDown = false; }
	else if( nLevel <= 5 )	{ fRate	= 0.5f; fDecExp = 0.0f ; bPxpClear = false; bLvDown = false; }
	else if( nLevel <= 10 )	{ fRate	= 0.4f; fDecExp = 0.0f ; bPxpClear = true ; bLvDown = false; }
	else if( nLevel <= 15 )	{ fRate	= 0.3f; fDecExp = 0.02f; bPxpClear = true ; bLvDown = false; }
	else					{ fRate	= 0.3f; fDecExp = 0.03f; bPxpClear = true ; bLvDown = true;  }	
}

BOOL vMover::DoDropItemRandom( BOOL bExcludeEquip, vMover* pAttacker, BOOL bOnlyEquip )
{
	static const Address addrCall = 0x006169A0;
	BOOL _bRet = 0;
	__asm
	{
		push	bOnlyEquip;
		push	pAttacker;
		push	bExcludeEquip;
		
		mov		ecx, this;
		call	addrCall;
		mov		_bRet, eax;
	}
	return _bRet;
}

BOOL vMover::AddGold(int nGold, BOOL bSend)
{
	static const Address addrCall = 0x00612150;
	BOOL _bRet = FALSE;
	__asm
	{
		push	bSend;
		push	nGold;

		mov		ecx, this;
		call	addrCall;
		mov		_bRet, eax;
	}
	return _bRet;
}

BOOL vMover::SubPK( vMover* pAttacker, int nReflect )
{
	if(!IsPlayer())		return TRUE;

	if( !g_gameEvent.GetState(EVE_PK) || GetWorld()->IsArena()  || !g_pEventArena.IsActive() ||  
		( GetWorld()->GetId() == WI_WORLD_GUILDWAR || pAttacker->GetWorld()->GetId() == WI_WORLD_GUILDWAR ) && g_pGuildCombatMng.GetState() != vGuildCombatManager::CLOSE_STATE ||
		g_pGuildCombat1to1Mng.IsPossibleUser((vUser*)this) && g_pGuildCombat1to1Mng.IsPossibleUser((vUser*)pAttacker)
		) 
		return TRUE;


	if(g_gameEvent.GetState( EVE_PKCOST ))
	{
		if( IsPlayer() && IsChaotic())
		{
			CHAO_PROPENSITY Propensity = g_prj.GetPropensityPenalty( GetPKPropensity() );

			int nInvenDrop = xRandom(Propensity.nInvenDorpMin, Propensity.nInvenDorpMax);
			for(int i = 0; i < nInvenDrop; i++ )
			{
				if( DoDropItemRandom( TRUE, pAttacker ) == 0 )
					break;
			}

			int nEquipDrop = xRandom( Propensity.nEquipDorpMin, Propensity.nEquipDorpMax + 1 );
			for( int i = 0; i < nEquipDrop; ++i )
			{
				if( DoDropItemRandom( FALSE, pAttacker, TRUE ) == 0 )	
					break;
			}	
		}

		if( pAttacker->IsPlayer() )
		{
			m_idMurderer = pAttacker->GetId();
			
			vWorld* pWorld = GetWorld();
			if( pWorld )
			{
				char szFormat[256];
				strcpy_s( szFormat, pAttacker->GetName() );
// 				strcat_s( szFormat, g_prj.GetText( TID_PK_REWARDNOTICE ) );
// 				
				((vUser*)this)->AddDefinedText( TID_GAME_PKDEAD );

				g_pClient.SendWCWantedReward( GetId(), pAttacker->GetId(), szFormat, pWorld->GetId(), GetPos(), GetLayer() );
			}
		}
	}

	Log( LOG_SUCCESS, ">> mue %d", m_idMurderer );

	if( !pAttacker->IsPlayer() || IsNPC() )
		return TRUE;

	bool bAdd = false;
	if( pAttacker->IsChaotic() )
	{
		if( !IsChaotic() )
			bAdd = true;
	}
	else
	{
		if( !(IsChaotic() || IsPKPink()) )
			bAdd = true;
	}

// 	if( bAdd && nReflect == 0 && pAttacker != this )
// 	{
// 		if( IsPlayer() && pAttacker->IsPlayer() )
// 		{
// 			if( !pAttacker->IsChaotic() )
// 				((vUser*)pAttacker)->AddPlaySound( SND_PC_CHAOS );
// 			
// 			char szBuff[64] = {0};
// 
// 			sprintf_s( szBuff, g_prj.GetText(TID_GAME_PK_DEFENDER), pAttacker->GetName() );
// 			((vUser*)this)->AddText( szBuff );
// 			sprintf_s( szBuff, g_prj.GetText(TID_GAME_PK_ATTACKER) , GetName() );
// 			((vUser*)pAttacker)->AddText( szBuff );
// 		}
// 
// 		pAttacker->SetPKValue( pAttacker->GetPKValue() + 1 );
// 		((vUser*)pAttacker)->AddPKValue();
// 		pAttacker->SetPKPropensity( pAttacker->GetPKPropensity() + NextPKPropensity( pAttacker->GetPKValue() ) );
// 		g_UserMng.AddPKPropensity( pAttacker );
// 		g_dpDBClient.SendLogPkPvp( pAttacker, this, 0, 'P' );
// 		((vUser*)pAttacker)->SetHonorAdd(HS_PK_COUNT,HI_COUNT_CHECK);
// 	}
	
	return TRUE;
}

inline MoverProp* vMover::GetProperty()
{	
	return g_prj.GetMoverProp( m_dwIndex );						
}

inline __int64 vMover::GetMaxExp1()
{	
	return g_prj.m_pExpCharacter[m_nLevel+1].nExp1;
}
inline __int64 vMover::GetMaxExp2()
{	
	return g_prj.m_pExpCharacter[m_nLevel].nExp2;
}