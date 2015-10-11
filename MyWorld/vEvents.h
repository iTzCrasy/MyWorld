#pragma once
#include "vCtrl.h"
#include "vMover.h"
#include "vUser.h"


using namespace tbb;

class vCtrl;
class vMover;
class vUser;

typedef void (__stdcall* tDestroyPlayer)(vUser* pUser);

class vEvents
{

public:
	void Inject();

	tDestroyPlayer m_pDestroyPlayerHook;
};

void vAdduser();
void vOnJoin();
void vProcess();
void vDoDie();
void __stdcall vOnDestroyPlayer(vUser* pUser);
void vOnRevival();
void vOnNotify();