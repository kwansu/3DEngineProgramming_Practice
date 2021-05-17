#pragma once
#include "cObj_Human.h"

class cObj_Player :
	public cObj_Human, public iInputProcessor
{
private:

public:
	cObj_Player();
	~cObj_Player();

	void Setup() override;
	void Update() override;

private:
	void InputProcess(iInputProcessor* pGenerator) override;
};

