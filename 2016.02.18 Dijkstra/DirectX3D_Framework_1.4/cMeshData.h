#pragma once

struct stMeshAttribute
{
	LPDIRECT3DTEXTURE9	pTexture;
	D3DMATERIAL9		mtl;

	stMeshAttribute() : pTexture(NULL) { ZeroMemory(&mtl, sizeof(D3DMATERIAL9)); }
};


class cMeshData
{
private:
	LPD3DXMESH				m_pMesh;
	vector<stMeshAttribute>	m_vecAttribute;
	
public:
	cMeshData();
	~cMeshData();

	void Render();
	void SetMesh(LPD3DXMESH pMesh);
	vector<stMeshAttribute>& GetAttributeDate();
};

