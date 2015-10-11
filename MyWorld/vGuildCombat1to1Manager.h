#pragma once

#include "vCtrl.h"
#include "vMover.h"
#include "vUser.h"

class vCtrl;
class vMover;
class vUser;

class vGuildCombat1to1Manager
{
public:
	void Inject();

	BOOL	IsPossibleUser( vUser* pUser );
};

