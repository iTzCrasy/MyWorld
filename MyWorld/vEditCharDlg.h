#pragma once
#include "vCtrl.h"
#include "vMover.h"
#include "vUser.h"

class vCtrl;
class vMover;
class vUser;

class vEditCharDlg
{
public:
	bool CreateEditCharDialog(DWORD dwUserId);
	void LoadUser(DWORD dwId);


	bool m_bCreated;
};

