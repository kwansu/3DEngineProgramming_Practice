#pragma once
#include "stdGameObjects.h"
#include "cDijkstraManager.h"

class cGameObjectManager
{
	SINGLETONE(cGameObjectManager);

private:
	cGrid*	m_pGrid;
	cDijkstraManager a;

	vector<cGameObject*>	m_vecpGameObjects;

	D3DLIGHT9				m_light;

public:
	void Setup();
	void Relese();
	void Update();
	void Render();
};


extern cGameObjectManager*	g_pGameObjects;
