#pragma once
#include "stdafx.h"

#include "defineJob.h"

enum ePropType{ NO_PROP = 0, FIRE, WATER, ELECTRICITY, WIND, EARTH, END_PROP };

typedef struct tagExpCharacter
{
	__int64	nExp1;
	__int64	nExp2;
	DWORD dwLPPoint;
	__int64	nLimitExp;
}
EXPCHARACTER, *LPEXPCHARACTER;

typedef struct tagJOB
{
	char	szName[ 32 ];
	char	szEName[ 32 ];
	DWORD	dwJobBase;
	DWORD	dwJobType;

} JOB,* LPJOB;

typedef	struct	tagPLAY_ACCOUNT
{
	TCHAR	lpszAccount[36];
	SYSTEMTIME	m_stLogin;
	TCHAR	lpAddr[16];	
}PLAY_ACCOUNT;


struct REGIONELEM
{
	float			m_fTeleAngle;
	D3DXVECTOR3		m_vTeleWorld;  
	D3DXVECTOR3		m_vPos;  
	char			m_szName[32];
	char			m_szKey[32];	
	DWORD			m_dwIdTeleWorld;
	char			m_szSound[32];
	char			m_szScript[32];
	DWORD			m_dwAttribute;
	RECT			m_rect;
	bool			m_bInside;
	char			m_cDescSize;

	char			m_szDesc [ MAX_REGIONDESC  ];
	char			m_szTitle[ MAX_REGIONTITLE ];
	union
	{
		bool		m_bDirectMusic;
		bool		m_bUnit;
	};

	bool			m_bPlayDirectMusic;
	bool			m_bTargetKey;

	union
	{
		DWORD		m_dwStructure;
		DWORD       m_dwIdMusic;
	};
	DWORD			m_dwWorldId;
	DWORD			m_dwIndex;

	DWORD			m_uItemId;
	UINT			m_uiItemCount;
	UINT			m_uiMinLevel;
	UINT			m_uiMaxLevel;
	int				m_iQuest;
	int				m_iQuestFlag;
	int				m_iJob;
	int				m_iGender;
	BOOL			m_bCheckParty;
	BOOL			m_bCheckGuild;
	BOOL			m_bChaoKey;
};
typedef REGIONELEM*  LPREGIONELEM;

enum REPLACE_TYPE
{
	REPLACE_NORMAL,
	REPLACE_FORCE,
};

typedef	REGIONELEM	RegionElem, *PRegionElem;

typedef struct tagWORLD
{
	char	m_szFileName[128];
	char	m_szWorldName[128];
	DWORD	m_dwId;
	BOOL	IsValid()	{	return( m_szFileName[0] != '\0' );	}
}
WORLD,* LPWORLD;

typedef	struct	tagRANDOM_ITEM
{
	BYTE	m_lpQuestFlagArray[ITEM_KIND_MAX / 8 + 1];

	void	SetItemKind( int nItemKind,BOOL bBool );
	BOOL	IsItemKind( int nItemKind );

	BYTE	m_nTotalNum;
	BYTE	m_nUniqueMax;
	BYTE	m_nUniqueMin;
	WORD	m_nGoldMax;
	WORD	m_nAmmoMax;
	WORD	m_nDartMax;
	WORD	m_nGoldMin;
	WORD	m_nAmmoMin;
	WORD	m_nDartMin;
	tagRANDOM_ITEM()
	{
		m_nTotalNum		= 0;
		m_nUniqueMax	= 0;
		m_nUniqueMin	= 0;
		m_nGoldMax		= 0;
		m_nAmmoMax		= 0;
		m_nDartMax		= 0;
		m_nGoldMin		= 0;
		m_nAmmoMin		= 0;
		m_nDartMin		= 0;
	}
}
RANDOM_ITEM,* LPRANDOM_ITEM;

typedef DWORD DPID, FAR *LPDPID;

typedef struct tagCHARACTER
{
	// 	CHAR			m_szKey[ 64 ];
	// 	CString			m_strName;
	// 	CHAR			m_szChar[ 64 ];
	// 	CHAR			m_szDialog[ 64 ];
	// 	CHAR			m_szDlgQuest[ 64 ];
	// 	int				m_nStructure;
	// 	int				m_nEquipNum;
	// 	DWORD			m_dwMoverIdx;
	// 	DWORD			m_dwMusicId;
	// 	DWORD			m_adwEquip[ MAX_HUMAN_PARTS ];
	// 	DWORD			m_dwHairMesh;
	// 	DWORD			m_dwHairColor;
	// 	DWORD			m_dwHeadMesh;
	// 	RANDOM_ITEM		m_randomItem;
	// 	BOOL			m_abMoverMenu[ MAX_MOVER_MENU ];
	// 	CString			m_venderSlot[ 4 ];
	// 	CPtrArray		m_venderItemAry[ 4 ];
	// 
	// 	CWordArray		m_awSrcQuest;
	// 	CWordArray		m_awDstQuest;
	// 	CUIntArray		m_anSrcQuestItem; 
	// 	CUIntArray		m_anDstQuestItem; 
	// 	void Clear();
	// 
	// 	int				m_nVenderType;
	// 	CPtrArray		m_venderItemAry2[ 4 ];
	// 	vector<NPC_BUFF_SKILL> m_vecNPCBuffSkill;
	// 	vector<DWORD>	m_vecdwLanguage;
	// 	BOOL			bOutput;
	// 	DWORD			m_dwWorldId;
	// 	D3DXVECTOR3		m_vPos;
	// 	vector<D3DXVECTOR3> m_vecTeleportPos;
} CHARACTER,* LPCHARACTER;

struct BOUND_BOX
{
	D3DXVECTOR3		m_vPos[8];
};


struct vObjProp
{
	DWORD	dwID;
	char	szName[64];
	DWORD	dwType; 
	DWORD	dwAI;
	DWORD	dwHP;

	vObjProp()
	{
		*szName	= '\0';
		dwID = dwType = dwAI	= dwHP	= 0;
	}
};

struct vCtrlProp : vObjProp
{
	DWORD   dwCtrlKind1;
	DWORD   dwCtrlKind2;
	DWORD   dwCtrlKind3;
	DWORD   dwSfxCtrl;
	DWORD   dwSndDamage;

	vCtrlProp() : vObjProp()
	{
		dwCtrlKind1	= dwCtrlKind2	= dwCtrlKind3	= dwSfxCtrl	= dwSndDamage	= 0;
	}


	BOOL IsGuildHousingObj( )	{ return CK1_GUILD_HOUSE == dwCtrlKind1; }
	BOOL IsHousingObj( )		{ return CK1_HOUSING == dwCtrlKind1; }
};

struct vItemProp : vCtrlProp
{
	DWORD		dwMotion;
	DWORD		dwNum;
	DWORD		dwPackMax;
	DWORD		dwItemKind1;
	DWORD		dwItemKind2;
	DWORD		dwItemKind3;
	DWORD		dwItemJob;
	BOOL		bPermanence;
	DWORD		dwUseable;
	DWORD		dwItemSex;
	DWORD		dwCost;
	DWORD		dwEndurance;
	int			nLog;	
	int			nAbrasion;
	int			nMaxRepair;
	DWORD		dwHanded;
	DWORD		dwFlag;
	DWORD		dwParts;
	DWORD		dwPartsub;
	DWORD		bPartsFile;
	DWORD		dwExclusive;
	DWORD		dwBasePartsIgnore;
	DWORD		dwItemLV;
	DWORD		dwItemRare;
	DWORD		dwShopAble;
	int			nShellQuantity;
	DWORD		dwActiveSkillLv;
	DWORD		dwFuelRe;
	DWORD		dwAFuelReMax;
	DWORD		dwSpellType;
	DWORD		dwLinkKindBullet;
	DWORD		dwLinkKind;
	DWORD		dwAbilityMin;
	DWORD		dwAbilityMax;
	BOOL		bCharged;		
	ePropType	eItemType;
	short		wItemEatk;
	DWORD		dwParry;
	DWORD		dwblockRating;
	int			nAddSkillMin;
	int			nAddSkillMax;
	DWORD		dwAtkStyle;
	DWORD		dwWeaponType;
	DWORD		dwItemAtkOrder1;
	DWORD		dwItemAtkOrder2;
	DWORD		dwItemAtkOrder3;
	DWORD		dwItemAtkOrder4;
	DWORD		tmContinuousPain;
	DWORD		dwRecoil;
	DWORD		dwLoadingTime;
	LONG		nAdjHitRate;
	float		fAttackSpeed;
	DWORD		dwDmgShift;
	DWORD		dwAttackRange;
	int			nProbability;

	DWORD		dwDestParam[6];
	LONG		nAdjParamVal[6];
	DWORD		dwChgParamVal[6];
	int			nDestData1[6];

	DWORD		dwActiveSkill;
	DWORD		dwActiveSkillRate;
	DWORD		dwReqMp;
	DWORD		dwReqFp;
	DWORD		dwReqDisLV;
	DWORD		dwReSkill1;
	DWORD		dwReSkillLevel1;
	DWORD		dwReSkill2;
	DWORD		dwReSkillLevel2;
	DWORD		dwSkillReadyType;
	DWORD		dwSkillReady;
	DWORD		_dwSkillRange;
	DWORD		dwSfxElemental;
	DWORD		dwSfxObj;
	DWORD		dwSfxObj2;
	DWORD		dwSfxObj3;
	DWORD		dwSfxObj4;
	DWORD		dwSfxObj5;
	DWORD		dwUseMotion;
	DWORD		dwCircleTime;
	DWORD		dwSkillTime;
	DWORD		dwExeTarget;
	DWORD		dwUseChance;
	DWORD		dwSpellRegion;
	DWORD		dwReferStat1;
	DWORD		dwReferStat2;
	DWORD		dwReferTarget1;
	DWORD		dwReferTarget2;
	DWORD		dwReferValue1;
	DWORD		dwReferValue2;
	DWORD		dwSkillType;
	int			nItemResistElecricity;
	int			nItemResistDark;
	int			nItemResistFire;
	int			nItemResistWind;
	int			nItemResistWater;
	int			nItemResistEarth;
	long		nEvildoing;
	DWORD		dwExpertLV;
	DWORD		dwExpertMax;
	DWORD		dwSubDefine;
	DWORD		dwExp;
	DWORD		dwComboStyle;
	float		fFlightSpeed;
	float		fFlightLRAngle;
	float		fFlightTBAngle;
	DWORD		dwFlightLimit;
	DWORD		dwFFuelReMax;
	DWORD		dwLimitLevel1;
	int			nReflect;
	DWORD		dwSndAttack1;
	DWORD		dwSndAttack2;
	DWORD		dwQuestId;
	char		szTextFileName[64];
	int			nMinLimitLevel;
	int			nMaxLimitLevel;
	int			nItemGroup;
	int			nUseLimitGroup;
	int			nMaxDuplication;
	int			nEffectValue;
	int			nTargetMinEnchant;
	int			nTargetMaxEnchant;
	BOOL		bResetBind;
	int			nBindCondition;
	int			nResetBindCondition;
	DWORD		dwHitActiveSkillId;
	DWORD		dwHitActiveSkillLv;
	DWORD		dwHitActiveSkillProb;
	DWORD		dwHitActiveSkillTarget;
	DWORD		dwDamageActiveSkillId;
	DWORD		dwDamageActiveSkillLv;
	DWORD		dwDamageActiveSkillProb;
	DWORD		dwDamageActiveSkillTarget;	
	DWORD		dwEquipActiveSkillId;
	DWORD		dwEquipActiveSkillLv;
	DWORD		dwSmelting;
	DWORD		dwAttsmelting;
	DWORD		dwGemsmelting;
	DWORD		dwPierce;
	DWORD		dwUprouse;
	BOOL		bAbsoluteTime;
	DWORD		dwItemGrade;
	BOOL		bCanTrade;
	DWORD		dwMainCategory;	
	DWORD		dwSubCategory;
	BOOL		bCanHaveServerTransform;
	BOOL		bCanSavePotion;
	BOOL		bCanLooksChange;
	BOOL		blsLooksChangeMaterial;

	DWORD	GetCoolTime()  { return dwSkillReady; }

	BOOL	IsUltimate( void )
	{
		return( ( dwItemKind2 == IK2_WEAPON_DIRECT || dwItemKind2 == IK2_WEAPON_MAGIC ) && dwReferStat1 == WEAPON_ULTIMATE );
	}

	BOOL	IsVisPet()	{ return (dwItemKind3 == IK3_PET) && (dwReferStat1 == PET_VIS); }
	BOOL	IsVis()		{ return (dwItemKind3 == IK3_VIS ); }

};

const DWORD		OBJ_FLAG_DELETE					= 0x00000001;
const DWORD     OBJ_FLAG_VISIBLE				= 0x00000002;
const DWORD     OBJ_FLAG_VIRTUAL				= 0x00000004;
const DWORD     OBJ_FLAG_UPDATEMATRIX			= 0x00000008;
const DWORD     OBJ_FLAG_POSCHANGED				= 0x00000010;
const DWORD		OBJ_FLAG_VISIBLE_COLLISION		= 0x00000020;
const int		PETVIS_DEFAULT_VIS_SLOT_SZIE	= 2;
const DWORD		NEXT_TICK_DUEL					= SEC(1);
const DWORD		NEXT_TICK_ENDDUEL				= MIN(3);
const DWORD		NEXT_TICK_RECOVERY				= SEC(2);
const DWORD		NEXT_TICK_RECOVERYSTAND			= SEC(3);
const int		MAX_PROPMOVER					= 2000;

struct MonsterTransform
{
	float fHPRate;
	DWORD dwMonsterId;
	MonsterTransform() : fHPRate( 0.0f ), dwMonsterId( 0xffffffff ) {}
};

struct MoverProp : vCtrlProp
{
	DWORD	dwStr;                
	DWORD	dwSta;
	DWORD	dwDex;
	DWORD	dwInt;
	DWORD	dwHR;
	DWORD   dwER;
	DWORD	dwRace;
	DWORD	dwBelligerence;
	DWORD	dwGender;
	DWORD	dwLevel;
	DWORD	dwFlightLevel;
	DWORD	dwSize;
	DWORD   dwClass;
	BOOL	bIfParts;
	int		nChaotic;
	DWORD	dwUseable;
	DWORD	dwActionRadius;
	DWORD	dwAtkMin;
	DWORD	dwAtkMax;
	DWORD	dwAtk1;
	DWORD	dwAtk2;
	DWORD	dwAtk3;
	DWORD	dwAtk4;
	FLOAT	fFrame;
	DWORD	dwOrthograde;
	DWORD	dwThrustRate;
	DWORD	dwChestRate;
	DWORD	dwHeadRate;  
	DWORD	dwArmRate;
	DWORD	dwLegRate;
	DWORD	dwAttackSpeed;
	DWORD	dwReAttackDelay;
	DWORD	dwAddHp;
	DWORD	dwAddMp;
	DWORD	dwNaturalArmor;	
	int		nAbrasion;
	int		nHardness;
	DWORD	dwAdjAtkDelay;

	ePropType	eElementType;
	short	wElementAtk;

	DWORD	dwHideLevel;
	float	fSpeed;
	DWORD	dwShelter;
	DWORD	dwFlying;
	DWORD	dwJumpIng;
	DWORD	dwAirJump;
	DWORD	bTaming;
	DWORD	dwResisMgic; 

	int		nResistElecricity;
	int		nResistDark;
	int		nResistFire;
	int		nResistWind;
	int		nResistWater;
	int		nResistEarth;

	DWORD	dwCash;
	DWORD	dwSourceMaterial;
	DWORD	dwMaterialAmount;
	DWORD	dwCohesion;
	DWORD	dwHoldingTime;
	DWORD	dwCorrectionValue;
	__int64	nExpValue;
	int		nFxpValue;
	DWORD	nBodyState;
	DWORD	dwAddAbility;
	DWORD	bKillable;

	DWORD	dwVirtItem[3];
	DWORD	bVirtType[3]; 

	DWORD   dwSndAtk1;
	DWORD   dwSndAtk2;
	DWORD   dwSndDie1;
	DWORD   dwSndDie2;
	DWORD   dwSndDmg1;
	DWORD   dwSndDmg2;
	DWORD   dwSndDmg3;
	DWORD   dwSndIdle1;
	DWORD   dwSndIdle2;

	short   m_nEvasionHP;
	short	m_nEvasionSec;
	short   m_nRunawayHP;
	short   m_nCallHelperMax;
	short   m_nCallHP;
	short   m_nCallHelperIdx  [ 5 ];
	short   m_nCallHelperNum  [ 5 ];
	short   m_bCallHelperParty[ 5 ];

	short   m_dwAttackMoveDelay;
	short   m_dwRunawayDelay;
	short   m_bPartyAttack;
	short   m_nHelperNum;


	int		m_nScanJob;
	int		m_nHPCond;
	int		m_nLvCond;
	int		m_nRecvCondMe;
	int		m_nRecvCondHow;
	int		m_nRecvCondMP;
	byte	m_bMeleeAttack;
	byte	m_bRecvCondWho;
	byte	m_bRecvCond;
	byte	m_bHelpWho;
	byte	m_bRangeAttack[ MAX_JOB ];
	int		m_nSummProb;
	int		m_nSummNum;
	int		m_nSummID;
	int		m_nHelpRangeMul;
	DWORD	m_tmUnitHelp;
	int		m_nBerserkHP;
	float	m_fBerserkDmgMul;
	int		m_nLoot;
	int		m_nLootProb;
	DWORD   m_dwScanQuestId; 
	DWORD   m_dwScanItemIdx; 
	int		m_nScanChao;

	float	m_fHitPoint_Rate;
	float	m_fAttackPower_Rate;
	float	m_fDefence_Rate;
	float	m_fExp_Rate;
	float	m_fItemDrop_Rate;
	float	m_fPenya_Rate;
	BOOL	m_bRate;



	short	m_nAttackItemNear;
	short	m_nAttackItemFar;
	short	m_nAttackItem1;
	short	m_nAttackItem2;
	short	m_nAttackItem3;
	short	m_nAttackItem4;
	short	m_nAttackItemSec;
	short	m_nMagicReflection;
	short	m_nImmortality;
	BOOL 	m_bBlow;
	short	m_nChangeTargetRand;

	short   m_nAttackFirstRange;
	RANDOM_ITEM		m_randomItem  ;
	/*CDropItemGenerator*/void*	m_DropItemGenerator;
	/*CQuestItemGenerator*/void*	m_QuestItemGenerator;
	/*CDropKindGenerator*/void*	m_DropKindGenerator;
	MonsterTransform	m_MonsterTransform;


	MoverProp()
	{
		dwStr	= dwSta	= dwDex	= dwInt	= dwHR	= dwER	= dwRace	= dwBelligerence	=dwGender
			= dwLevel	= dwFlightLevel	= dwSize	= dwClass	= bIfParts	= nChaotic
			= dwUseable
			= dwActionRadius	= dwAtkMin	= dwAtkMax	= dwAtk1	= dwAtk2	= dwAtk3	= dwAtk4	= 0;
		fFrame	= 1.0F;
		dwOrthograde	= 0;
		dwThrustRate		= 0;
		dwChestRate			= 0;
		dwHeadRate			= 0;
		dwArmRate			= 0;
		dwLegRate			= 0;
		dwAttackSpeed		= 0;
		dwReAttackDelay		= 0;
		dwAddHp				= 0;
		dwAddMp				= 0;
		dwNaturalArmor		= 0;
		nAbrasion			= 0;
		nHardness			= 0;
		dwAdjAtkDelay		= 0;
		dwHideLevel			= 0;
		eElementType		= NO_PROP;
		wElementAtk			= 0;
		fSpeed				= 0.0F;
		dwShelter			= 0;
		dwFlying			= 0;
		dwJumpIng			= 0;
		dwAirJump			= 0;
		bTaming				= 0;
		dwResisMgic			= 0;
		nResistElecricity	= 0;
		nResistDark			= 0;
		nResistFire			= 0;
		nResistWind			= 0;
		nResistWater		= 0;
		nResistEarth		= 0;
		dwCash				= 0;
		dwSourceMaterial	= 0;
		dwMaterialAmount	= 0;
		dwCohesion			= 0;
		dwHoldingTime		= 0;
		dwCorrectionValue	= 0;
		nExpValue			= 0;
		nFxpValue			= 0;
		nBodyState			= 0;
		dwAddAbility		= 0;
		bKillable			= 0;

		memset( dwVirtItem, 0, sizeof(dwVirtItem) );
		memset( bVirtType, 0, sizeof(bVirtType) );

		dwSndAtk1			= 0;
		dwSndAtk2			= 0;
		dwSndDie1			= 0;
		dwSndDie2			= 0;
		dwSndDmg1			= 0;
		dwSndDmg2			= 0;
		dwSndDmg3			= 0;
		dwSndIdle1			= 0;
		dwSndIdle2			= 0;
		m_nEvasionHP		= 0;
		m_nEvasionSec		= 0;
		m_nRunawayHP		= 0;
		m_nCallHelperMax	= 0;
		m_nCallHP			= 0;

		memset( m_nCallHelperIdx, 0, sizeof(m_nCallHelperIdx) );
		memset( m_nCallHelperNum, 0, sizeof(m_nCallHelperNum) );
		memset( m_bCallHelperParty, 0, sizeof(m_bCallHelperParty) );

		m_dwAttackMoveDelay	= 0;
		m_dwRunawayDelay	= 0;
		m_bPartyAttack		= 0;
		m_nHelperNum		= 0;


		m_nScanJob			= 0;
		m_nHPCond			= 0;
		m_nLvCond			= 0;
		m_nRecvCondMe		= 0;
		m_nRecvCondHow		= 0;
		m_nRecvCondMP		= 0;
		m_bMeleeAttack		= 0;
		m_bRecvCondWho		= 0;
		m_bRecvCond			= 0;
		m_bHelpWho			= 0;
		memset( m_bRangeAttack, 0, sizeof(m_bRangeAttack) );
		m_nSummProb			= 0;
		m_nSummNum			= 0;
		m_nSummID			= 0;
		m_nHelpRangeMul		= 0;
		m_tmUnitHelp		= 0;
		m_nBerserkHP		= 0;
		m_fBerserkDmgMul	= 0;
		m_nLoot				= 0;
		m_nLootProb			= 0;
		m_dwScanQuestId		= 0;
		m_dwScanItemIdx		= 0;
		m_nScanChao			= 0;


		m_fHitPoint_Rate = m_fAttackPower_Rate = m_fDefence_Rate = m_fExp_Rate = m_fItemDrop_Rate = m_fPenya_Rate = 0.0F;

		m_bRate	= m_nAttackItemNear = m_nAttackItemFar = m_nAttackItem1	= m_nAttackItem2 = m_nAttackItem3 = m_nAttackItem4 = m_nAttackItemSec = m_nMagicReflection = m_nImmortality = m_bBlow = 
			m_nChangeTargetRand	= m_nAttackFirstRange = 0;
	}
};


class vItemBase
{
public:
	DWORD      m_dwObjId;
	DWORD	m_dwObjIndex;
	DWORD	m_dwItemId;
	int 	m_nExtra;
	char	m_szItemText[ 32 ];
	int		m_nCost;

private:
	DWORD	m_liSerialNumber;

public:
	inline	bool	IsEmpty()								{ return m_dwItemId ? false : true;	 }
	inline	DWORD	GetSerialNumber( void )					{	return m_liSerialNumber;	}
	inline	void	SetSerialNumber( DWORD liSerialNumber )	{	m_liSerialNumber	= liSerialNumber;	}
};


struct vAddSkillProp
{
	DWORD	dwID;				// 변수명	
	DWORD	dwName;				// 명칭
	DWORD	dwSkillLvl;			// 스킬레벨
	DWORD	dwAbilityMin;		// 최소능력
	DWORD	dwAbilityMax;		// 최대능력
	DWORD	dwAttackSpeed;		// 공격속도
	DWORD	dwDmgShift;			// 타격시 반동
	DWORD	nProbability;		// 발동 확률
	DWORD	dwTaunt;			// 타운트
	DWORD	dwDestParam[2];		// 적용대상1
	DWORD	nAdjParamVal[2];	// 적용값1;
	DWORD	dwChgParamVal[2];	//적용변화값1
	int		nDestData1[3];		// 적용데이타3개, DestParam[0]에 해당.
	DWORD	dwActiveSkill;		// 발동 마법
	DWORD	dwActiveSkillRate;	// 발동 마법 확률.
#if __VER >= 9	// __SKILL_0706
	DWORD	dwActiveSkillRatePVP;	// 대인 발동 마법 확률.
#endif	// __SKILL_0706
	int		nReqMp;				//필요MP
	int		nReqFp;				//필요FP
#if __VER >= 9	// __SKILL_0706
	DWORD	dwCooldown;		// 쿨다운
	DWORD	dwCastingTime;		//기술 준비시간
#else	// __SKILL_0706
	DWORD	dwSkillReady;		//기술 준비시간
#endif	// __SKILL_0706
	DWORD	dwSkillRange;		// 기술 시전거리	
	DWORD	dwCircleTime;		//유지시간
	DWORD   dwPainTime;         // 지속 피해시간
	DWORD	dwSkillTime;		//지속시간
	int		nSkillCount;		// 발사체 발사 개수. 개당공격력 = 총공격력 / nSkillCount;
	DWORD   dwSkillExp;         //스킬 경험치
	DWORD	dwExp;				//현재경험치
	DWORD	dwComboSkillTime;	//콤보스킬타임
#if __VER >= 9	// __SKILL_0706
	DWORD	dwAbilityMinPVP;	// 최소능력(대인)
	DWORD	dwAbilityMaxPVP;	// 최대능력(대인)
	DWORD	nProbabilityPVP;	// 발동 확률(대인)
#endif	// __SKILL_0706

	vAddSkillProp()
	{
		dwID = dwName = 0;
		nProbability = 0;
		dwSkillLvl = dwAbilityMin = dwAbilityMax = dwAttackSpeed = dwDmgShift = dwTaunt = 0;
		dwDestParam[0] = dwDestParam[1] = nAdjParamVal[0] = nAdjParamVal[1] = dwChgParamVal[0] = dwChgParamVal[1] = 0;
		nReqMp = nReqFp = 0;
		dwActiveSkillRate	= 0;
#if __VER >= 9	// __SKILL_0706
		dwCastingTime	= 0;
		dwAbilityMinPVP		= 0;
		dwAbilityMaxPVP		= 0;
		dwCooldown	= 0;
		nProbabilityPVP	= 0;
		dwActiveSkillRatePVP	= 0;
#else	// __SKILL_0706
		dwSkillReady = 0;
#endif	// __SKILL_0706
		dwCircleTime = dwSkillTime = dwExp = dwComboSkillTime = 0;
	}
};

#define			MAX_CTRLDROPITEM		4
#define			MAX_CTRLDROPMOB			3
#define			MAX_TRAP                3

#define			MAX_KEY					64

#define         OPEN_COOLTIME			SEC(10)

typedef struct vCtrlElem
{
	DWORD		m_dwSet;				    //-열기조건 설정 UA_ITEM, UA_LEVEL...
	DWORD 		m_dwSetItem;				//-박스 오픈 조건(아이템)								- UA_ITEM
	DWORD		m_dwSetLevel;				//-박스 오픈 조건(레벨)									- UA_LEVEL
	DWORD		m_dwSetQuestNum;			//-박스 오픈 조건(퀘스트 넘버,퀘스트 플래그 넘버)       - UA_QUEST
	DWORD		m_dwSetFlagNum;
	DWORD		m_dwSetGender;				//-박스 오픈 조건(성별)									- UA_GENDER
	BOOL		m_bSetJob[32];			//-박스 오픈 조건(클래스)								- UA_CLASS

	DWORD		m_dwSetEndu;				//-박스 내구도 ? hp와 같이 적용	

	DWORD		m_dwMinItemNum;				//-최소 발생 아이템 수 
	DWORD		m_dwMaxiItemNum;			//-최대 발생 아이템 수
	DWORD		m_dwInsideItemKind[MAX_CTRLDROPITEM];		//-들어가는 아이템 종류 값 !!!주의!!! 마지막 MAX_CTRLDROPITEM-1 은 레어 아템공간
	DWORD		m_dwInsideItemPer [MAX_CTRLDROPITEM];		//-들어가는 아이템 의 발생 확룰( 3000000000 )

	DWORD       m_dwMonResKind  [MAX_CTRLDROPMOB];          //-몬스터1 발생 종류(몬스터 아이디 입력)
	DWORD		m_dwMonResNum   [MAX_CTRLDROPMOB];			//-몬스터1 발생 수량
	DWORD		m_dwMonActAttack[MAX_CTRLDROPMOB];			//-몬스터 타입1에서 선공 몬스터 발생 수량(위에 필드 수량 초과해서는 않됨)

	// 트랩관련
	DWORD		m_dwTrapOperType;              // 트랩 발동 타입 TOT_RANDOM, TOT_NOENDU
	DWORD		m_dwTrapRandomPer;             // 트랩 발동 확율(TOT_RANDOM일경우)
	DWORD		m_dwTrapDelay;				   // 트랩 발동 딜레이 0이면 즉시 발생

	DWORD		m_dwTrapKind	[MAX_TRAP];    // 트랩 종류 - 가상 스킬로 사용함 모든 트랩은 스킬임 (스킬프로퍼티의 ID값)
	DWORD		m_dwTrapLevel	[MAX_TRAP];
	TCHAR		m_strLinkCtrlKey[MAX_KEY];		// 연결 컨트롤의 키 이름
	TCHAR		m_strCtrlKey[MAX_KEY];			// 컨트롤의 키 이름
	DWORD		m_dwSetQuestNum1;			//-박스 열고난후 적용(퀘스트 넘버,퀘스트 플래그 넘버)       - UA_QUEST
	DWORD		m_dwSetFlagNum1;
	DWORD		m_dwSetQuestNum2;			//-박스 열고난후 적용(퀘스트 넘버,퀘스트 플래그 넘버)       - UA_QUEST
	DWORD		m_dwSetFlagNum2;
	DWORD 		m_dwSetItemCount;
	DWORD		m_dwTeleWorldId;
	DWORD		m_dwTeleX;
	DWORD		m_dwTeleY;
	DWORD		m_dwTeleZ;

} vCtrlElem, *LPCtrlElem;


class BBOX
{
public:
	D3DXVECTOR3		Center;
	float			Extent[3];
	D3DXVECTOR3		Axis[3];
};						  


typedef struct _CHAO_PROPENSITY
{
	DWORD	dwPropensityMin;		/// 성향 수치 Min
	DWORD	dwPropensityMax;		/// 성향 수치 Max
	int		nEquipDorpMin;			/// 착용아이템 드롭 개수 Min
	int		nEquipDorpMax;			/// 착용아이템 드롭 개수 Max
	int		nInvenDorpMin;			/// 인벤아이템 드롭 개수 Min
	int		nInvenDorpMax;			/// 인벤아이템 드롭 개수 Max
	int		nShop;					/// 상점 이용 유/무
	int		nBank;					/// 창고 이용 유/무
	int		nFly;					/// 비행 이용 유/무
	int		nGuardAttack;			/// 경비병 공격 유/무
	int		nVendor;				/// 개인상점 이용 및 개설 유/무
	_CHAO_PROPENSITY()
	{
		dwPropensityMin = 0;
		dwPropensityMax = 0;
		nEquipDorpMin = 0;
		nEquipDorpMax = 0;
		nInvenDorpMin = 0;
		nInvenDorpMax = 0;
		nShop = 1;
		nBank = 1;
		nFly = 1;
		nGuardAttack = 1;
		nVendor = 1;
	}
} CHAO_PROPENSITY, *PCHAO_PROPENSITY;

struct vItemElem : public vItemBase
{//264
	int			m_nAbilityOption;

	enum	{	expired	= 0x01,	binds	= 0x02,	isusing	= 0x04,	};

	int			m_nRepair;
	BYTE		m_nRepairNumber;
	int			m_nHitPoint;
	short		m_nItemNum; 
	BYTE		m_byFlag;
	DWORD		m_idGuild;
};

struct JobProp
{
	float	fAttackSpeed;
	float	fFactorMaxHP;
	float	fFactorMaxMP;
	float	fFactorMaxFP;
	float   fFactorDef;
	float	fFactorHPRecovery;
	float	fFactorMPRecovery;
	float	fFactorFPRecovery;
	float	fMeleeSWD;
	float	fMeleeAXE;
	float   fMeleeSTAFF;
	float   fMeleeSTICK;
	float   fMeleeKNUCKLE;
	float   fMagicWAND;
	float   fBlocking;
	float	fMeleeYOYO;
	float   fCritical;
};

enum
{
	AIMSG_INIT = 1,
	AIMSG_PROCESS, 
	AIMSG_TIMEOUT,
	AIMSG_SETSTATE,
	AIMSG_SETPROCESS,
	AIMSG_DSTDAMAGE,
	AIMSG_DSTDIE,
	AIMSG_DAMAGE,
	AIMSG_DIE,
	AIMSG_COLLISION,
	AIMSG_ARRIVAL,
	AIMSG_NOMOVE,
	AIMSG_BEGINMOVE,
	AIMSG_ATTACK_MELEE,
	AIMSG_END_MELEEATTACK,
	AIMSG_END_APPEAR,
	AIMSG_INIT_TARGETCLEAR,
	AIMSG_EXIT,
	AIMSG_TARGET_FIND,
	AIMSG_REATTACK_TIMEOUT,
	AIMSG_INVALID_TARGET,
};

enum AI2_STATE
{
	AI2_IDLE,
	AI2_MOVE,
	AI2_RAGE,
	AI2_SEARCH,
	AI2_TRACKING,
	AI2_ATTACK,
};


enum 
{	
	SM_BANK15, SM_BANK30, SM_PARTYSKILL15, SM_PARTYSKILL30, SM_SHOUT15, SM_SHOUT30, 
	SM_MAINTAIN_MP, SM_MAINTAIN_FP, SM_MAX_HP, SM_MAX_HP50, SM_ACTPOINT,
	SM_STR_DOWN, SM_STA_DOWN, SM_DEX_DOWN, SM_INT_DOWN,
	SM_ATTACK_UP, SM_RESIST_ATTACK_LEFT, SM_RESIST_ATTACK_RIGHT, SM_RESIST_DEFENSE,
	SM_ESCAPE, SM_REVIVAL, SM_VELOCIJUMP, SM_PARTYSKILL1, SM_ATTACK_UP1, 
	SM_SHOUT001, SM_BANK001, XXUNKWN,
	SM_MAX  
};

enum OBJACT
{
	OBJACT_NONE,
	OBJACT_MELEE_ATTACK,
	OBJACT_MAGIC_ATTACK,
	OBJACT_RANGE_ATTACK,
	OBJACT_SP_ATTACK,
	OBJACT_USESKILL,
	OBJACT_USEITEM,
	OBJACT_COLLECT,

};


typedef	struct tagCORR_ACTION
{
	float		f;
	float		fSpeed;
	DWORD		dwState;
	DWORD		dwStateFlag;
	DWORD		dwMotion;
	int			nMotionEx;
	int			nLoop;
	DWORD		dwMotionOption;
	D3DXVECTOR3	v;
	D3DXVECTOR3	vd;
	float		fAngleX;
	float		fAccPower;
	float		fTurnAngle;
	BOOL		fValid;
	BOOL		fBehavior;
	BOOL		fHalf;
} CORR_ACTION, *PCORR_ACTION;

#define		OBJSTA_NONE					0x00000000	// 아무것도 아닌상태.

// stop/move
#define		OBJSTA_STAND				0x00000001	// 대기상태
#define		OBJSTA_STAND2				0x00000002	// 대기상태EX
#define		OBJSTA_SIT					0x00000003	// 앉기
#define		OBJSTA_FMOVE				0x00000004	// 앞으로 걷기
#define		OBJSTA_BMOVE				0x00000005	// 뒤로 걷기
#define		OBJSTA_LEFT					0x00000006	// 옆으로 걷기(수평이동)
#define		OBJSTA_RIGHT				0x00000007	// 
#define		OBJSTA_PICKUP				0x00000008	// (물건등을)줍다.

#define		OBJSTA_LMOVE				0x00000009	// 수평왼쪽으로 걷기
#define		OBJSTA_RMOVE				0x0000000a	// 스평오른쪽으로 걷기
#define		OBJSTA_STOP_RUN				0x0000000b	// 제자리 뛰기

#define		OBJSTA_MOVE_ALL				0x000000FF
#define		OBJSTA_NOT_STAND			(OBJSTA_MOVE_ALL & (~OBJSTA_STAND))		// STAND이외가 있는가.

// turn
#define		OBJSTA_LTURN				0x00000100	// 좌 턴
#define		OBJSTA_RTURN				0x00000200	// 우 턴
#define		OBJSTA_TURN_ALL				0x00000300	//
// look up/down
#define		OBJSTA_LOOKUP				0x00000400	//
#define		OBJSTA_LOOKDOWN				0x00000800	//
#define		OBJSTA_LOOK_ALL				0x00000C00

// jump
#define		OBJSTA_FJUMP_READY			0x00001000	// 점프전 도약 - 앞점프
#define		OBJSTA_FJUMP				0x00002000	// 점프중
#define		OBJSTA_FFALL				0x00003000	// 떨어지는중
#define		OBJSTA_FLAND				0x00004000	// 착지
#define		OBJSTA_SJUMP1				0x00005000	// 점프전 도약 - 제자리점프
#define		OBJSTA_SJUMP2				0x00006000	// 점프중
#define		OBJSTA_SJUMP3				0x00007000	// 떨어지는중
#define		OBJSTA_SJUMP4				0x00008000	// 착지
#define		OBJSTA_BJUMP_READY			0x00009000	// 점프전 도약 - 백점프
#define		OBJSTA_BJUMP				0x0000a000	// 점프중
#define		OBJSTA_BFALL				0x0000b000	// 떨어지는중
#define		OBJSTA_BLAND				0x0000c000	// 착지
#define		OBJSTA_JUMP_ALL				0x0000F000
// attack
#define		OBJSTA_ATK1					0x00010000	// 1번연타 공격동작중
#define		OBJSTA_ATK2					0x00020000	// 2번연타 공격동작중
#define		OBJSTA_ATK3					0x00030000	// ...
#define		OBJSTA_ATK4					0x00040000	// ...				// 나중에 "공격중"이라는 개념으로 통합될지도 모르겠다....
// wand attack
#define		OBJSTA_ATK_MAGIC1    		0x00050000	// 완드공격동작중
#define		OBJSTA_ATK_RANGE1    		0x00060000	// 원거리공격동작중
#define		OBJSTA_RANGE3				0x00070000	// 
#define		OBJSTA_RANGE4				0x00080000	// 
// melee skill
#define		OBJSTA_ATK_MELEESKILL		0x00090000	// 근접 전투스킬동작 중
#define		OBJSTA_ATK_RANGESKILL		0x000a0000	// 장거리 전투스킬동작 중
#define		OBJSTA_ATK_CASTING1			0x000b0000	// 마법 캐스팅 1번 (시작)
#define		OBJSTA_ATK_CASTING2			0x000c0000	// 마법 캐스팅 2번 (반복.)
#define		OBJSTA_ATK_MAGICSKILL		0x000d0000	// 마법 발사 동작.
#define		OBJSTA_SP_ATK1				0x00100000	// 특수공격 : 몬스터가 사용.
#define		OBJSTA_SP_ATK2				0x00200000	// 특수공격2 : 몬스터가 사용.
#define		OBJSTA_ATK_ALL				0x00FF0000
//#define		OBJSTA_RANGE_ALL			0x0f000000
// damage
#define		OBJSTA_DMG					0x01000000	// 피격
#define		OBJSTA_DMG_RESERVED1		0x04000000	
#define		OBJSTA_DMG_RESERVED2		0x05000000	

#define		OBJSTA_DMG_FLY				0x02000000	// 왕 피격 - 날아가기
#define		OBJSTA_DMG_DIE				0x03000000	// 왕 피격후 땅에 털썩!
#define		OBJSTA_DMG_LIVE				0x06000000	// 쓰러진 상태에서 다시 일어나기.
#define		OBJSTA_DMG_FLY_ALL			0x02000000	// 날아가는 데미지 모두. 다른곳에서 2번째 비트를 쓰지 않도록주의.

#define		OBJSTA_DEAD					0x08000000	// 죽어 널부러진 상태(죽은상태)
#define		OBJSTA_DISAPPEAR			0x09000000	// 죽어 없어지는 상태
#define		OBJSTA_RESURRECTION			0x0C000000	// 부활 0xd = 1101
#define		OBJSTA_DEAD_RESERVED1		0x0D000000	
#define		OBJSTA_DIE_ALL				0x08000000	// 죽음 - 0x00800000 비트가 온이면 죽은 상태.
#define		OBJSTA_DMG_ALL				0x0F000000	// 피격 & 죽음 모두

// 일반 action - 다른 어떤 명령도 이 액션중에는 영향을 못미친다.
#define		OBJSTA_COLLECT				0x10000000	// 채집.
#define		OBJSTA_APPEAR				0x20000000	// 등장씬.
#define		OBJSTA_APPEAR2				0x30000000  // 등장씬 2
#define		OBJSTA_STUN					0x40000000	// 스턴 상태.
#define		OBJSTA_ACTION_ALL			0xF0000000	// 

#define		OBJSTA_ALL	(OBJSTA_MOVE_ALL | OBJSTA_TURN_ALL | OBJSTA_LOOK_ALL | OBJSTA_JUMP_ALL | OBJSTA_ATK_ALL | OBJSTA_DMG_ALL | OBJSTA_ACTION_ALL )


// State Flag
#define		OBJSTAF_COMBAT				0x00000001	// 전투 모드
#define		OBJSTAF_WALK				0x00000002	// 걷는 모드
#define		OBJSTAF_SIT					0x00000004	// 앉기 상태
#define		OBJSTAF_FLY					0x00000008	// 비행 모드
#define		OBJSTAF_ACC					0x00000010	// 가속 상태
#define		OBJSTAF_ETC					0x00000020	// 커스텀 모션
#define		OBJSTAF_ACCTURN				0x00000040	// 급 선회.
#define		OBJSTAF_TURBO				0x00000080	// 터보 모드.

// Act Message
enum OBJMSG
{
	OBJMSG_NONE,
	OBJMSG_FORWARD,		// 전진 해라
	OBJMSG_BACKWARD,	// 후진 해라
	OBJMSG_STAND,		// 제자리에 서있어라
	OBJMSG_SITDOWN,		// 앉아라
	OBJMSG_STANDUP,		// 서라.(앉아있을때)
	OBJMSG_STOP,		// 멈춰라
	OBJMSG_ASTOP,		// 멈춰라
	OBJMSG_LTURN,		// 왼쪽으로 돌아라
	OBJMSG_RTURN,		// 오른쪽으로 돌아라
	OBJMSG_STOP_TURN,		// 도는걸 멈춰라
	OBJMSG_PICKUP,		// 줍다.
	OBJMSG_RESURRECTION,	// 부활.
	OBJMSG_COLLECT,		// 채집.
	OBJMSG_APPEAR,		// 등장
	OBJMSG_APPEAR2,		// 등장2
	OBJMSG_STUN,		// 스턴상태
	OBJMSG_JUMP,		// 점프
	OBJMSG_MODE_COMBAT,		// 전투모드가 되어라
	OBJMSG_MODE_PEACE,		// 평화모드가 되어라,
	OBJMSG_MODE_WALK,		// 걷기모드가 되어라
	OBJMSG_MODE_RUN,		// 뛰기모드가 되어라
	OBJMSG_MODE_FLY,		// 비행모드가 되어라
	OBJMSG_MODE_GROUND,		// 지상모드가 되어라
	OBJMSG_MODE_TURBO_ON,	// 순간 가속 모드.
	OBJMSG_MODE_TURBO_OFF,	// 가속모드 해제.
	OBJMSG_MODE_TURN,
	OBJMSG_ACC_START,	// 가속 시작
	OBJMSG_ACC_STOP,	// 가속 중지
	OBJMSG_ATK1,		// 연타공격 1시작
	OBJMSG_ATK2,		// 연타공격 2시작..
	OBJMSG_ATK3,
	OBJMSG_ATK4,
	OBJMSG_SP_ATK1,		// 특수공격 : 몬스터가 사용.
	OBJMSG_SP_ATK2,
	OBJMSG_ATK_RANGE1,	// 원거리공격 1시작 - 활같은...
	OBJMSG_ATK_MAGIC1,	// 완드공격
	OBJMSG_MELEESKILL,
	OBJMSG_MAGICSKILL,
	OBJMSG_MAGICCASTING,
	OBJMSG_DIE,		// 죽어라!
	OBJMSG_DAMAGE,			// 데미지먹음.
	OBJMSG_DAMAGE_FORCE,	// 강데미지 - 맞으면 날아감.
	OBJMSG_LOOKUP,
	OBJMSG_LOOKDOWN,
	OBJMSG_STOP_LOOK,
	OBJMSG_MOTION,
	OBJMSG_TURNMOVE,
	OBJMSG_TURNMOVE2,
	OBJMSG_BASE_RADY,		// 기본 시전 동작
	OBJMSG_TEMP,
	OBJMSG_TEMP2,	// 디버깅용 공격메시지
	OBJMSG_TEMP3,
	OBJMSG_DESTPOS,
	OBJMSG_DESTOBJ,
	OBJMSG_FALL,
	OBJMSG_LFORWARD,
	OBJMSG_RFORWARD,
	OBJMSG_STOP_RUN,
};


#define		MVRF_NONE			0x00000000
#define		MVRF_SKILL			0x00000001		// 연속 스킬 사용중.
#define		MVRF_CRITICAL		0x00000002		// 크리티컬 모드. 1회용.
#define		MVRF_TRACKING		0x00000004		// 비행중 자동추적모드중.
#define		MVRF_WARMARK		0x00000008		// 전투마크가 머리위에 떴는지. 0이면 CreateSfx를 해주고 1로 만들어 준다.
#define		MVRF_COLLECT		0x00000010		// 채집 이펙트.
#define		MVRF_HITCONT		0x00000020		// 일반공격 타점이후부터 애니끝날때까지 계속 ON
#define		MVRF_LASERCHARGE	0x00000040		// 레이저 충전중.
#define		MVRF_EFFECT1		0x00000080		// 무버가 하나씩 달고다닐수 있게 하는 이펙트(라이젬같은넘..)
#define		MVRF_NOMOVE			0x00000100		// 이동금지. 제자리에서 이동못함.
#define		MVRF_NOATTACK		0x00000200		// 공격금지. 근접/완드/스킬등 공격 및 스킬을 사용 못함
#define		MVRF_NOUSERITEM		0x00000400		// 아이템사용금지. 
#define		MVRF_NOANI			0x00000800		// 애니메이션 금지.
#define		MVRF_NOACTION		(MVRF_NOMOVE | MVRF_NOATTACK | MVRF_NOUSERITEM)		// 액션금지( 이동/공격/스킬/아이템 모두 합한거 )
#define		MVRF_FREEZE			(MVRF_NOANI | MVRF_NOACTION)	// 애니메이션도 멈추고 동작도 다 멈춘다.
#define		MVRF_MEDITATION_SIT	0x00001000		// 메디테이션사용후 앉기 플래그 - 최초 한번만 앉아야 하기때문.
#define		MVRF_SETITEMSFX		0x00002000		// 세트 아이템 효과 이펙트


#define		ENEMY_PVP_PARTY		0		// 파티 듀얼
#define		ENEMY_WAR			1		// 길드전
#define		ENEMY_PK			2		// 피케이
#define		ENEMY_PVP			3		// 듀얼


typedef struct tagSkill
{
	DWORD dwSkill;
	DWORD dwLevel;
	//ItemProp* GetProp()	{ return prj.GetSkillProp( dwSkill ); }

} SKILL,* LPSKILL;

typedef struct RESURRECTION_DATA
{
	u_long			dwPlayerID;
	BOOL			bUseing;
	vItemProp*		pSkillProp;
	vAddSkillProp*	pAddSkillProp;
	int				nDamage;
} RESURRECTION_DATA;


typedef	struct	_EQUIP_INFO
{
	DWORD	dwId;
	int		nOption;
	BYTE	byFlag;
}	EQUIP_INFO,	*PEQUIP_INFO; //9

enum TRADE_STATE
{
	TRADE_STEP_ITEM,			/// 아이템 단계 - 아이템을 올리고 내리고  
	TRADE_STEP_OK,			    /// OK누른 단계 - ok버튼을 눌렸다.        
	TRADE_STEP_CONFIRM,			/// CONFIRM단계 - 최종확인단계            
};



typedef	struct	tagSfxHit
{
	int		id;
	DWORD	objid;
	DWORD	dwAtkFlags;
	DWORD	dwSkill;
	int		nMaxDmgCnt;
} SfxHit, *PSfxHit;

class CSfxHitArray
{
	enum	{	nMaxSizeOfSfxHit	= 30,	};
private:
	SfxHit	m_aSfxHit[nMaxSizeOfSfxHit];
	int		m_id;
};


class CNpcProperty
{
	char			m_szName[64];
	int				m_nGlobal;
	DWORD			m_dwTick;
};

typedef struct tagQuest
{
	BYTE		m_nState;
	WORD		m_wTime;
	WORD		m_wId;

	WORD		m_nKillNPCNum[ 2 ];	// chipi_091015 - NPC Kill Quest 갯수 확장( BYTE -> WORD )
	BYTE		m_bPatrol   : 1;
	BYTE		m_bDialog   : 1;
	BYTE		m_bReserve3 : 1;
	BYTE		m_bReserve4 : 1;
	BYTE		m_bReserve5 : 1;
	BYTE		m_bReserve6 : 1;
	BYTE		m_bReserve7 : 1;
	BYTE		m_bReserve8 : 1;

	//QuestProp* GetProp() { return prj.m_aPropQuest.GetAt( m_wId ); }

} QUEST,* LPQUEST;

typedef struct tagSHORTCUT
{
	DWORD   m_dwShortcut; 
	DWORD   m_dwId; 
	DWORD   m_dwType; 
	DWORD   m_dwIndex; 
	DWORD   m_dwUserId; 
	DWORD   m_dwData; 
	char	m_szString[MAX_SHORTCUT_STRING];

	bool IsEmpty()		{	return m_dwShortcut == SHORTCUT_NONE;		}
	void Empty()		{	m_dwShortcut = SHORTCUT_NONE;				}
} SHORTCUT,* LPSHORTCUT;


//152

class CUserTaskBar  
{
public:
	DWORD x;

	SHORTCUT	m_aSlotApplet[ MAX_SLOT_APPLET ]; //2736
	SHORTCUT	m_aSlotItem  [ MAX_SLOT_ITEM_COUNT ][ MAX_SLOT_ITEM   ];
	SHORTCUT	m_aSlotQueue [ MAX_SLOT_QUEUE  ];
	int			m_nActionPoint;
	int			m_nUsedSkillQueue;
};

#define MAX_COOLTIME_TYPE 3

class CCooltimeMgr 
{
protected:
	DWORD				m_times[MAX_COOLTIME_TYPE];
	DWORD				m_bases[MAX_COOLTIME_TYPE];
};//24

class CAction
{
public:
	inline DWORD			GetMoveState()						{ return m_dwState & OBJSTA_MOVE_ALL;				}
	inline DWORD			GetTurnState()						{ return m_dwState & OBJSTA_TURN_ALL;				}
	inline DWORD			GetLookState()						{ return m_dwState & OBJSTA_LOOK_ALL;				}
	inline DWORD			GetJumpState()						{ return m_dwState & OBJSTA_JUMP_ALL;				}
	inline DWORD			GetDmgState()						{ return m_dwState & OBJSTA_DMG_ALL;				}
	inline DWORD			GetActionState()					{ return m_dwState & OBJSTA_ACTION_ALL;				}

	inline bool				IsState( DWORD dwState )			{ return (m_dwState & dwState)?true:false;			}
	inline bool				IsStateFlag( DWORD dwStateFlag )	{ return (m_dwStateFlag & dwStateFlag)? true:false;	}
	inline bool				IsFly()								{ return (m_dwStateFlag & OBJSTAF_FLY)?true:false;	}
	inline bool				IsDie()								{ return (m_dwState & OBJSTA_DIE_ALL)?true:false;	}
	inline bool				IsSit()								{ return (m_dwStateFlag & OBJSTAF_SIT)?true:false;	}
	inline bool				IsRun()								{ return ((m_dwStateFlag & OBJSTAF_WALK) == 0);		}
	inline bool				IsWalk()							{ return (m_dwStateFlag & OBJSTAF_WALK)?true:false;	}
	inline bool				IsAction()							{ return (m_dwState & OBJSTA_ACTION_ALL)?true:false;}

public:

	DWORD x;
	DWORD			m_dwState;			
	DWORD			m_dwStateFlag;	



};

class CActionMover : public CAction
{
};