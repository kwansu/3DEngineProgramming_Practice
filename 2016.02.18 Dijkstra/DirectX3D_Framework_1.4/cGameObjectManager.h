#pragma once
#include "stdGameObjects.h"
#include "cDijkstraManager.h"

class cGameObjectManager
{
	SINGLETONE(cGameObjectManager);

private:
	cGrid*	m_pGrid;

	cDijkstraManager	a;
	LPD3DXMESH			m_pMesh;
	DijNode*			m_pPicked;
	vector<DijNode>		m_vecNode;
	vector<stVertex_PC>	m_vecEdge;

	vector<cGameObject*>	m_vecpGameObjects;

	D3DLIGHT9				m_light;

public:
	void Setup();
	void Relese();
	void Update();
	void Render();

	void ProcessClick();
};


extern cGameObjectManager*	g_pGameObjects;
