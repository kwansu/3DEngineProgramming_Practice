#pragma once
#include "cObject.h"

class cObject_Pyramid :
	public cObject
{
private:
	vector<Vertex_PN>	m_aVertexPN;
	D3DMATERIAL9		m_mtl;

public:
	cObject_Pyramid(D3DXCOLOR color);
	~cObject_Pyramid();
	void Setup() {}
	void Update();
	void Render();
};

