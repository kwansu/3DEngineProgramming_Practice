#pragma once
#include "cMesh.h"
#include "cCollider_Terrain.h"

#define g_pResourceManager	cResourceManager::GetInstance()

class cResourceManager
{
	SINGLETONE(cResourceManager);

private:
	map<string, cMesh>					m_mapMeshData;
	map<string, MtlTexture>				m_mapMtlTexData;
	map<string, LPDIRECT3DTEXTURE9>		m_mapTexture;

	vector<D3DXVECTOR3>					m_aVertex;

	LPD3DXMESH							m_pMesh;
	int									m_nVertices;

private:
	bool LoadMtlFile(char* sFileName);

public:
	bool LoadObjFile(char* sFileName, bool isMesh);
	bool GetMesh(OUT cMesh* &pMesh, string name);
	void Destroy();
};

