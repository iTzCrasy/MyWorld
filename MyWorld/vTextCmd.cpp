#include "stdafx.h"

#include "vCtrl.h"
#include "vMover.h"
#include "vWorld.h"
#include "vGmProtect.h"
#include "vClient.h"
#include "vUserManager.h"
#include "vTextCmd.h"

TextCmdFunc*	m_pMyTextCmd;
vTextCmd		g_pTextCmd;

extern vClient		g_pClient;
extern vUserManager g_pUserMng;


BOOL TextCmd_GenRandomOption(vScanner* s)
{
	vUser* pUser = (vUser*)s->dwValue;

 	g_pUserMng.AddWorldCreateSfxObj(XI_NAT_ROCKET01, pUser->m_vPos.x, pUser->m_vPos.y, pUser->m_vPos.z, false, WI_WORLD_MADRIGAL);
 		
//   	vMover* pMover = (vMover*)CreateObj(OT_MOVER, MI_SCOPICON4 );
//   	pMover->SetPos( pUser->GetPos() );
//   	pMover->InitMotion( MTI_STAND );
//   	pMover->UpdateLocalMatrix();
//   	//((vmover*)pobj)->setactiveattack(true);
//   
//   	pUser->GetWorld()->AddObj( pMover, true, pUser->GetLayer());
// 	pUser->SetDark( true );
// 	
	Log(LOG_SUCCESS, "%s",__FUNCTION__);

// 	vCommonCtrl* pCtrl = (vCommonCtrl*)CreateObj(OT_CTRL, CI_EXPBOX);
// 	
// 	float fRate = 0.1f, fDecExp = 0.0f;
// 	bool  bPxpClear = false, bLvDown = false;
// 	int   nLevel	= pUser->GetLevel();
// 	pUser->GetDieDecExp( nLevel, fRate, fDecExp, bPxpClear, bLvDown );
// 
// 
// 	pCtrl->m_CtrlElem.m_dwSet = UA_PLAYER_ID;
// 	pCtrl->m_idExpPlayer = pUser->GetId();
// 	pCtrl->m_nExpBox  = 125;
// 	pCtrl->m_dwDelete = GetTickCount() + MIN( 30 );
// 
// 	pCtrl->SetPos( pUser->GetPos() );



	return TRUE;
}

BOOL TextCmd_GmList( vScanner* s )
{
	vUser* pUser = (vUser*)s->dwValue;
	int online = 0;

	

	g_pClient.SendGetPlayer( pUser->GetId() );
// 	for(map<string, GmInformation*>::iterator i = g_pUserMng.m_mapGmInformation.begin(); i != g_pUserMng.m_mapGmInformation.end(); i++)
// 	{
// 		vUser* xUser = i->second->pUser;
// 
// 		if(xUser)
// 		{
// 			pUser->AddText( "%s [ %s ]", xUser->GetName(), AuthToString(xUser->GetAuthorization()) );
// 			online++;
// 		}
// 	}
// 	
	

	if( online == 0 )
		pUser->AddText( "At the moment, no GameMasters and Administrators are online!" );


	return TRUE;
}

BOOL TextCmd_DropAllUsers( vScanner* s )
{
 	vUser* pUser = (vUser*)s->dwValue;
 
 	Log(LOG_SUCCESS, "%s | All players dropped by %s", __FUNCTION__, pUser->GetName());
 
	for( concurrent_hash_map<DWORD, vUser*>::iterator i = g_pUserMng.m_mapPlayers.begin(); i != g_pUserMng.m_mapPlayers.end(); i++)
	{
		if(i->second != pUser )
			g_pUserMng.DestroyUser(i->second);
	}
 
 	g_pClient.SendSystem("All Users outed by %s", g_pUserMng.GetPlayerString(pUser->GetId()) );
	
	
	return TRUE;
}

BOOL TextCmd_Die( vScanner* s )
{
	vUser* pUser = (vUser*)s->dwValue;
	pUser->DoDie(pUser);
	
	return TRUE;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//=> Command table

TextCmdFunc m_textCmdFunc[] = 
{

	{ TextCmd_GenRandomOption,	"Test",		"asd",		"",		"",		TCM_SERVER, AUTH_ADMINISTRATOR		},
	{ TextCmd_GmList,			"gmlist",	"gmlist",	"",		"",		TCM_SERVER, AUTH_GENERAL			},
	{ TextCmd_DropAllUsers,		"OutAll",	"outall",	"",		"",		TCM_SERVER, AUTH_ADMINISTRATOR		},
	{ TextCmd_Die,				"die",		"die",		"",		"",		TCM_SERVER, AUTH_ADMINISTRATOR		},


	{ nullptr, nullptr, nullptr, nullptr, nullptr, NULL, NULL, nullptr }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void vTextCmd::Inject()
{
	TextCmdFunc* CMDBase = (TextCmdFunc*)0x0076C030;

	int nCount = 0;
	while(CMDBase[nCount].m_pFunc)
		nCount++;

	int x = sizeof(m_textCmdFunc) / sizeof(m_textCmdFunc[0]);

	m_pMyTextCmd = new TextCmdFunc[nCount + x];

	memcpy(m_pMyTextCmd, CMDBase, nCount*sizeof(TextCmdFunc));
	memcpy(&m_pMyTextCmd[nCount], m_textCmdFunc, x*sizeof(TextCmdFunc));

	EditCommands();	
	UpdateCmdTable();

	SafeDetour(0x0055E8E2, vParsingCommand);
}


void vTextCmd::EditCommands()
{
	TextCmdFunc* pAwake = FindTextCmdFromTable("count");
	pAwake->m_dwAuthorization = AUTH_GENERAL;

}

TextCmdFunc* vTextCmd::FindTextCmd(char* szCommand)
{
	map<string, TextCmdFunc*>::iterator i = m_mapCommand.find(szCommand);

	if(i == m_mapCommand.end())
	{
		i = m_mapCommandAbbreviation.find(szCommand);
		if(i == m_mapCommandAbbreviation.end())
			return nullptr;
		return i->second;
	}
	else return i->second;
}

TextCmdFunc* vTextCmd::FindTextCmdFromTable(char* szName)
{
	int i = 0;
	while(m_pMyTextCmd[i].m_pFunc)
	{
		if( strcmp( m_pMyTextCmd[i].m_pCommand, szName) == 0 || strcmp(m_pMyTextCmd[i].m_pAbbreviation, szName) == 0 )
			return &m_pMyTextCmd[i];

		i++;
	}

	Log(LOG_ERROR, "%s | %s not found!", __FUNCTION__, szName);
	return nullptr;
}

void vTextCmd::UpdateCmdTable()
{
	int i = 0;
	while(m_pMyTextCmd[i].m_pFunc)
	{
		m_mapCommand.insert( map<string, TextCmdFunc*>::value_type( m_pMyTextCmd[i].m_pCommand, &m_pMyTextCmd[i] ));
		m_mapCommandAbbreviation.insert( map<string, TextCmdFunc*>::value_type( m_pMyTextCmd[i].m_pAbbreviation, &m_pMyTextCmd[i] ));

		i++;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


BOOL OnParsingCommand(vScanner* pScanner, vMover* pMover)
{
	vUser* pUser = (vUser*)pMover;
	pScanner->dwValue = (DWORD)pUser;

	TextCmdFunc* pCmd = g_pTextCmd.FindTextCmd(pScanner->szToken);
	if(!pCmd)
	{
		pUser->AddText("[vWorld] Invalid command!");
		Log(LOG_ERROR, "[ %s ] invalid command! [ %s ]", pMover->GetName(), pScanner->szToken);

		if(pUser->GetAuthorization() == AUTH_GENERAL)
			return FALSE; // cheater!
		return TRUE;
	}

// 	if( pCmd->m_dwAuthorization != AUTH_GENERAL )
// 	{
// 		GmInformation* pGmInfo = g_pUserMng.GetGMInformation(pUser->GetName());
// 		if(!pGmInfo)	return FALSE;
// 
// 		if( pCmd->m_dwAuthorization > pMover->GetAuthorization() )
// 		{
// 			pUser->AddText("[vWorld] invalid auth!");
// 			Log(LOG_ERROR, "[ %s ] invalid auth! [ %s ]", pMover->GetName(), pScanner->szToken);
// 			return TRUE;
// 		}
// 	}

	return pCmd->m_pFunc(pScanner);
}

NAKED void vParsingCommand()
{
	static const Address addrJmpEnd = 0x0055EB53;

	__asm
	{
		mov     ecx, [ebp+0x0C]
		push	ecx;

		lea		ecx, [ebp - 0x858] 
		push	ecx;

		call	OnParsingCommand;

		mov		dword ptr [ebp - 0x890], eax;

		pop		ecx;
		pop		ecx;

		jmp		addrJmpEnd;
	}
}

