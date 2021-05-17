#pragma once
class cTerrain
{
private:
	vector<Vertex_PN>	m_aVerexPN;
	D3DMATERIAL9		m_mtl;
	D3DXMATRIXA16		m_matScale;

public:
	cTerrain();
	~cTerrain();
	void Render();
};

