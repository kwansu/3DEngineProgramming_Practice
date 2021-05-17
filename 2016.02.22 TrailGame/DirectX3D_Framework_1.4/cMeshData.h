#pragma once

struct stMeshAttribute
{
	LPDIRECT3DTEXTURE9	pTexture;
	D3DMATERIAL9		mtl;

	stMeshAttribute() : pTexture(NULL) { ZeroMemory(&mtl, sizeof(D3DMATERIAL9)); }
};

class cMeshManager;

class cMeshData
{
	friend class cMeshManager;

private:
	LPD3DXMESH				m_pMesh;
	vector<stMeshAttribute>	m_vecAttribute;
	
private:
	cMeshData();
	void Release();

public:
	~cMeshData();
	void SetMesh(LPD3DXMESH pMesh);
	void Render();
	vector<stMeshAttribute>& GetAttributeDate();
};

