#pragma once
#include "stdGameObjects.h"

class cGameObjectManager
{
	SINGLETONE(cGameObjectManager);

private:
	D3DLIGHT9				m_light;
	cGrid*					m_pGrid;

	vector<cGameObject*>	m_vecpGameObjects;

public:
	void Setup();
	void Release();
	void Update();
	void Render();
};


extern cGameObjectManager*	g_pGameObjects;
