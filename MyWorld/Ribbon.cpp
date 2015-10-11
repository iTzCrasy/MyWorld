#include "stdafx.h"
#include <atlbase.h>
#include <atlcom.h>
#include <initguid.h>
#include <uiribbon.h>
#include <UIRibbonPropertyHelpers.h>
#include "vSelCharDlg.h"
#include "Ribbon.h"
#include "vGui.h"
#include "ribbonres.h"


extern vGui g_vGui;



HRESULT vGuiRibbon::OnViewChanged(UINT32 nViewID, UI_VIEWTYPE typeID, IUnknown* pView, UI_VIEWVERB verb, INT32 uReasonCode)
{
	return E_NOTIMPL;
}

HRESULT vGuiRibbon::OnCreateUICommand(UINT32 nCmdID, UI_COMMANDTYPE typeID, IUICommandHandler** ppCommandHandler)
{
// 	if(nCmdID == cmdEditUsers)
// 		return QueryInterface(IID_PPV_ARGS(ppCommandHandler));

	return E_NOTIMPL;
}

HRESULT vGuiRibbon::OnDestroyUICommand(UINT32 commandId, UI_COMMANDTYPE typeID, IUICommandHandler* pCommandHandler)
{
	return E_NOTIMPL;
}

HRESULT vGuiRibbon::Execute(UINT nCmdID, UI_EXECUTIONVERB verb, const PROPERTYKEY* key, const PROPVARIANT* ppropvarValue, IUISimplePropertySet* pCommandExecutionProperties)
{
	switch(verb)    
	{  
	case UI_EXECUTIONVERB_EXECUTE:
		{
// 			if(nCmdID == cmdEditUsers)
// 			{
// 				CreateDialog( g_vGui.m_hInstance, MAKEINTRESOURCEA( IDD_SEARCH_CHARACTER ), g_vGui.m_hWnd, DlgSearchCharProc );
// 			}	
		}
		break;
	}

	return S_OK;
}

HRESULT vGuiRibbon::UpdateProperty(UINT nCmdID, __in REFPROPERTYKEY key, __in_opt const PROPVARIANT* ppropvarCurrentValue, __out PROPVARIANT* ppropvarNewValue)
{

	HRESULT hr = E_FAIL;
	return hr;
}

//////////////////////////////////////////////////////////////////////////


HRESULT InitRibbon(HWND hWindowFrame)
{
	::CoCreateInstance(CLSID_UIRibbonFramework, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&g_pFramework));

	CComObject<vGuiRibbon>* pApplication = nullptr;
	CComObject<vGuiRibbon>::CreateInstance(&pApplication);
	g_pFramework->Initialize(hWindowFrame, pApplication);
	g_pFramework->LoadUI(g_hModule, MAKEINTRESOURCEW(APPLICATION_RIBBON));


	return S_OK;
}

void DestroyRibbon()
{
	if (g_pFramework)
	{
		g_pFramework->Destroy();
		g_pFramework->Release();
		g_pFramework = NULL;
	}
}