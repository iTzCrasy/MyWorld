#pragma once

typedef DWORD Address;



class CDetourEnableWriteOnCodePage
{
public:
	CDetourEnableWriteOnCodePage(PBYTE pbCode, LONG cbCode)
	{
		m_pbCode = pbCode;
		m_cbCode = cbCode;
		m_dwOldPerm = 0;
		m_hProcess = GetCurrentProcess();

		if (m_pbCode && m_cbCode) {
			if (!FlushInstructionCache(m_hProcess, pbCode, cbCode)) {
				return;
			}
			if (!VirtualProtect(pbCode,
				cbCode,
				PAGE_EXECUTE_READWRITE,
				&m_dwOldPerm)) {
					return;
			}
		}
	}

	~CDetourEnableWriteOnCodePage()
	{
		if (m_dwOldPerm && m_pbCode && m_cbCode) {
			DWORD dwTemp = 0;
			if (!FlushInstructionCache(m_hProcess, m_pbCode, m_cbCode)) {
				return;
			}
			if (!VirtualProtect(m_pbCode, m_cbCode, m_dwOldPerm, &dwTemp)) {
				return;
			}
		}
	}

	BOOL SetPermission(DWORD dwPerms)
	{
		if (m_dwOldPerm && m_pbCode && m_cbCode) {
			m_dwOldPerm = dwPerms;
			return TRUE;
		}
		return FALSE;
	}

	BOOL IsValid(VOID)
	{
		return m_pbCode && m_cbCode && m_dwOldPerm;
	}

private:
	HANDLE  m_hProcess;
	PBYTE   m_pbCode;
	LONG    m_cbCode;
	DWORD   m_dwOldPerm;
};

//////////////////////////////////////////////////////////////////////////
//=> Functions

bool bDataCompare(const BYTE* pData, const BYTE* bMask, const char* szMask);
DWORD dwFindPattern(DWORD dwAddress, DWORD dwLen, BYTE* bMask,char* szMask);

void Log(int nLogType, char* szString, ...);
void LogEx(WORD wAttribute, int nLogType, char* szString, ...);
void vMsgBox( UINT uType, char* szTitle, char* szText, ...);

char*	AuthToString(DWORD dwAuth);
void	AsmPush(PBYTE pbTarget, DWORD dwSize);
void	AsmCall(PBYTE pbTarget, PBYTE pbAddr);
int xRandom(int min, int max);
int xRandom(); 


inline PBYTE GenMovEax(PBYTE pbCode, UINT32 nValue)
{
	*pbCode++ = 0xB8;
	*((UINT32*&)pbCode)++ = nValue;
	return pbCode;
}

inline PBYTE GenMovEbx(PBYTE pbCode, UINT32 nValue)
{
	*pbCode++ = 0xBB;
	*((UINT32*&)pbCode)++ = nValue;
	return pbCode;
}

inline PBYTE GenMovEcx(PBYTE pbCode, UINT32 nValue)
{
	*pbCode++ = 0xB9;
	*((UINT32*&)pbCode)++ = nValue;
	return pbCode;
}

inline PBYTE GenMovEdx(PBYTE pbCode, UINT32 nValue)
{
	*pbCode++ = 0xBA;
	*((UINT32*&)pbCode)++ = nValue;
	return pbCode;
}

inline PBYTE GenMovEsi(PBYTE pbCode, UINT32 nValue)
{
	*pbCode++ = 0xBE;
	*((UINT32*&)pbCode)++ = nValue;
	return pbCode;
}

inline PBYTE GenMovEdi(PBYTE pbCode, UINT32 nValue)
{
	*pbCode++ = 0xBF;
	*((UINT32*&)pbCode)++ = nValue;
	return pbCode;
}

inline PBYTE GenMovEbp(PBYTE pbCode, UINT32 nValue)
{
	*pbCode++ = 0xBD;
	*((UINT32*&)pbCode)++ = nValue;
	return pbCode;
}

inline PBYTE GenMovEsp(PBYTE pbCode, UINT32 nValue)
{
	*pbCode++ = 0xBC;
	*((UINT32*&)pbCode)++ = nValue;
	return pbCode;
}

inline PBYTE GenPush(PBYTE pbCode, UINT32 nValue)
{
	*pbCode++ = 0x68;
	*((UINT32*&)pbCode)++ = nValue;
	return pbCode;
}

inline PBYTE GenPushad(PBYTE pbCode)
{
	*pbCode++ = 0x60;
	return pbCode;
}

inline PBYTE GenPopad(PBYTE pbCode)
{
	*pbCode++ = 0x61;
	return pbCode;
}

inline PBYTE GenJmp(PBYTE pbCode, PBYTE pbJmpDst, PBYTE pbJmpSrc = 0)
{
	if (pbJmpSrc == 0) 
		pbJmpSrc = pbCode;

	*pbCode++ = 0xE9;
	*((INT32*&)pbCode)++ = pbJmpDst - (pbJmpSrc + 5);
	return pbCode;
}

inline PBYTE GenCall(PBYTE pbCode, PBYTE pbJmpDst, PBYTE pbJmpSrc = 0)
{
	if (pbJmpSrc == 0) 
		pbJmpSrc = pbCode;

	*pbCode++ = 0xE8;
	*((INT32*&)pbCode)++ = pbJmpDst - (pbJmpSrc + 5);
	return pbCode;
}

inline PBYTE GenBreak(PBYTE pbCode)
{
	*pbCode++ = 0xcc;
	return pbCode;
}

inline PBYTE GenRet(PBYTE pbCode)
{
	*pbCode++ = 0xc3;
	return pbCode;
}

inline PBYTE GenNop(PBYTE pbCode)
{
	*pbCode++ = 0x90;
	return pbCode;
}