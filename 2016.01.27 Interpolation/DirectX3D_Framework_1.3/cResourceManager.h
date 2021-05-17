#pragma once
#include "cMesh.h"
#include "cCollider.h"

#define g_pResourceManager	cResourceManager::GetInstance()

class cResourceManager
{
	SINGLETONE(cResourceManager);

private:
	map<string, cMesh>					m_mapMeshData;
	map<string, cCollider>				m_mapColliderData;
	map<string, MtlTexture>				m_mapMtlTexData;
	map<string, LPDIRECT3DTEXTURE9>		m_mapTexture;


private:
	bool LoadMtlFile(char* sFileName);

public:
	bool LoadObjFile(char* sFileName, bool isMesh);
	bool GetMesh(OUT cMesh* &pMesh, string name);
	bool GetCollider(OUT cCollider* pColl, string name);
	void Destroy();
};

