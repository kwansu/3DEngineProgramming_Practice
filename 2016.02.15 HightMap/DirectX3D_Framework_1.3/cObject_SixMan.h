#pragma once
#include "cObject_Mario.h"

#define SIX_LINE_TIME	(ROUND_TIME / 6)

class cObject_SixMan :
	public cObject_Mario
{

public:
	cObject_SixMan();
	~cObject_SixMan();
	void Update();
	//void Render();
};

