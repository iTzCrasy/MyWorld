#include "stdafx.h"
#include "vWorldManager.h"
#include "vGui.h"
#include "vUserManager.h"
#include "vPartyManager.h"
#include "vLog.h"
#include "vClient.h"


void CreateConsole();

CComModule _Module;

extern vWorldManager	g_pWorldMng;
extern vEvents			g_pEvents;
extern vGui				g_vGui;
extern vTextCmd			g_pTextCmd;
extern vLog				g_pLog;
extern vClient			g_pClient;
extern vProperties		g_pProperties;
extern vUserManager		g_pUserMng;
extern vPartyManager	g_pPartyMng;


BOOL APIENTRY DllMain( HMODULE hDllHandle, DWORD dwReason, LPVOID lpreserved )
{
	if(dwReason == DLL_PROCESS_ATTACH)
	{
		CoInitialize(nullptr);

		TOKEN_PRIVILEGES TPLEGES;	
		TPLEGES.PrivilegeCount=1;
		TPLEGES.Privileges->Luid.LowPart = 0x00000014;
		TPLEGES.Privileges->Luid.HighPart = 0x00000000;
		TPLEGES.Privileges->Attributes = 0x00000002;

		HANDLE htoken;
		OpenProcessToken(hDllHandle, TOKEN_ALL_ACCESS, &htoken);
		AdjustTokenPrivileges(htoken, 0, &TPLEGES, 0, 0, 0);

		INITCOMMONCONTROLSEX InitCtrls;
		InitCtrls.dwSize = sizeof(InitCtrls);
		InitCtrls.dwICC = ICC_WIN95_CLASSES;
		InitCommonControlsEx(&InitCtrls);

		g_hModule = hDllHandle;
		g_hModuleSrv = GetModuleHandleA( nullptr );
		g_uKey = *(ULONG*)0x007831CC;
		g_uIdofMulti = *(ULONG*)0x007831C8;

		DisableThreadLibraryCalls(hDllHandle);
		CreateConsole();

		Log(LOG_INFO, "--- vIrtuaL W0rld 0.6 by ---");
		Log(LOG_INFO, "Build: %s %s\n\n", __DATE__, __TIME__);

		Log(LOG_INFO, ">> Instance: ");
		Log(LOG_INFO, "DLL: %x  SRV: %x\n", g_hModule, g_hModuleSrv);
		
	
		g_prj.Inject();
		g_pLog.Inject();
		g_vGui.Inject();
		g_pWorldMng.Inject();
		g_pEvents.Inject();
		g_pTextCmd.Inject();
		g_pClient.Inject();
		g_pProperties.Inject();
		g_pUserMng.Inject();
		g_pPartyMng.Inject();
	}

	return TRUE;
}

void CreateConsole()
{
	AllocConsole();

	HANDLE lStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int hConHandle = _open_osfhandle(PtrToUlong((ULONG)lStdHandle), _O_TEXT);
	FILE* fp = _fdopen(hConHandle, "w");
	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);

	lStdHandle = GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle(PtrToUlong((ULONG)lStdHandle), _O_TEXT);
	fp = _fdopen(hConHandle, "r");
	*stdin = *fp;
	setvbuf(stdin, NULL, _IONBF, 0);

	lStdHandle = GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(PtrToUlong((ULONG)lStdHandle), _O_TEXT);
	fp = _fdopen(hConHandle, "w");
	*stderr = *fp;
	setvbuf(stderr, NULL, _IONBF, 0);
	::SetConsoleMode( lStdHandle, ENABLE_ECHO_INPUT );

	char szStr[64] = {0};
	sprintf_s( szStr, "vIrtuaL W0rLd - Build: %s %s", __DATE__, __TIME__ );
	SetConsoleTitleA( szStr );
}