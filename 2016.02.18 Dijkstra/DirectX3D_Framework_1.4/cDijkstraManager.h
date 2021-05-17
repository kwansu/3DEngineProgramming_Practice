#pragma once
#include "DijLoader.h"

class cDijkstraManager
{
private:
	vector<stVertex_PC>	m_vecVertexEdge;
	vector<DijNode>		m_vecDijNode;
	float**				m_arrEdgeCost;
	LPD3DXMESH			m_pMesh;

	DijNode*			m_pRoot;
	DijNode*			m_pTarget;

public:
	cDijkstraManager();
	~cDijkstraManager();

	void Setup();
	void Render();
	void ProcessMouseClicked(bool bR);

private:
	void ProcessPath();
	void CalcDijkstra();
};

