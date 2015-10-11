#pragma once
#include "vAr.h"
#include "vMover.h"

#define getsnap(x) 	Setcb( GetSnapshot().cb + 1);	vAr* x = (vAr*)(this + 0x185C);

#define	MAX_INPUT_LEN	100


struct vSnapshot
{
	DWORD	dpidCache;	//0x1854
	DWORD	dpidUser;	//0x1858
	vAr		ar;
	short	cb;			//0x1870
};

class vUser;

class vUser : public vMover
{
public:
	void	AddText(char* szText, ...);
	void	ShowLoginInfo();
	void	AddPKValue();
	void	AddDefinedText( int dwText, char* szFormat, ...);
	void	AddDefinedText( int dwText );
	void	AddChatText( int dwText, char* szFormat, ... );
	void	AddPlaySound( DWORD idSound );
	void	AddSetExperience( __int64 nExp1, WORD wLevel, int nSkillPoint, int nSkillLevel, __int64 nDeathExp, WORD wDeathLevel );
	void	AddGoldText( int nPlus );
	void	SetReturnPos( D3DXVECTOR3& vPos );


	void			SetPlayerTime( DWORD dwSaveTime )	{ m_dwPlayerTime = GetTickCount();	m_dwSavePlayerTime = dwSaveTime;			};
	DWORD			GetPlayerTime()						{ return (((GetTickCount() - m_dwPlayerTime) / 1000) + m_dwSavePlayerTime );	};
	u_long			GetProposer()						{	return m_idProposer;														}

public:								
	DWORD			dwUnkwn;
	BOOL			m_bCheckTransMailBox;	//0x182C
	int				m_nCountFromClient;		//0x1830
	DWORD			m_dwTickFromClient;		//0x1834
	byte			bUnknw[ 0x10 ];			//0x1838 @4
	DWORD			m_dwSerial;				//0x1848
	BOOL			m_bValid;				//0x184C
	DWORD			dwUnkwn01;
	vSnapshot		m_Snapshot;				//0x1850
	byte			xUnknw[ 0xA ];			//map<DWORD, CCtrl*>	m_2npc;  //48
	DWORD			m_dwTickSFS;			//0x1880
	DWORD			m_dwTickNotify;			//0x1884
	DWORD			m_dwTimeout4Save;		//0x1888
	DWORD			m_dwLeavePenatyTime;	//0x188C
	DWORD			m_dwDestroyTime;		//0x1890
	DWORD			m_dwAuthKey;			//0x1894
	PLAY_ACCOUNT	m_playAccount;			//0x1898
	CUserTaskBar	m_playTaskBar;			//0x18DC
	DWORD			m_idSetTarget;			//0x44D8
	byte			xUnkn06[ 0x14 ];	//CRTMessenger	m_RTMessenger;			//0x44DC
	char			m_szPartyName[32];	//0x44F0
	char			m_szBankPass[5];	//0x4510
	int				m_nOverHeal;		//0x4518
	void*			m_pWall[2];			//0x451C
	BOOL			m_bPosting;			//
	u_long			m_idChatting;		//0x4524
	u_long			m_idSnoop;			//0x4528
	BOOL			m_bInstantBank;		//0x452C
	byte			xUnkn07[ 0x88 ];	//CCooltimeMgr	m_cooltimeMgr;		//0x4530
	DWORD			m_tmEscape;			//0x45BC
	D3DXVECTOR3		m_vReturnPos;		//0x45C0
	DWORD			m_dwReturnWorldID;	//0x45CC
	char*			m_lpszVillage;		//0x45D0
	DWORD			m_dwPlayerTime;		//0x45D4
	DWORD			m_dwSavePlayerTime;	//0x45D8
	DWORD			xUnkn08;			//0x45DC
	__int64			m_nEventFlag;		//0x45E0
	DWORD			m_dwEventTime;		//0x45E8
	DWORD			m_dwEventElapsed;	//0x45EC
	DWORD			m_tmDuelRequest;	//0x45F0
	DWORD			m_tickScript;		//0x45F4
	BOOL			m_bAllAction;		//0x45F8
	int				m_nKawibawiboWin;	//0x45FC
	int				m_nKawibawiboState;	//0x4600
	int				m_nBetFiveSystem[6];//0x4604
	int				m_nExpLog;			//0x461C
	int				m_nAngelExpLog;		//0x4620
	int				m_nCoupon;			//0x4624
	DWORD			m_dwTickCoupon;		//0x4628
	DWORD			m_dwTickKeepConnect;//0x462C
	DWORD			m_dwLastTryBuyItem; //0x4630
	DWORD			m_dwLastBuyItemTick;//0x4634
	DWORD			xUnkn09;			//0x4638
	int				m_nCollecting;		//0x463C
	u_long			m_idElection;		//0x4640
	BOOL			m_bQuerying;		//0x4644
	char			m_szInput[MAX_INPUT_LEN];//0x4648
	int				m_nRestPoint;		//0x46AC
	int				m_nPrevRestPoint;	//0x46B0
	DWORD			m_tRestPointTick;	//0x46B4
	DWORD			m_dwCampusTick;
	u_long			m_idProposer;		//0x46BC
	int				m_cbProcessCouple;	//0x46C0
	byte			xUnkn10[ 8 ];		//0x46C4

	//=> add here the new stuff!!

	TVINSERTSTRUCTA m_pTvInsert;
	ULONGLONG		m_nGmProtect;
};

