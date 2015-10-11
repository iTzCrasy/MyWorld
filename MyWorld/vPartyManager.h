#pragma once

#include "vParty.h"

class vParty;

class vPartyManager
{
public:
	void		Inject();
	vParty*		GetParty( idParty id );
	BOOL		DeleteParty(idParty id);

};

