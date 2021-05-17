#pragma once
#include "cMesh.h"

class cMap	:
	public cObject
{
public:
	cMesh*			m_pmeshMap;

public:
	cMap();
	~cMap();
	void Setup();
	void Update();
	void Render();
};

