#pragma once
#include "cUI.h"

class cUI_Button :
	public cUI
{
public:
	cUI_Button();
	~cUI_Button();

	void Setup();
	void Update();
	void Render();
	void Down();
};

