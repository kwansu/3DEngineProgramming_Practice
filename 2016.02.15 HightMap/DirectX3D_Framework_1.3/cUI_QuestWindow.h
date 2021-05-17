#pragma once
#include "cUI_Button.h"

class cUI_QuestWindow : 
	public cUI
{
private:
	cUI_Button*		m_pClose;
	cUI_Button*		m_pYes;
	cUI_Button*		m_pNo;

public:
	cUI_QuestWindow();
	~cUI_QuestWindow();
	void Update();
	void Render();
};

