#pragma once

#include "stdafx.h"


#define MAX_TOKENSTR 2048

struct vScanner
{
public:
	BOOL	xUnkn01;
	BOOL	m_bComma;		//	BOOL	GetComma()		{ return *(BOOL*)(this+4);		}
	byte	m_bMemFlag;		//	byte	GetMemFlag()	{ return *(byte*)(this+8);		}

	int		m_nProgSize;	//	9 + 4 = 12
	DWORD	m_dwDef;		//  DWORD	GetDef()		{ return *(DWORD*)(this+16);	}
	CHAR*	m_lpMark;		//	char*	GetMark()		{ return *(char**)(this+20);	}			
	CHAR*	m_pProg;		//  char*	GetProc()		{ return *(char**)(this+24);	}				
	CHAR*	m_pBuf;			//  char*	GetBuff()		{ return *(char**)(this+28);	}

	char*	szUnkn;			//32
	char*	szToken;		//36
	char*	szUnkn02;		//40

	char*		token;		//	char*	GetToken()		{ return *(char**)(this+40);	}				
	char		m_mszToken[ MAX_TOKENSTR ];	 //char*	GetBaseToken()	{ return *(char**)(this+44);	}
	int			tokenType;	// 2092				
	int			tok;		// 		2096	
	int			m_nDoubleOps;// 2100
	DWORD		dwValue;	//	DWORD	GetValue()		{ return *(DWORD*)(this+2104);	}
	char*		_sm_strFileName_01; // 8 
	char*		_sm_strFileName_; // 12
	BOOL		m_bErrorCheck; // BOOL	GetErrorCheck()	{ return *(BOOL*)(this+2112);	}

	void		GetToken( BOOL bComma = FALSE)
	{
		static const Address addrCall = 0x00666520;
		__asm
		{
			push	bComma;
			lea		ecx, this;
			call	addrCall;
		}
	}
};