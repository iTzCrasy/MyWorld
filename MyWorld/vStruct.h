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
	DWORD	dwID;				// ������	
	DWORD	dwName;				// ��Ī
	DWORD	dwSkillLvl;			// ��ų����
	DWORD	dwAbilityMin;		// �ּҴɷ�
	DWORD	dwAbilityMax;		// �ִ�ɷ�
	DWORD	dwAttackSpeed;		// ���ݼӵ�
	DWORD	dwDmgShift;			// Ÿ�ݽ� �ݵ�
	DWORD	nProbability;		// �ߵ� Ȯ��
	DWORD	dwTaunt;			// Ÿ��Ʈ
	DWORD	dwDestParam[2];		// ������1
	DWORD	nAdjParamVal[2];	// ���밪1;
	DWORD	dwChgParamVal[2];	//���뺯ȭ��1
	int		nDestData1[3];		// ���뵥��Ÿ3��, DestParam[0]�� �ش�.
	DWORD	dwActiveSkill;		// �ߵ� ����
	DWORD	dwActiveSkillRate;	// �ߵ� ���� Ȯ��.
#if __VER >= 9	// __SKILL_0706
	DWORD	dwActiveSkillRatePVP;	// ���� �ߵ� ���� Ȯ��.
#endif	// __SKILL_0706
	int		nReqMp;				//�ʿ�MP
	int		nReqFp;				//�ʿ�FP
#if __VER >= 9	// __SKILL_0706
	DWORD	dwCooldown;		// ��ٿ�
	DWORD	dwCastingTime;		//��� �غ�ð�
#else	// __SKILL_0706
	DWORD	dwSkillReady;		//��� �غ�ð�
#endif	// __SKILL_0706
	DWORD	dwSkillRange;		// ��� �����Ÿ�	
	DWORD	dwCircleTime;		//�����ð�
	DWORD   dwPainTime;         // ���� ���ؽð�
	DWORD	dwSkillTime;		//���ӽð�
	int		nSkillCount;		// �߻�ü �߻� ����. ������ݷ� = �Ѱ��ݷ� / nSkillCount;
	DWORD   dwSkillExp;         //��ų ����ġ
	DWORD	dwExp;				//�������ġ
	DWORD	dwComboSkillTime;	//�޺���ųŸ��
#if __VER >= 9	// __SKILL_0706
	DWORD	dwAbilityMinPVP;	// �ּҴɷ�(����)
	DWORD	dwAbilityMaxPVP;	// �ִ�ɷ�(����)
	DWORD	nProbabilityPVP;	// �ߵ� Ȯ��(����)
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
	DWORD		m_dwSet;				    //-�������� ���� UA_ITEM, UA_LEVEL...
	DWORD 		m_dwSetItem;				//-�ڽ� ���� ����(������)								- UA_ITEM
	DWORD		m_dwSetLevel;				//-�ڽ� ���� ����(����)									- UA_LEVEL
	DWORD		m_dwSetQuestNum;			//-�ڽ� ���� ����(����Ʈ �ѹ�,����Ʈ �÷��� �ѹ�)       - UA_QUEST
	DWORD		m_dwSetFlagNum;
	DWORD		m_dwSetGender;				//-�ڽ� ���� ����(����)									- UA_GENDER
	BOOL		m_bSetJob[32];			//-�ڽ� ���� ����(Ŭ����)								- UA_CLASS

	DWORD		m_dwSetEndu;				//-�ڽ� ������ ? hp�� ���� ����	

	DWORD		m_dwMinItemNum;				//-�ּ� �߻� ������ �� 
	DWORD		m_dwMaxiItemNum;			//-�ִ� �߻� ������ ��
	DWORD		m_dwInsideItemKind[MAX_CTRLDROPITEM];		//-���� ������ ���� �� !!!����!!! ������ MAX_CTRLDROPITEM-1 �� ���� ���۰���
	DWORD		m_dwInsideItemPer [MAX_CTRLDROPITEM];		//-���� ������ �� �߻� Ȯ��( 3000000000 )

	DWORD       m_dwMonResKind  [MAX_CTRLDROPMOB];          //-����1 �߻� ����(���� ���̵� �Է�)
	DWORD		m_dwMonResNum   [MAX_CTRLDROPMOB];			//-����1 �߻� ����
	DWORD		m_dwMonActAttack[MAX_CTRLDROPMOB];			//-���� Ÿ��1���� ���� ���� �߻� ����(���� �ʵ� ���� �ʰ��ؼ��� �ʵ�)

	// Ʈ������
	DWORD		m_dwTrapOperType;              // Ʈ�� �ߵ� Ÿ�� TOT_RANDOM, TOT_NOENDU
	DWORD		m_dwTrapRandomPer;             // Ʈ�� �ߵ� Ȯ��(TOT_RANDOM�ϰ��)
	DWORD		m_dwTrapDelay;				   // Ʈ�� �ߵ� ������ 0�̸� ��� �߻�

	DWORD		m_dwTrapKind	[MAX_TRAP];    // Ʈ�� ���� - ���� ��ų�� ����� ��� Ʈ���� ��ų�� (��ų������Ƽ�� ID��)
	DWORD		m_dwTrapLevel	[MAX_TRAP];
	TCHAR		m_strLinkCtrlKey[MAX_KEY];		// ���� ��Ʈ���� Ű �̸�
	TCHAR		m_strCtrlKey[MAX_KEY];			// ��Ʈ���� Ű �̸�
	DWORD		m_dwSetQuestNum1;			//-�ڽ� ������ ����(����Ʈ �ѹ�,����Ʈ �÷��� �ѹ�)       - UA_QUEST
	DWORD		m_dwSetFlagNum1;
	DWORD		m_dwSetQuestNum2;			//-�ڽ� ������ ����(����Ʈ �ѹ�,����Ʈ �÷��� �ѹ�)       - UA_QUEST
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
	DWORD	dwPropensityMin;		/// ���� ��ġ Min
	DWORD	dwPropensityMax;		/// ���� ��ġ Max
	int		nEquipDorpMin;			/// ��������� ��� ���� Min
	int		nEquipDorpMax;			/// ��������� ��� ���� Max
	int		nInvenDorpMin;			/// �κ������� ��� ���� Min
	int		nInvenDorpMax;			/// �κ������� ��� ���� Max
	int		nShop;					/// ���� �̿� ��/��
	int		nBank;					/// â�� �̿� ��/��
	int		nFly;					/// ���� �̿� ��/��
	int		nGuardAttack;			/// ��� ���� ��/��
	int		nVendor;				/// ���λ��� �̿� �� ���� ��/��
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

#define		OBJSTA_NONE					0x00000000	// �ƹ��͵� �ƴѻ���.

// stop/move
#define		OBJSTA_STAND				0x00000001	// ������
#define		OBJSTA_STAND2				0x00000002	// ������EX
#define		OBJSTA_SIT					0x00000003	// �ɱ�
#define		OBJSTA_FMOVE				0x00000004	// ������ �ȱ�
#define		OBJSTA_BMOVE				0x00000005	// �ڷ� �ȱ�
#define		OBJSTA_LEFT					0x00000006	// ������ �ȱ�(�����̵�)
#define		OBJSTA_RIGHT				0x00000007	// 
#define		OBJSTA_PICKUP				0x00000008	// (���ǵ���)�ݴ�.

#define		OBJSTA_LMOVE				0x00000009	// ����������� �ȱ�
#define		OBJSTA_RMOVE				0x0000000a	// ������������� �ȱ�
#define		OBJSTA_STOP_RUN				0x0000000b	// ���ڸ� �ٱ�

#define		OBJSTA_MOVE_ALL				0x000000FF
#define		OBJSTA_NOT_STAND			(OBJSTA_MOVE_ALL & (~OBJSTA_STAND))		// STAND�̿ܰ� �ִ°�.

// turn
#define		OBJSTA_LTURN				0x00000100	// �� ��
#define		OBJSTA_RTURN				0x00000200	// �� ��
#define		OBJSTA_TURN_ALL				0x00000300	//
// look up/down
#define		OBJSTA_LOOKUP				0x00000400	//
#define		OBJSTA_LOOKDOWN				0x00000800	//
#define		OBJSTA_LOOK_ALL				0x00000C00

// jump
#define		OBJSTA_FJUMP_READY			0x00001000	// ������ ���� - ������
#define		OBJSTA_FJUMP				0x00002000	// ������
#define		OBJSTA_FFALL				0x00003000	// ����������
#define		OBJSTA_FLAND				0x00004000	// ����
#define		OBJSTA_SJUMP1				0x00005000	// ������ ���� - ���ڸ�����
#define		OBJSTA_SJUMP2				0x00006000	// ������
#define		OBJSTA_SJUMP3				0x00007000	// ����������
#define		OBJSTA_SJUMP4				0x00008000	// ����
#define		OBJSTA_BJUMP_READY			0x00009000	// ������ ���� - ������
#define		OBJSTA_BJUMP				0x0000a000	// ������
#define		OBJSTA_BFALL				0x0000b000	// ����������
#define		OBJSTA_BLAND				0x0000c000	// ����
#define		OBJSTA_JUMP_ALL				0x0000F000
// attack
#define		OBJSTA_ATK1					0x00010000	// 1����Ÿ ���ݵ�����
#define		OBJSTA_ATK2					0x00020000	// 2����Ÿ ���ݵ�����
#define		OBJSTA_ATK3					0x00030000	// ...
#define		OBJSTA_ATK4					0x00040000	// ...				// ���߿� "������"�̶�� �������� ���յ����� �𸣰ڴ�....
// wand attack
#define		OBJSTA_ATK_MAGIC1    		0x00050000	// �ϵ���ݵ�����
#define		OBJSTA_ATK_RANGE1    		0x00060000	// ���Ÿ����ݵ�����
#define		OBJSTA_RANGE3				0x00070000	// 
#define		OBJSTA_RANGE4				0x00080000	// 
// melee skill
#define		OBJSTA_ATK_MELEESKILL		0x00090000	// ���� ������ų���� ��
#define		OBJSTA_ATK_RANGESKILL		0x000a0000	// ��Ÿ� ������ų���� ��
#define		OBJSTA_ATK_CASTING1			0x000b0000	// ���� ĳ���� 1�� (����)
#define		OBJSTA_ATK_CASTING2			0x000c0000	// ���� ĳ���� 2�� (�ݺ�.)
#define		OBJSTA_ATK_MAGICSKILL		0x000d0000	// ���� �߻� ����.
#define		OBJSTA_SP_ATK1				0x00100000	// Ư������ : ���Ͱ� ���.
#define		OBJSTA_SP_ATK2				0x00200000	// Ư������2 : ���Ͱ� ���.
#define		OBJSTA_ATK_ALL				0x00FF0000
//#define		OBJSTA_RANGE_ALL			0x0f000000
// damage
#define		OBJSTA_DMG					0x01000000	// �ǰ�
#define		OBJSTA_DMG_RESERVED1		0x04000000	
#define		OBJSTA_DMG_RESERVED2		0x05000000	

#define		OBJSTA_DMG_FLY				0x02000000	// �� �ǰ� - ���ư���
#define		OBJSTA_DMG_DIE				0x03000000	// �� �ǰ��� ���� �н�!
#define		OBJSTA_DMG_LIVE				0x06000000	// ������ ���¿��� �ٽ� �Ͼ��.
#define		OBJSTA_DMG_FLY_ALL			0x02000000	// ���ư��� ������ ���. �ٸ������� 2��° ��Ʈ�� ���� �ʵ�������.

#define		OBJSTA_DEAD					0x08000000	// �׾� �κη��� ����(��������)
#define		OBJSTA_DISAPPEAR			0x09000000	// �׾� �������� ����
#define		OBJSTA_RESURRECTION			0x0C000000	// ��Ȱ 0xd = 1101
#define		OBJSTA_DEAD_RESERVED1		0x0D000000	
#define		OBJSTA_DIE_ALL				0x08000000	// ���� - 0x00800000 ��Ʈ�� ���̸� ���� ����.
#define		OBJSTA_DMG_ALL				0x0F000000	// �ǰ� & ���� ���

// �Ϲ� action - �ٸ� � ��ɵ� �� �׼��߿��� ������ ����ģ��.
#define		OBJSTA_COLLECT				0x10000000	// ä��.
#define		OBJSTA_APPEAR				0x20000000	// �����.
#define		OBJSTA_APPEAR2				0x30000000  // ����� 2
#define		OBJSTA_STUN					0x40000000	// ���� ����.
#define		OBJSTA_ACTION_ALL			0xF0000000	// 

#define		OBJSTA_ALL	(OBJSTA_MOVE_ALL | OBJSTA_TURN_ALL | OBJSTA_LOOK_ALL | OBJSTA_JUMP_ALL | OBJSTA_ATK_ALL | OBJSTA_DMG_ALL | OBJSTA_ACTION_ALL )


// State Flag
#define		OBJSTAF_COMBAT				0x00000001	// ���� ���
#define		OBJSTAF_WALK				0x00000002	// �ȴ� ���
#define		OBJSTAF_SIT					0x00000004	// �ɱ� ����
#define		OBJSTAF_FLY					0x00000008	// ���� ���
#define		OBJSTAF_ACC					0x00000010	// ���� ����
#define		OBJSTAF_ETC					0x00000020	// Ŀ���� ���
#define		OBJSTAF_ACCTURN				0x00000040	// �� ��ȸ.
#define		OBJSTAF_TURBO				0x00000080	// �ͺ� ���.

// Act Message
enum OBJMSG
{
	OBJMSG_NONE,
	OBJMSG_FORWARD,		// ���� �ض�
	OBJMSG_BACKWARD,	// ���� �ض�
	OBJMSG_STAND,		// ���ڸ��� ���־��
	OBJMSG_SITDOWN,		// �ɾƶ�
	OBJMSG_STANDUP,		// ����.(�ɾ�������)
	OBJMSG_STOP,		// �����
	OBJMSG_ASTOP,		// �����
	OBJMSG_LTURN,		// �������� ���ƶ�
	OBJMSG_RTURN,		// ���������� ���ƶ�
	OBJMSG_STOP_TURN,		// ���°� �����
	OBJMSG_PICKUP,		// �ݴ�.
	OBJMSG_RESURRECTION,	// ��Ȱ.
	OBJMSG_COLLECT,		// ä��.
	OBJMSG_APPEAR,		// ����
	OBJMSG_APPEAR2,		// ����2
	OBJMSG_STUN,		// ���ϻ���
	OBJMSG_JUMP,		// ����
	OBJMSG_MODE_COMBAT,		// ������尡 �Ǿ��
	OBJMSG_MODE_PEACE,		// ��ȭ��尡 �Ǿ��,
	OBJMSG_MODE_WALK,		// �ȱ��尡 �Ǿ��
	OBJMSG_MODE_RUN,		// �ٱ��尡 �Ǿ��
	OBJMSG_MODE_FLY,		// �����尡 �Ǿ��
	OBJMSG_MODE_GROUND,		// �����尡 �Ǿ��
	OBJMSG_MODE_TURBO_ON,	// ���� ���� ���.
	OBJMSG_MODE_TURBO_OFF,	// ���Ӹ�� ����.
	OBJMSG_MODE_TURN,
	OBJMSG_ACC_START,	// ���� ����
	OBJMSG_ACC_STOP,	// ���� ����
	OBJMSG_ATK1,		// ��Ÿ���� 1����
	OBJMSG_ATK2,		// ��Ÿ���� 2����..
	OBJMSG_ATK3,
	OBJMSG_ATK4,
	OBJMSG_SP_ATK1,		// Ư������ : ���Ͱ� ���.
	OBJMSG_SP_ATK2,
	OBJMSG_ATK_RANGE1,	// ���Ÿ����� 1���� - Ȱ����...
	OBJMSG_ATK_MAGIC1,	// �ϵ����
	OBJMSG_MELEESKILL,
	OBJMSG_MAGICSKILL,
	OBJMSG_MAGICCASTING,
	OBJMSG_DIE,		// �׾��!
	OBJMSG_DAMAGE,			// ����������.
	OBJMSG_DAMAGE_FORCE,	// �������� - ������ ���ư�.
	OBJMSG_LOOKUP,
	OBJMSG_LOOKDOWN,
	OBJMSG_STOP_LOOK,
	OBJMSG_MOTION,
	OBJMSG_TURNMOVE,
	OBJMSG_TURNMOVE2,
	OBJMSG_BASE_RADY,		// �⺻ ���� ����
	OBJMSG_TEMP,
	OBJMSG_TEMP2,	// ������ ���ݸ޽���
	OBJMSG_TEMP3,
	OBJMSG_DESTPOS,
	OBJMSG_DESTOBJ,
	OBJMSG_FALL,
	OBJMSG_LFORWARD,
	OBJMSG_RFORWARD,
	OBJMSG_STOP_RUN,
};


#define		MVRF_NONE			0x00000000
#define		MVRF_SKILL			0x00000001		// ���� ��ų �����.
#define		MVRF_CRITICAL		0x00000002		// ũ��Ƽ�� ���. 1ȸ��.
#define		MVRF_TRACKING		0x00000004		// ������ �ڵ����������.
#define		MVRF_WARMARK		0x00000008		// ������ũ�� �Ӹ����� ������. 0�̸� CreateSfx�� ���ְ� 1�� ����� �ش�.
#define		MVRF_COLLECT		0x00000010		// ä�� ����Ʈ.
#define		MVRF_HITCONT		0x00000020		// �Ϲݰ��� Ÿ�����ĺ��� �ִϳ��������� ��� ON
#define		MVRF_LASERCHARGE	0x00000040		// ������ ������.
#define		MVRF_EFFECT1		0x00000080		// ������ �ϳ��� �ް�ٴҼ� �ְ� �ϴ� ����Ʈ(������������..)
#define		MVRF_NOMOVE			0x00000100		// �̵�����. ���ڸ����� �̵�����.
#define		MVRF_NOATTACK		0x00000200		// ���ݱ���. ����/�ϵ�/��ų�� ���� �� ��ų�� ��� ����
#define		MVRF_NOUSERITEM		0x00000400		// �����ۻ�����. 
#define		MVRF_NOANI			0x00000800		// �ִϸ��̼� ����.
#define		MVRF_NOACTION		(MVRF_NOMOVE | MVRF_NOATTACK | MVRF_NOUSERITEM)		// �׼Ǳ���( �̵�/����/��ų/������ ��� ���Ѱ� )
#define		MVRF_FREEZE			(MVRF_NOANI | MVRF_NOACTION)	// �ִϸ��̼ǵ� ���߰� ���۵� �� �����.
#define		MVRF_MEDITATION_SIT	0x00001000		// �޵����̼ǻ���� �ɱ� �÷��� - ���� �ѹ��� �ɾƾ� �ϱ⶧��.
#define		MVRF_SETITEMSFX		0x00002000		// ��Ʈ ������ ȿ�� ����Ʈ


#define		ENEMY_PVP_PARTY		0		// ��Ƽ ���
#define		ENEMY_WAR			1		// �����
#define		ENEMY_PK			2		// ������
#define		ENEMY_PVP			3		// ���


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
	TRADE_STEP_ITEM,			/// ������ �ܰ� - �������� �ø��� ������  
	TRADE_STEP_OK,			    /// OK���� �ܰ� - ok��ư�� ���ȴ�.        
	TRADE_STEP_CONFIRM,			/// CONFIRM�ܰ� - ����Ȯ�δܰ�            
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

	WORD		m_nKillNPCNum[ 2 ];	// chipi_091015 - NPC Kill Quest ���� Ȯ��( BYTE -> WORD )
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