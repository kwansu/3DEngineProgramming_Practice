#pragma once
#include "cObj_Box.h"

class cObj_Plane :
	public cObj_Box
{
public:
	cObj_Plane();
	~cObj_Plane();

	void Setup() override;
	void Update() override;
};

