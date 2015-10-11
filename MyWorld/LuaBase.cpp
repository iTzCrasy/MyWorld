#include "stdafx.h"
#include "LuaBase.h"


CLuaBase::CLuaBase()
{
	m_pLuaState = nullptr;
	m_pLuaState = luaL_newstate();

	luaL_openlibs( m_pLuaState );
}

CLuaBase::~CLuaBase()
{
	if( m_pLuaState )
		lua_close( m_pLuaState );
}


void CLuaBase::RegisterFunction( char* szFromLuaFunc, lua_CFunction ToCFunc )
{
	lua_register( m_pLuaState, szFromLuaFunc, ToCFunc );
}

int CLuaBase::RunScript( const char* szFileName )
{
	return luaL_dofile( m_pLuaState, szFileName );
}

bool CLuaBase::GetLuaFunction( char* szFunc )
{
	lua_getglobal( m_pLuaState, szFunc );
	return lua_isfunction(m_pLuaState, -1);
}

void CLuaBase::CallLuaFunction( int nElem, int nReturn )
{
	if( lua_pcall( m_pLuaState, nElem, nReturn, 0 ) != 0 )
		Log(LOG_ERROR, "%s | %s", __FUNCTION__, ToString(-1));
}

double CLuaBase::GetGlobalNumber( char* szName )
{
	double fValue = 0;
	lua_getglobal( m_pLuaState, szName );
	if( lua_isnumber( m_pLuaState, -1 ) )
		fValue = ToNumber( -1 );
	Pop(1);

	return fValue;
}

const char* CLuaBase::GetGlobalString( char* szName )
{
	char* szValue = NULL;
	lua_getglobal( m_pLuaState, szName );
	if( lua_isstring( m_pLuaState, -1 ) )
		szValue = (char*)ToString( -1 );

	Pop( 1 );

	return szValue;
}

bool CLuaBase::GetGlobalBool( char* szName )
{
	BOOL bValue = FALSE;
	lua_getglobal( m_pLuaState, szName );
	if( lua_isboolean( m_pLuaState, -1 ) )
		bValue = ToBool( -1 );

	Pop( 1 );

	return bValue == TRUE? true : false;
}

void CLuaBase::Pop( int nPop )
{  
	if( nPop == 0 )
		lua_settop( m_pLuaState, 0 );
	else
		lua_pop( m_pLuaState, nPop );
}

double CLuaBase::GetFieldToNumber( int nStackPos, char* szName )
{
	double fValue = 0;
	lua_getfield( m_pLuaState, nStackPos, szName );
	if( lua_isnumber( m_pLuaState, -1 ) )
		fValue = ToNumber( -1 );
	Pop( 1 );

	return fValue;
}

const char* CLuaBase::GetFieldToString( int nStackPos, char* szName )
{
	char* szValue = NULL;
	lua_getfield( m_pLuaState, nStackPos, szName );
	if( lua_isstring( m_pLuaState, -1 ) )
		szValue = (char*)ToString( -1 );
	Pop( 1 );

	return szValue;
}

bool CLuaBase::GetFieldToBool( int nStackPos, char* szName )
{
	BOOL bValue = 0;
	lua_getfield( m_pLuaState, nStackPos, szName );
	if( lua_isboolean( m_pLuaState, -1 ) )
		bValue = ToBool( -1 );
	Pop( 1 );

	return bValue == TRUE? true: false;
} 