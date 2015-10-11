#pragma once
#include "stdafx.h"
#include "vProject.h"
#include "vInventory.h"
#include "vCtrl.h"


#define	MAX_SKILLBUFF_COUNT	14
class vMover;

class CVTInfo
{
private:
	DWORD					m_dwTradeGold;				//4
	vItemBase*				m_apItem_VT[MAX_VENDITEM];	//120
	DWORD					m_objId;					//4	
	vMover*					m_pOwner;					//4
	TRADE_STATE				m_state;					//4
	byte x[28];
	//string					m_strTitle;
};//164

class vMover : public vCtrl
{
public:

	float		SubDieDecExp( BOOL bTransfer = TRUE, DWORD dwDestParam = 0, BOOL bResurrection = FALSE  );
	void		SetHitPoint(int nVal);
	vItemProp*	GetEquipItem(int nParts);

	vItemProp*	GetWeaponItem( int nParts = 10 );
	void		RemoveBuff( WORD wType, WORD wId );
	bool		Replace( DWORD dwWorldID, D3DXVECTOR3 & vPos, REPLACE_TYPE rType, int nLayer  );
	void		InitNPCProperty();
	CHARACTER*	GetCharacter();
	void		InitCharacter( CHARACTER* pChar );
	void		DoDie(vCtrl* pAttacker, DWORD dwMsg = 0 );

	bool		SetStun( bool bApply, DWORD dwMaxTime = 0);
	bool		SetPoison( bool bApply, DWORD idAttacker = NULL_ID, DWORD tmMaxTime = 0, DWORD tmUnit = 0, short wDamage = 0 );
	bool		SetDark( bool bApply, DWORD tmMaxTime = 0, int nAdjHitRate = 0 );
	bool		SetBleeding( bool bApply, DWORD idAttacker = NULL_ID, DWORD tmMaxTime = 0, DWORD tmUnit = 0, short wDamage = 0 );
	bool		SetDarkCover( bool bApply, DWORD tmMaxTime = 0 );


	BOOL		SetSleeping( BOOL bApply, DWORD tmMaxTime = 0);
	char*		GetName(BOOL bNickname = FALSE);
	void		RemoveItem( DWORD bId, int nNum);
	vItemBase*	GetItemId(DWORD dwId);
	void		UpdateItem(byte nId, CHAR cParam, DWORD dwValue, DWORD dwTime);
	void		SetGold(int nGold);
	BOOL		AddExperience( __int64 nExp, BOOL bFirstCall = TRUE, BOOL bMultiPly = TRUE, BOOL bMonster = FALSE );
	int			GetChgParam( int nDestParameter );
	int			GetAdjParam( int nDestParameter );
	int			GetParam(int nDest, int nParam);
	void		GetDieDecExpRate( float& fDecExp, DWORD dwDestParam, bool bResurrection );
	long		GetSta();
	long		GetStr();
	long		GetDex();
	long		GetInt();
	bool		IsSMMode( int nType ){ return *(int*)(this + nType + 196) > 0 ;}
	void		GetDieDecExp( int nLevel, float& fRate, float& fDecExp, bool& bPxpClear, bool& bLvDown );
	BOOL		SubPK( vMover* pAttacker, int nReflect );
	int			DoDropItemRandom( BOOL bExcludeEquip, vMover* pAttacker, BOOL bOnlyEquip = FALSE );
	BOOL		AddGold(int nGold, BOOL bSend = TRUE);
	
 public:
	int			GetMaxHitPoint();
	int			GetMaxManaPoint();

	int			GetMaxOriginHitPoint( bool bOriginal = false );
	int			GetMaxOriginManaPoint( bool bOriginal = true );
	void		SetPointParam( int nDstParameter, int nValue, bool bTrans = false  );

	void		ResetDestParam( int nDstParameter, int nAdjParameterValue, bool fSend );
	void		SetDestParam( int nDstParameter, int nAdjParameterValue, int nChgParameterValue, bool bSend = true );
	int			GetMaxFatiguePoint();
	int			GetMaxOriginFatiguePoint( bool bOriginal = false );
	void		RemoveDebuff( DWORD dwState );


	inline int SendActMsg( OBJMSG dwMsg, int nParam1 = 0, int nParam2 = 0, int nParam3 = 0, int nParam4 = 0 ) 	
	{	
		static const Address addrCall = 0x00491500;
		
		__asm
		{
			push	nParam4;
			push	nParam3;
			push	nParam2;
			push	nParam1;
			push	dwMsg;
			mov		ecx, this;
			call addrCall;
		}
	}


	MoverProp*			GetProperty();
	__int64				GetMaxExp1();
	__int64				GetMaxExp2();

	void				ClearDestObj()					 	{	m_idDest = NULL_ID; m_fArrivalRange = 0.0f;					}
	void				ClearDestPos()						{	m_vDestPos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );				}		
	void				ClearDest()							{	ClearDestObj(); ClearDestPos();								}

/*	void				SetStop()			{ SendActMsg( OBJMSG_STAND ); ClearDestObj(); } */

	inline	bool		HasActivatedEatPet()				{	return m_oiEatPet != NULL_ID;								}
	inline	bool		HasActivatedSystemPet()				{	return m_dwPetId != NULL_ID;								}
	inline	DWORD		GetEatPetId()						{	return m_oiEatPet;											}
	inline	DWORD		GetPetId()							{	return m_dwPetId;											}
	inline	u_long		GetCampusId()						{	return m_idCampus;											}
	inline	int			GetCampusPoint()					{	return m_nCampusPoint;										}
	inline	bool		IsNPC()								{	return !m_bPlayer;											}
	inline	BOOL		IsPlayer()							{	return m_bPlayer;											}
	inline	bool		IsFlyingNPC()						{	return (m_dwTypeFlag & OBJTYPE_FLYING)?true:false;			}	
	inline	DWORD		GetDestId()							{	return m_idDest;											}
	inline	bool		IsRegionAttr( DWORD dwAttribite )	{	return (m_dwRegionAttr & dwAttribite) == dwAttribite;		}
	inline	DWORD		GetRideItemIdx()					{	return m_dwRideItemIdx;										}
	inline	DWORD		IsAuthorization( DWORD dwAuth )		{	return dwAuth == m_dwAuthorization;							}
	inline	DWORD		IsAuthHigher( DWORD dwAtuh )		{	return dwAtuh <= m_dwAuthorization;							}
	inline	DWORD		GetAuthorization()					{	return m_dwAuthorization;									}
	inline	void		SetName( char* lpszName )			{	strcpy_s( m_szName, lpszName );								}
	inline	byte		GetSex()							{	return m_bySex;												}
	inline	bool		IsPeaceful()						{	return m_dwBelligerence == BELLI_PEACEFUL;					}
	inline	DWORD		GetPKPink()							{	return m_dwPKTime;											}
	inline	bool		IsPKPink()							{	return m_dwPKTime > 0;										}
	inline	bool		IsChaotic()							{	return m_dwPKPropensity > 0;								}
	inline	int			GetPKValue()						{	return m_nPKValue;											}
	inline	DWORD		GetPKPropensity()					{	return m_dwPKPropensity;									}
	inline	bool		GetFlightLv()						{	return GetLevel() >= 20;									}
	inline	int			GetLevel()							{	return m_nLevel;											}
	inline	int			GetFxp()							{	return m_nFxp;												}
	inline	int			GetTxp()							{	return m_nFxp;												}
	inline	bool		IsDie()								{	return m_pActMover->IsDie() || m_nHitPoint == 0;			}
	inline	bool		IsLive()							{	return !m_pActMover->IsDie() || m_nHitPoint > 0;			}
	inline	void		SetMode( DWORD dwMode )				{	m_dwMode |= dwMode;											}
	inline	void		SetNotMode( DWORD dwMode )			{	m_dwMode &= (~dwMode);										} 
	inline	__int64		GetExp1()							{	return m_nExp1;												}


	inline int			GetHitPoint()						{	return GetParam( DST_HP, m_nHitPoint );						}
	inline int			GetManaPoint()						{	return GetParam( DST_MP, m_nManaPoint );					}
	inline int			GetFatiguePoint()					{	return GetParam( DST_FP, m_nFatiguePoint );					}


	inline int			GetJob()							{	return m_nJob; 												}
	inline int			GetRemainGP()						{	return m_nRemainGP;											}
	inline int			GetGold()							{	return m_dwGold;											}

	inline int			GetExpPercent()						{	int nExpPercent = 0;	nExpPercent = (int)( GetExp1() * 10000 / GetMaxExp1() );	return nExpPercent;		}
	inline BOOL			IsFly()								{	return m_pActMover->IsFly(); 								}


public:
	byte					bUnkw[ 0x14 ];
	BOOL					m_bPlayer;					//0x228
	u_long					m_idPlayer;					//0x22C
	CActionMover*			m_pActMover;				//0x230				0xBCu
	DWORD					m_dwTypeFlag;				//0x234
	DWORD					m_dwMode;					//0x238
	DWORD					m_dwFlag;					//0x23C
	DWORD					m_dwStateMode;				//0x240
	float					m_fCrrSpd;					//0x244
	float					m_fAniSpeed;				//0x248
	float					m_fArrivalRange;			//0x24C
	DWORD					m_idDest;					//0x250
	D3DXVECTOR3				m_vDestPos;					//0x254
	float					m_fDestAngle;				//0x260
	void*					m_pIADestPos;				//0x264
	BOOL					m_fWaitQueryGetPos;			//0x268
	int						m_nCorr;					//0x26C
	u_long					m_uRemnantCorrFrm;			//0x270
	CORR_ACTION				m_CorrAction;				//0x274
	bool					m_bForward;					//0x2C4
	bool					m_bPositiveZ;				//0x2C5
	bool					m_bPositiveX;				//0x2C6
	bool					m_bLeft;					//0x2C7
	DWORD					m_dwRegionAttr;				//0x2C8
	DWORD					m_dwOldRegionAttr;			//0x2CC
	DWORD					m_dwMotion;					//0x2D0
	DWORD					m_dwMotionOption;			//0x2D4
	OBJMSG					m_dwMotionArrive;			//0x2D8
	DWORD					m_dwTickRecovery;			//0x2DC
	DWORD					m_dwTickRecoveryStand;		//0x2E0
	byte					bUnkwXX[ 0x14 ];			//0x2E4
	int						m_nAccountPlayTime;			//0x2F8
	byte					m_pBuffs[ 0x14 ];			//0x2FC > CBuffMgr		m_buffs;
	DWORD					m_dwSMTime[SM_MAX];			//0x310
	SKILL					m_aJobSkill[ MAX_SKILL_JOB ];	//0x37C >> 198
	DWORD					m_tmReUseDelay[ MAX_SKILL_JOB ]; //0x514
	long					m_nStr;						//0x5E0
	long					m_nSta;						//0x5E4
	long					m_nDex;						//0x5E8
	long					m_nInt;						//0x5EC
	long					m_nLevel;					//0x5F0
	long					m_nDeathLevel;				//0x5F4
	__int64					m_nExp1;					//0x5F8
	__int64					m_nDeathExp;				//0x5FC
	long					m_nFlightLv;				//0x604
	long					m_nFxp;						//0x60C
	long					m_nHitPoint;				//0x610
	long					m_nManaPoint;				//0x614	
	long					m_nFatiguePoint;			//0x618
	long					m_nRemainGP;				//0x61C
	long					m_nDefenseMin;				//0x620
	long					m_nDefenseMax;				//0x624
	int						m_nAdjHitRate;				//0x628
	int						m_nAdjParry;				//0x62C
	long					m_nJob;						//0x630
	byte					m_bySex;					//0x634
	DWORD					m_dwSkinSet;				//0x638
	DWORD					m_dwFace;					//0x63C
	DWORD					m_dwHairMesh;				//0x640
	DWORD					m_dwHairColor;				//0x644
	DWORD					m_dwHeadMesh;				//0x648
	float					m_fHairColorR;				//0x64C
	float					m_fHairColorG;				//0x650
	float					m_fHairColorB;				//0x654
	DWORD					m_dwAuthorization;			//0x658
	char					m_szCharacterKey[32];		//0x65C
	DWORD					m_dwBelligerence;			//0x67C
	BOOL					m_bActiveAttack;			//0x680
	DWORD					m_dwVirtItem;				//0x684
	DWORD					m_dwVirtType;				//0x688
	DWORD					m_oiEatPet;					//0x68C
	int						m_nFuel;					//0x690
	int						m_tmAccFuel;				//0x694
	BOOL					m_bItemFind;				//0x698
	int						m_nReadyTime;				//0x69C
	DWORD					m_dwUseItemId;				//0x6A0
	DWORD					m_dwCtrlReadyTime;			//0x6A4
	DWORD					m_dwCtrlReadyId;			//0x6A8
	DWORD					m_idAttacker;				//0x6AC
	DWORD					m_idTargeter;				//0x6B0
	DWORD					m_idTracking;				//0x6B4
	DWORD					m_idLastHitMover;			//0x6B8
	float					m_fExpRatio;				//0x6BC
	int						m_nAtkCnt;					//0x6C0
	int						m_nReflexDmg;				//0x6C4
	long					m_nPlusMaxHitPoint;			//0x6C8
	DWORD					m_tmPoisonUnit;				//0x6CC
	DWORD					m_tmBleedingUnit;			//0x6D0
	DWORD					m_idPoisonAttacker;			//0x6D4
	DWORD					m_idBleedingAttacker;		//0x6D8
	short					m_wStunCnt;					//0x6DC
	short					m_wPoisonCnt;				//0x6DE
	short					m_wPoisonDamage;			//0x6E0
	short					m_wDarkCnt;					//0x6E2
	short					m_wDarkVal;					//0x6E4
	short					m_wBleedingCnt;				//0x6E6
	short					m_wBleedingDamage;			//0x6E8
	short					m_wDarkCover;				//0x6EA	
	short					m_nHealCnt;					//0x6EC
	float					m_fSpeedFactor;				//0x6F0
	byte					m_nAttackResistLeft;		//0x6F4
	byte					m_nAttackResistRight;		//0x6F5
	byte					m_nDefenseResist;			//0x6F6
	u_long					m_idparty;					//0x6F8
	u_long					m_idGuild;					//0x6FC
	BOOL					m_bGuildBank;				//0x700
	DWORD					m_idGuildCloak;				//0x704
	u_long					m_idWar;					//0x708
	DWORD					m_tmActionPoint;			//0x70C
	DWORD					m_dwTickCheer;				//0x710
	int						m_nCheerPoint;				//0x714
	DWORD					m_dwTickDuel;				//0x718
	DWORD					m_dwTickEndDuel;			//0x71C
	int						m_nDuelState;				//0x720
	int						m_nDuel;					//0x724
	DWORD					m_idDuelOther;				//0x728
	u_long					m_idDuelParty;				//0x72C
	int						m_nFame;					//0x730
	u_long					m_idMurderer;				//0x734
	DWORD					m_dwPKTime;					//0x738
	int						m_nPKValue;					//0x73C
	DWORD					m_dwPKPropensity;			//0x740
	DWORD					m_dwPKExp;					//0x744
	__int64					m_nAngelExp;				//0x748
	long					m_nAngelLevel;				//0x750
	byte					m_nLegend;					//0x754
	DWORD					dwRemoveSfxObj[MAX_SKILLBUFF_COUNT]; //0x758
	int						m_nHonor;					//0x790
	DWORD					m_dwHonorCheckTime;			//0x794
	int						m_aHonorTitle[MAX_HONOR_TITLE];	 //0x798 
	char*					m_strTitle;					//0x9F0
	DWORD					m_dwMute;					//0x9F4
	RESURRECTION_DATA		m_Resurrection_Data;		//0x9F8
	vInventory*				m_ShopInventory[ MAX_VENDOR_INVENTORY_TAB ]; //CItemContainer< CItemElem  >*	m_ShopInventory[ MAX_VENDOR_INVENTORY_TAB ]; //0xA0C
	byte					bUnknwInven[ 0x1C ];		//CItemContainer< CItemElem  >	m_Inventory;			//0xA1C
	byte					bXPocketController[ 0x74 ];	//CPocketController	m_Pocket;						//0xA38
	byte					bXArray[ 0x3E8 ];			//EQUIP_INFO		m_aEquipInfo[MAX_HUMAN_PARTS];	//0xAAC
	CVTInfo					m_vtInfo;					//0xE94
	byte					m_nSlot;					//0xF38
	BOOL					m_bBank;					//0xF3C
	u_long					m_idPlayerBank[3];			//0xF40
	DWORD					m_dwGoldBank[3];			//0xF4C
	byte					bUnknwBank[ 0x1C * 3];		//CItemContainer< CItemElem >	m_Bank[3];		//0xF58
	byte					m_nQuestKeeping;			//0xFAC
	byte					m_nPartyQuestKeeping;		//0xFAD
	DWORD					m_nQuestSize;				//0xFB0
	QUEST*					m_aQuest;					//0xFB4
	DWORD					m_nCompleteQuestSize;		//0xFB8
	WORD*	   				m_aCompleteQuest;			//0xFBC
	byte					m_nCheckedQuestSize;		//0xFC0
	WORD*					m_aCheckedQuest;			//0xFC4
	int						m_nDead;					//0xFC8
	int						m_nGuildCombatState;		//0xFCC
	D3DXVECTOR3				m_vMarkingPos;				//0xFD0
	DWORD					m_idMarkingWorld;			//0xFDC
	CNpcProperty*			m_pNpcProperty;				//0xFE0
	time_t					m_timerQuestLimitTime;		//0xFE8
	byte					xUnkn06[ 0x18 ];			//0xFF0
	DWORD					m_dwPKTargetLimit;			//0x1008	
	DWORD					m_dwTickCreated;			//0x100C
	BOOL					m_bLastPK;					//0x1010
	BOOL					m_bLastDuelParty;			//0x1014
	time_t					m_tGuildMember;				//0x1018
	BOOL					m_bGuildCombat;				//0x1020
	CSfxHitArray			m_sfxHitArray;				//0x1024 >> 25C
	byte					bXUNknwMap[ 0x28 ];			//0x1280 	map< OBJID, queue< SFXHIT_INFO> >	m_mapSFXInfo;	//
	byte					bXUNknwMap1[ 0x28 ];		//0x12A8 	map< OBJID, queue< SFXHIT_COUNT > >	m_mapSFXCount;	// >> 0x28
	DWORD					m_dwPetId;					//0x12D0
	DWORD					m_dwMoverSfxId;				//0x12D4
	DWORD					m_objIdVisPet;				//0x12D8
	int						m_nMaxCltTime;				//0x12DC
	int						m_nCltTime;					//0x12E0
	int						m_nSkillLevel;				//0x12E4
	int						m_nSkillPoint;				//0x12E8
	int						m_SkillTimer;				//0x12EC
	byte					x[ 0x1E ];					//0x12F4
	BOOL					m_SkillTimerStop;			//0x1310
	BOOL					m_pAngelFlag;				//0x1314
	void*					m_pAngel;					//0x1318
	D3DXVECTOR3				m_AngelPos;					//0x131C
	D3DXMATRIX				m_AngelWorldM;				//0x1328
	DWORD					m_dwAngelKind;				//0x1368
	BOOL					m_pBalloonFlag;				//0x136C
	void*					m_pBalloon;					//0x1370
	D3DXVECTOR3				m_BalloonPos;				//0x137C
	D3DXMATRIX				m_BalloonWorldM;			//0x13BC
	DWORD					m_dwBalloonKind;			//0x13C0
	float					m_fBalloonYPos;				//0x13C4
	BOOL					m_bBalloon;					//0x13C8		
	
private:
	byte					bMapIdEnemies[ 0xC ];		//0x13CC > 13CC
	OBJACT					m_oaCmd;					//0x13D8
	int						m_nCParam[3];				//0x13DC
	OBJACT					m_oaAct;					//0x13E8
	int						m_nAParam[5];				//0x13EC
	long					m_adjParamAry[ MAX_ADJPARAMARY ];	//0x1400
	long					m_chgParamAry[ MAX_ADJPARAMARY ];	//0x15D4
	BOOL					m_bRegenItem;				//0x17A8
	int						m_nMovePattern;				//0x17AC
	int						m_nMoveEvent;				//0x17B0	
	int						m_nMoveEventCnt;			//0x17B4	
	u_long					m_idCampus;					//0x17B8
	int						m_nCampusPoint;				//0x17BC

protected:
	int						m_nCount;					//0x17C0
	DWORD					m_dwGold;					//0x17C4
	DWORD					m_dwRideItemIdx;			//0x17C8
	void*					m_pRide;					//0x17CC 
	char					m_szName[MAX_NAME];			//0x17D0
	DWORD					xUnkn05;					//0x1810
	BOOL					m_bPVPEnd;					//0x1814
	DWORD					xUnkn02;					//0x1818
	DWORD					xUnkn03;					//0x181C
	DWORD					xUnkn04;					//0x1820
};

//007816C8 madrigal gift ptr
