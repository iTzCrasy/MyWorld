#pragma once
#include "vCtrl.h"
#include "vMover.h"
#include "vUser.h"

class vCtrl;
class vMover;
class vUser;

class vEventArena
{
public:
	void Inject();

	BOOL IsActive() { return *(BOOL*)0x007813F0; } 
};

