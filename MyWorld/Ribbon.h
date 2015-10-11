#pragma once

#include <atlbase.h>
#include <atlcom.h>
#include <initguid.h>

#include <uiribbon.h>
#include <UIRibbonPropertyHelpers.h>

class vGuiRibbon : public CComObjectRootEx<CComMultiThreadModel>, public IUIApplication, public IUICommandHandler
{
public:
	BEGIN_COM_MAP(vGuiRibbon)
		COM_INTERFACE_ENTRY(IUIApplication)
		COM_INTERFACE_ENTRY(IUICommandHandler)
	END_COM_MAP()

	STDMETHOD(OnViewChanged)(UINT32 nViewID, __in UI_VIEWTYPE typeID, __in IUnknown* pView, UI_VIEWVERB verb, INT32 uReasonCode);
	STDMETHOD(OnCreateUICommand)(UINT32 nCmdID, __in UI_COMMANDTYPE typeID, __deref_out IUICommandHandler** ppCommandHandler);
	STDMETHOD(OnDestroyUICommand)(UINT32 commandId, __in UI_COMMANDTYPE typeID, __in_opt IUICommandHandler* pCommandHandler);


	STDMETHODIMP Execute(UINT nCmdID, UI_EXECUTIONVERB verb, __in_opt const PROPERTYKEY* key, __in_opt const PROPVARIANT* ppropvarValue, __in_opt IUISimplePropertySet* pCommandExecutionProperties);
	STDMETHODIMP UpdateProperty(UINT nCmdID, __in REFPROPERTYKEY key, __in_opt const PROPVARIANT* ppropvarCurrentValue, __out PROPVARIANT* ppropvarNewValue);

private:
	BOOL _fEnabled;
};

void DestroyRibbon();
HRESULT InitRibbon(HWND hWindowFrame);