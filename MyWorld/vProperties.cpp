#include "stdafx.h"
#include "vProperties.h"

static const Address addrDropMng		= 0x00903698;


void vProperties::Inject()
{

	if(m_pLua.RunScript(".\\vWorld\\Project.lua") != NULL)
	{
		vMsgBox( MB_OK, "Error", "%s | load lua failed!", __FUNCTION__);
		DBGBREAK;
	}

	m_fMonsterExp	= (float)m_pLua.GetGlobalNumber("MyMonsterExp");
	m_fGoldDrop		= (float)m_pLua.GetGlobalNumber("MyGoldDrop");
	m_fItemDrop		= (float)m_pLua.GetGlobalNumber("MyItemDrop");
	m_fMonsterHit	= (float)m_pLua.GetGlobalNumber("MyMonsterHit");
	m_fPetSpeed		= (float)m_pLua.GetGlobalNumber("MyPetSpeed");

	m_bPartyLinkShare = m_pLua.GetGlobalBool("EnablePartyLink");

	//71BDE8
	SetVar(float, 0x0076DF28, m_fGoldDrop);
	SetVar(float, 0x0076DF2C, m_fMonsterExp);
	SetVar(float, 0x0076DF24, m_fItemDrop);
	SetVar(float, 0x0076DF30, m_fMonsterHit);


	if(m_bPartyLinkShare)
		SafeDetour(0x00630CDC, 0x00630CE2);

//	SafeDetour(0x0046DAD7, vMonsterDropLoad);

	m_aExpCharacter = *(EXPCHARACTER**)0x00788BB8;
	m_aJob			= *(JOB**)0x00786398;

}

void vProperties::ModifyDropRate(DWORD dwGoldMainProb, DWORD dwGoldMin, DWORD dwGoldMax, DWORD dwMainProb, DWORD dwItemCountMin, DWORD dwItemCountMax )
{
	dwGoldMin = (DWORD)(dwGoldMin * m_fGoldDrop);
	dwGoldMax = (DWORD)(dwGoldMax * m_fGoldDrop);

	dwGoldMainProb = (DWORD)(dwGoldMainProb * m_fItemDrop);
	dwMainProb = (DWORD)(dwMainProb * m_fItemDrop);
}

vProperties g_pProperties;

NAKED void vMonsterDropLoad()
{
	static const Address addrExit = 0x0046DADD;
	__asm
	{
		MOV		DWORD PTR SS:[EBP-0x0FC8], EAX; //	dwItemCountMax
		push	eax;

		MOV		eax, DWORD PTR SS:[EBP-0x0FC4];	//		dwItemCountMin
		push	eax;

		MOV		eax, DWORD PTR SS:[EBP-0x0F90];	//		dwMainProb
		push	eax;

		MOV		eax, DWORD PTR SS:[EBP-0x0F60];//		dwGoldMax 
		push	eax;

		MOV		eax, DWORD PTR SS:[EBP-0x0F54];	//		dwGoldMin
		push	eax;

		MOV		eax, DWORD PTR SS:[EBP-0x0F4C];//		dwGoldMainProb
		push	eax;

		mov		ecx, g_pProperties;
		call	vProperties::ModifyDropRate;
		mov		ecx, addrDropMng;

		JMP addrExit;
	}
}