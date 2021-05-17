#include "stdafx.h"
#include "cMeshManager.h"


cMeshManager* g_pMeshManager = cMeshManager::GetInstance();

cMeshManager::cMeshManager()
{
}


cMeshManager::~cMeshManager()
{
}

void cMeshManager::Release()
{
	m_mapMeshData.clear();
}

bool cMeshManager::AddMesh(string strKey, cMeshData pMeshData)
{
	if (m_mapMeshData.find(strKey) != m_mapMeshData.end())
	{
		return false;
	}

	m_mapMeshData.insert(pair<string, cMeshData>(strKey, pMeshData));

	return true;
}

cMeshData* cMeshManager::GetMesh(string strMeshName)
{
	if (m_mapMeshData.find(strMeshName) == m_mapMeshData.end())
	{
		assert("cMeshManager->GetMesh : NotFind.");
		return NULL;
	}

	return &m_mapMeshData[strMeshName];
}
