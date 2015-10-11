#pragma once
#include "stdafx.h"
#include "vUserManager.h"
#include "vEditCharDlg.h"

extern vEditCharDlg g_vDlgEditChar;
extern vUserManager	g_pUserMng;


INT_PTR CALLBACK DlgSearchCharProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if(uMsg == WM_COMMAND && HIWORD(wParam) == IDC_BUTTON1 )
	{
		char szName[MAX_NAME] = {0};
		::GetDlgItemText( hwndDlg, IDC_EDIT1, szName, MAX_NAME );

		DWORD dwId = g_pUserMng.GetUserId(szName);
		if(!dwId)
			MessageBoxA( hwndDlg, "Character not found :<", "Search Character", MB_ICONERROR | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2 );
		else 
		{
			if(!g_vDlgEditChar.m_bCreated)
				g_vDlgEditChar.CreateEditCharDialog(dwId);
			else
				g_vDlgEditChar.LoadUser(dwId);
		}

		return TRUE;
	}

	return FALSE;
}