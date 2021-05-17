#pragma once
#include "cObject.h"

class cObject_Cube :
	public cObject
{
protected:
	vector<D3DXVECTOR3>	m_aLocalPos;
	vector<Vertex_PC>	m_aVertexPC;
	vector<Vertex_PN>	m_aVertexPN;
	vector<Vertex_PNT>	m_aVertexPNT;
	LPDIRECT3DTEXTURE9	m_pTexture;
	D3DMATERIAL9		m_stMaterial;

public:
	cObject_Cube();
	~cObject_Cube();
	void Setup();
	void Update();
	void Render();
	void SetLocalSize(float sx, float sy, float sz);
};

