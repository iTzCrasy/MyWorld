#include "stdafx.h"
#include "Ribbon.h"
#include "vUserManager.h"
#include "vDlgSetLevel.h"
#include "resource.h"
#include "vGui.h"

extern vUserManager g_pUserMng;

void vGui::Inject()
{
	SafeDetour( 0x00522A00, vShowNormalWindow );
	SafeDetour( 0x00522724,	0x00522788 );
	SafeDetour( 0x00522923,	vHideWnd );
}

ATOM vGui::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXA wcex = {0};

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= GuiProc;
	wcex.hInstance		= hInstance;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= "vworldwnd";

	return RegisterClassExA(&wcex);
}

WNDPROC procEdit;
INT_PTR CALLBACK TreeViewCallback(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		Log(LOG_INFO, "%s >> Test", __FUNCTION__);

	case WM_NCLBUTTONDBLCLK:
		{
			Log(LOG_INFO, "%s >> Test", __FUNCTION__);


			break;
		}

	}

	return FALSE;
	//return CallWindowProc(procEdit, hwndDlg, uMsg, wParam, lParam);
}

void vGui::CreateGui()
{
	MyRegisterClass(m_hInstance);

	int xPos = (GetSystemMetrics(SM_CXSCREEN) - WINDOWSIZE_X)/2;
	int yPos = (GetSystemMetrics(SM_CYSCREEN) - WINDOWSIZE_Y)/2;

	m_hWnd		= CreateWindowA( "vworldwnd", "vIrtual World ADCP", WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME, xPos, yPos, WINDOWSIZE_X, WINDOWSIZE_Y, NULL, NULL, m_hInstance, NULL);
	m_hWndTree	= CreateWindowA( WC_TREEVIEW, "Tree View", WS_VISIBLE | WS_CHILD | WS_BORDER, NULL, 147, 110, WINDOWSIZE_Y-146, m_hWnd, (HMENU)ID_TREEVIEW_MAIN, m_hInstance, NULL );

	int x = 150;
	int y = 150;

	m_hStaticLevel = CreateWindowA( WC_STATIC, "Level", WS_CHILD, x, y, 150, 25, m_hWnd, (HMENU)ID_STATIC_LEVEL, m_hInstance, NULL );

	Log(LOG_INFO, "%x > %x", GetWindowLongPtr(m_hWndTree, GWLP_WNDPROC), GuiProc );

	InitRibbon(m_hWnd);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
}

void vGui::AddUser(vUser* pUser)
{
	pUser->m_pTvInsert.hParent = NULL;
	pUser->m_pTvInsert.hInsertAfter = TVI_ROOT;
	pUser->m_pTvInsert.item.mask = TVIF_TEXT;
	pUser->m_pTvInsert.item.pszText = pUser->GetName();
	pUser->m_pTvInsert.item.cchTextMax = 16;
	pUser->m_pTvInsert.item.iImage = 0;
	pUser->m_pTvInsert.item.iSelectedImage = 1;
	TreeView_InsertItem(m_hWndTree, &pUser->m_pTvInsert);
}

void vGui::RemoveUser(vUser* pUser)
{
	TreeView_DeleteItem(m_hWndTree, pUser->m_pTvInsert.item.hItem);
}

void vGui::DrawUser(vUser* pUser)
{
	char szBuff[64] = {0};
	sprintf_s( szBuff, "Level: %i", pUser->GetLevel());

	SetWindowText(m_hStaticLevel, szBuff);
	ShowWindow(m_hStaticLevel, SW_SHOW);
}

vGui g_vGui;

LRESULT CALLBACK GuiProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc; 
	int wmId, wmEvent;

	switch (message)
	{
	case WM_NOTIFY:
		{
			if( ((LPNMHDR)lParam)->code == NM_DBLCLK ) 
			{
				switch( ((LPNMHDR)lParam)->idFrom )
				{
				case ID_TREEVIEW_MAIN:
					{
						HTREEITEM pSelected = TreeView_GetSelection(g_vGui.m_hWndTree);
						if(!pSelected)
							return 0;

						TVITEM item;
						item.hItem = pSelected;
						item.mask = TVIF_TEXT;
						char szName[16] = {0};
						item.pszText = szName;
						item.cchTextMax = 16;
						::SendMessage(g_vGui.m_hWndTree, TVM_GETITEM, 0, (LPARAM)&item);

						DWORD dwId = g_pUserMng.GetUserId(szName);
						vUser* pUser = g_pUserMng.GetUserById(dwId);
						if(!pUser)
							return 0;
						g_vGui.DrawUser(pUser);
						break;
					}

				case ID_STATIC_LEVEL:
					{
						Log(LOG_INFO,"%s", __FUNCTION__);
						break;
					}
				}				
			}

			break;
		}
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam); 
		//switch (wmId)
		//{
			Log(LOG_SUCCESS, "%i %i >>", wmId, wmEvent);
			return DefWindowProc(hWnd, message, wParam, lParam);
		//}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return FALSE;
}


void ShowNormalWindow(HINSTANCE hInstance, HWND hWndWsrv)
{
	g_vGui.m_hWndWorldServer = hWndWsrv;
	g_vGui.m_hInstance = hInstance;

	g_vGui.CreateGui();
	ShowWindow(hWndWsrv, SW_HIDE);
}

NAKED void vShowNormalWindow()
{
	static const Address addrJmp = 0x00522A28;
	__asm
	{
		mov		ecx, DWORD PTR SS:[ ebp + 0x8 ];
		push	ecx;

		mov		ecx, DWORD PTR SS:[ ebp - 0x14 ];
		push	ecx;

		call	ShowNormalWindow;
		pop		ecx;
		pop		ecx;

		jmp		addrJmp;
	}
}

NAKED void vHideWnd()
{
	static const Address addrJmp = 0x0052292F;
	__asm
	{
		push	SWP_HIDEWINDOW;
		push    416;
		push    800;
		JMP		addrJmp;
	}
}