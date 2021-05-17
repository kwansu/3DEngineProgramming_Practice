#pragma once
#include "cRay.h"

class cTerrain
{
private:
	vector<Vertex_PN>	m_aVertexPN;
	D3DMATERIAL9		m_mtl;
	D3DXMATRIXA16		m_matScale;

public:
	cTerrain();
	~cTerrain();
	void Render();
	bool SearchCollision(cRay* pray, OUT float* fDist);
};

