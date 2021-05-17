#pragma once
#include "cObj_Human.h"

class cObj_Player :
	public cObj_Human
{
private:

public:
	cObj_Player();
	~cObj_Player();

	void Setup() override;
	void Update() override;
};

