#pragma once
#include "cUI_Button.h"

class cUI_Quest :
	public cUI_Box
{
private:
	bool	m_bDrag;
	
public:
	cUI_Quest();
	~cUI_Quest();

	void Setup() override;
	void Update() override;
	void Event(cUI* pGenerator, bool bDown) override;
};

