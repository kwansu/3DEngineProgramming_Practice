#pragma once
#include "stdGameObjects.h"

class cGameObjectManager
{
	SINGLETONE(cGameObjectManager);

private:
	cGrid*	m_pGrid;

	vector<cGameObject*>	m_vecpGameObjects;

public:
	void Setup();
	void Update();
	void Render();
};


extern cGameObjectManager*	g_pGameObjects;
