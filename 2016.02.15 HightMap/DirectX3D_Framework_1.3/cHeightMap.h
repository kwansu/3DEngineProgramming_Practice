#pragma once
#include "cRawLoader.h"

class cHeightMap
{
private:
	LPD3DXMESH			m_pMesh;
	LPDIRECT3DTEXTURE9	m_pTexture;
	D3DMATERIAL9		m_mtl;
	D3DXMATRIXA16		m_matWorld;

	vector<D3DXVECTOR3>	m_vecPos;
	unsigned			m_uLen;

public:
	cHeightMap();
	~cHeightMap();

	void Setup();
	void Render();
	bool GetHeight(const float x, const float y, OUT float* pfResultY);
};

