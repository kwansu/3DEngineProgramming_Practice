#pragma once
#include "cGeometry.h"

class ASELoader;

class cBone
{
	friend class ASELoader;
private:
	vector<cGeometry*>	m_apChild;

public:
	cBone();
	~cBone();
	void Update();
	void Render();
};

