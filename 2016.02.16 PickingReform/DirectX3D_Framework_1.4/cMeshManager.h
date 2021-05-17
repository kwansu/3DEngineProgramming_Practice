#pragma once
#include "cMeshData.h"

class cMeshManager
{
	SINGLETONE(cMeshManager);

private:
	map<string, cMeshData>	m_mapMeshData;

public:
	void Release();

	bool AddMesh(string strKey, cMeshData pMeshData);
	cMeshData* GetMesh(string strMeshName);
};

extern cMeshManager* g_pMeshManager;
