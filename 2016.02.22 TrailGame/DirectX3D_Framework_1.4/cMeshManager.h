#pragma once
#include "cMeshData.h"

class cMeshManager
{
	SINGLETONE(cMeshManager);

private:
	map<string, cMeshData*>	m_mappMeshData;

public:
	void Setup();
	void Release();

	cMeshData* CreateMeshData(string strKey);
	cMeshData* GetMeshData(string strMeshName);
};

extern cMeshManager* g_pMeshManager;
