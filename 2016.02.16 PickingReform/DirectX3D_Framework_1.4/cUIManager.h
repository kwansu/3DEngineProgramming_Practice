#pragma once
#include "stdUIObjects.h"

class cUIManager :
	public iUI_Messenger
{
	SINGLETONE(cUIManager);

private:
	cUI_Button*		m_pButton;
	vector<cUI*>	m_apUI;
	list<cUI*>		m_listAutoReleaseUI;

public:
	void Setup();
	void Update();
	void Render();
	void DisableUI(cUI* pSender);
};

extern cUIManager* g_pUIManager;
