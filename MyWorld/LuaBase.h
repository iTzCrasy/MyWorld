#pragma once
 
 class CLuaBase  
 {
 public:
 	CLuaBase();
 	virtual ~CLuaBase();
 
 	lua_State*	GetLuaState()								{  return m_pLuaState;  }
 	void		RegisterFunction( char* szFromLuaFunc, lua_CFunction ToCFunc );
 	int			RunScript( const char* szFileName );
 
 	bool		IsNil( int nStackPos )						{  return lua_isnil( m_pLuaState, nStackPos );  }
 	bool		IsTable( int nStackPos )					{  return lua_istable( m_pLuaState, nStackPos );  }
 
 	void		PushNumber( double nValue )					{  lua_pushnumber( m_pLuaState, nValue );  }
 	void		PushString( const char* szValue )			{  lua_pushstring( m_pLuaState, szValue );  }
 	void		PushPointer( void* p )						{  lua_pushlightuserdata( m_pLuaState, p );  }
 	void		PushBool( int bValue )						{  lua_pushboolean( m_pLuaState, bValue );  }
 	void		PushNil()									{  lua_pushnil( m_pLuaState );  }
 	void		Pop( int nPop );
 
 	double		ToNumber( int nStackPos )					{  return lua_tonumber( m_pLuaState, nStackPos );  }
 	const char*	ToString( int nStackPos )					{  return lua_tostring( m_pLuaState, nStackPos );  }
 	bool		ToBool( int nStackPos )						{  return lua_toboolean( m_pLuaState, nStackPos ) == TRUE? true: false;  }
 	int			TableLoop( int nStackPos )					{  return lua_next( m_pLuaState, nStackPos );  }	
 	void		GetGlobal( char* szName )					{  lua_getglobal( m_pLuaState, szName );  }
 	double		GetGlobalNumber( char* szName );
 	const char* GetGlobalString( char* szName );
 	bool		GetGlobalBool( char* szName );
 	void		GetField( int nStackPos, char* szName )		{  lua_getfield( m_pLuaState, nStackPos, szName );  }
 	double		GetFieldToNumber( int nStackPos, char* szName );
 	const char* GetFieldToString( int nStackPos, char* szName );
 	bool		GetFieldToBool( int nStackPos, char* szName );
 
 	bool		GetLuaFunction( char* szFunc );
 	void		CallLuaFunction( int nElem, int nReturn );
 
 private:
 	lua_State*	m_pLuaState;
 };
