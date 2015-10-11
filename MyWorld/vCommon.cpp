#include "stdafx.h"
#include "vCommon.h"

bool bDataCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for(;*szMask;++szMask,++pData,++bMask)
		if(*szMask=='x' && *pData!=*bMask ) 
			return false;
	return (*szMask) == NULL;
} 

DWORD dwFindPattern(DWORD dwAddress, DWORD dwLen, BYTE* bMask,char* szMask)
{
	for(DWORD i=0; i < dwLen; i++)
		if( bDataCompare( (BYTE*)( dwAddress+i ),bMask,szMask) )
			return (DWORD)(dwAddress+i);
	return NULL;
}

void Log(int nLogType, char* szString, ...)
{
	char szBuff[512] = {0,};
	va_list arg;
	va_start(arg, szString);
	vsnprintf_s(szBuff, 512, szString, arg);
	va_end(arg);


	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SYSTEMTIME time;
	GetLocalTime( &time );
	printf("[%02d:%02d:%02d]", time.wHour, time.wMinute, time.wSecond );

	switch(nLogType)
	{
	case LOG_ERROR:
		{
			SetConsoleTextAttribute( hStdout, COLOR_RED );
			printf(" [Err] ");
			break;
		}
	case LOG_SUCCESS:
		{
			SetConsoleTextAttribute( hStdout, COLOR_GREEN );
			printf(" [SUC] ");
			break;
		}
	case LOG_INFO:
		{
			SetConsoleTextAttribute( hStdout, COLOR_BLUE );
			printf(" [INF] ");
			break;
		}
	}
	SetConsoleTextAttribute( hStdout, COLOR_SILVER );
	printf("=> %s\n", szBuff);
}


void LogEx(WORD wAttribute, int nLogType, char* szString, ...)
{
	char szBuff[512] = {0,};
	va_list arg;
	va_start(arg, szString);
	vsnprintf_s(szBuff, 512, szString, arg);
	va_end(arg);


	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute( hStdout, wAttribute );
	printf("%s\n", szBuff);
	SetConsoleTextAttribute( hStdout, COLOR_SILVER );
}


void vMsgBox( UINT uType, char* szTitle, char* szText, ...)
{
	char szStrOut[256] = {0};

	va_list arg;
	va_start(arg, szText);
	_vsnprintf_s(szStrOut, 256, szText, arg);
	va_end(arg);

	MessageBoxA(NULL, szStrOut, szTitle, uType);
}

char* AuthToString(DWORD dwAuth)
{
	if(dwAuth == AUTH_ADMINISTRATOR)
		return "Administrator";
	return "Game Master";
}

void AsmPush(PBYTE pbTarget, DWORD dwSize)
{
	CDetourEnableWriteOnCodePage ewTarget(pbTarget, 5);
	if (!ewTarget.IsValid())
		return;

	GenPush(pbTarget, dwSize);
}

void AsmCall(PBYTE pbTarget, PBYTE pbAddr)
{
	CDetourEnableWriteOnCodePage ewTarget(pbTarget, 5);
	if (!ewTarget.IsValid())
		return;

	GenCall( pbTarget, pbAddr);
}


int xRandom(int min, int max) 
{ 
	return min + rand() % (max - min + 1); 
} 

int xRandom()
{
	return rand() % (RAND_MAX + 1 );
}