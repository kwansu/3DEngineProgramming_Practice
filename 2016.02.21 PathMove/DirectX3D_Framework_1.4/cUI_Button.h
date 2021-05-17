#pragma once
#include "cUI_Box.h"

class cUI_Button :
	public cUI_Box
{
private:
	bool	m_bClicked;

public:
	cUI_Button();
	~cUI_Button();

	virtual void Update() override;
};

