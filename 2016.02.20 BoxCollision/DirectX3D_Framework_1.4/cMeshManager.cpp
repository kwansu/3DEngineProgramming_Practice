#include "stdafx.h"
#include "cMeshManager.h"


cMeshManager* g_pMeshManager = cMeshManager::GetInstance();

cMeshManager::cMeshManager()
{
}


cMeshManager::~cMeshManager()
{
}

void cMeshManager::Setup()
{
	LPD3DXMESH pMesh = NULL;
	stMeshAttribute	attribute;

	D3DXCreateBox(g_pDevice, 2, 2, 2, &pMesh, NULL);
	attribute.mtl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1);

	m_mappMeshData["Box"] = new cMeshData;
	m_mappMeshData["Box"]->SetMesh(pMesh);
	m_mappMeshData["Box"]->GetAttributeDate().push_back(attribute);
}

void cMeshManager::Release()
{
	for each (auto pData in m_mappMeshData)
	{
		delete pData.second;
	}
}

cMeshData * cMeshManager::CreateMeshData(string strKey)
{
	if (m_mappMeshData.find(strKey) == m_mappMeshData.end())
	{
		assert("cMeshManager->GetMesh : NotFind.");
		return NULL;
	}

	return m_mappMeshData[strKey] = new cMeshData;
}

cMeshData* cMeshManager::GetMeshData(string strMeshName)
{
	if (m_mappMeshData.find(strMeshName) == m_mappMeshData.end())
	{
		assert("cMeshManager->GetMesh : NotFind.");
		return NULL;
	}

	return m_mappMeshData[strMeshName];
}
