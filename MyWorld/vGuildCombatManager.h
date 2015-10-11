#pragma once
#include "vCtrl.h"
#include "vMover.h"
#include "vUser.h"

class vCtrl;
class vMover;
class vMover;

class vGuildCombatManager
{
public:
	enum { OPEN_STATE, CLOSE_STATE, WAR_STATE, COMPLET_CLOSE_STATE, GM_COLSE_STATE };
	enum { NOTENTER_STATE = 100, NOTENTER_COUNT_STATE, ENTER_STATE, MAINTENANCE_STATE, WAR_WAR_STATE, WAR_CLOSE_STATE, WAR_CLOSE_WAIT_STATE, WAR_TELEPORT_STATE };
	enum { ALLMSG = 1000, GUILDMSG, JOINMSG, WORLDMSG, STATE, WARSTATE, WAIT };


	void Inject();

	int		GetState(){ return *(int*)0x0086DB18;	}
};

