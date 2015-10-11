#include "stdafx.h"
#include "vLog.h"

void vLog::Inject()	
{
	SafeDetour( 0x006EC7ED, vMyLog);
}

vLog g_pLog;

void MyLog(char* szText, char* szFunctionName )
{
	LogEx( FOREGROUND_GREEN | BACKGROUND_BLUE, LOG_INFO, "%s %s", szFunctionName, szText);
}

//02336F58
//-24
NAKED void vMyLog( )
{
	static const Address addrJmp = 0x006EC7F7;
	static char* szType = "%s : %s";

	__asm
	{
		mov		eax, DWORD PTR SS:[ esp + 0x10];
		mov		eax, [eax + 0x4];
		push	eax;

		mov		eax, DWORD PTR SS:[ ebp - 0x2C ];
		push	eax;

		call	MyLog;

		pop		eax;
		pop		eax;


		mov		DWORD PTR SS:[ ebp - 0x4 ], 0;
		mov		edx,DWORD PTR SS:[ ebp - 8 ];
	

		jmp		addrJmp;
	}
}