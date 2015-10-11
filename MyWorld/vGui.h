#pragma once

#define WINDOWSIZE_X 950
#define WINDOWSIZE_Y 650

#define ID_TREEVIEW_MAIN 5000
#define ID_STATIC_LEVEL 5001

#include "vCtrl.h"
#include "vMover.h"
#include "vUser.h"

class vCtrl;
class vMover;
class vUser;

class vGui
{
public:
	ATOM MyRegisterClass(HINSTANCE hInstance);

	void AddUser(vUser* pUser);
	void RemoveUser(vUser* pUser);
	void DrawUser(vUser* pUser);

	void Inject(void);
	void CreateGui();

	HWND m_hWnd;
	HWND m_hWndWorldServer;
	HINSTANCE m_hInstance;
	HWND m_hWndTree;

	HWND m_hStaticLevel;


};


LRESULT CALLBACK GuiProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK TreeViewProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void vShowNormalWindow();
void vHideWnd();