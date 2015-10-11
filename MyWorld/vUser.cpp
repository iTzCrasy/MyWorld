#include "stdafx.h"
#include "vWorld.h"
#include "vUser.h"
#include "vAr.h"
#include "vGmProtect.h"

extern vGmProtect g_gmProtect;


void vUser::ShowLoginInfo()
{
	if(GetAuthorization() != AUTH_GENERAL)
	{
		AddText("Login auth: %s", AuthToString(GetAuthorization()));
	}
}

void vUser::AddText(char* szText, ...)
{
	if(IsDelete())		return;

	char szBuff[512] = {0,};
	va_list arg;
	va_start(arg, szText);
	vsnprintf_s(szBuff, 512, szText, arg);
	va_end(arg);

	m_Snapshot.cb++;
	m_Snapshot.ar << NULL_ID;
	m_Snapshot.ar << SNAPSHOTTYPE_TEXT;
	m_Snapshot.ar << TEXT_GENERAL;
	m_Snapshot.ar.WriteString( szBuff );
}

void vUser::AddPKValue()
{
	if( IsDelete() )	return;

	m_Snapshot.cb++;
	m_Snapshot.ar << GetId();
	m_Snapshot.ar << (DWORD)0x210072;
	m_Snapshot.ar << PK_PKVALUE;
	m_Snapshot.ar << GetPKValue();
}

void vUser::AddDefinedText(int dwText, char* szFormat, ...)
{
	char szBuff[512] = {0,};
	va_list arg;
	va_start(arg, szFormat);
	vsnprintf_s(szBuff, 512, szFormat, arg);
	va_end(arg);

	m_Snapshot.cb++;
	m_Snapshot.ar << GetId();
	m_Snapshot.ar << (DWORD)0x2100A6;
	m_Snapshot.ar << dwText;
	m_Snapshot.ar.WriteString( szBuff );
}

void vUser::AddDefinedText( int dwText )
{
	if( IsDelete() )	return;

	m_Snapshot.cb++;
	m_Snapshot.ar << GetId();
	m_Snapshot.ar << (DWORD)0x2100A5;
	m_Snapshot.ar << dwText;
}

void vUser::AddChatText( int dwText, char* szFormat, ... )
{
	if( IsDelete() )	return;

	char szBuffer[256];

	va_list args;
	va_start( args, szFormat );
	_vsntprintf_s( szBuffer, 256, szFormat, args );
	va_end( args );

	m_Snapshot.cb++;
	m_Snapshot.ar << GetId();
	m_Snapshot.ar << (DWORD)0x21009E;
	m_Snapshot.ar << dwText;
	m_Snapshot.ar.WriteString( szBuffer );
}

void vUser::AddPlaySound( DWORD idSound )
{
	if( IsDelete() )	return;

	m_Snapshot.cb++;
	m_Snapshot.ar << GetId();
	m_Snapshot.ar << (DWORD)0x2100CB;
	m_Snapshot.ar << (byte)0;
	m_Snapshot.ar << idSound;
}

void vUser::AddSetExperience( __int64 nExp1, WORD wLevel, int nSkillPoint, int nSkillLevel, __int64 nDeathExp, WORD wDeathLevel )
{
	if( IsDelete() )	return;

	m_Snapshot.cb++;
	m_Snapshot.ar << GetId();
	m_Snapshot.ar << (DWORD)0x210008;
	m_Snapshot.ar << nExp1 << wLevel << nSkillLevel << nSkillPoint << nDeathExp << wDeathLevel;
}

void vUser::AddGoldText( int nPlus )
{
	AddDefinedText( TID_GAME_REAPMONEY, "%d %d", nPlus, GetGold() );
}


void vUser::SetReturnPos( D3DXVECTOR3& vPos )
{
	m_dwReturnWorldID = GetWorld()->GetId();
	m_vReturnPos = vPos;
}
