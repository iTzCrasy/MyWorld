#include "stdafx.h"
#include "vEditCharDlg.h"

bool vEditCharDlg::CreateEditCharDialog(DWORD dwUserId)
{
	if(m_bCreated)
		return true;


// 	::CoCreateInstance(CLSID_UIRibbonFramework, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&g_pFramework));
// 
// 	CComObject<vGuiRibbon>* pApplication = NULL;
// 	CComObject<vGuiRibbon>::CreateInstance(&pApplication);
// 	g_pFramework->Initialize(hWindowFrame, pApplication);
// 	g_pFramework->LoadUI(g_hModule, MAKEINTRESOURCEW(APPLICATION_RIBBON));



	LoadUser(dwUserId);


	return true;
}


void vEditCharDlg::LoadUser(DWORD dwId)
{

}



vEditCharDlg g_vDlgEditChar;