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

	cMeshData* pData;
	pData = new cMeshData;
	pData->SetMesh(pMesh);
	pData->GetAttributeDate().push_back(attribute);
	m_mappMeshData["Box"] = pData;

	D3DXCreateSphere(g_pDevice, 1, 10, 10, &pMesh, NULL);
	attribute.mtl.Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.4f, 1);

	pData = new cMeshData;
	pData->SetMesh(pMesh);
	pData->GetAttributeDate().push_back(attribute);
	m_mappMeshData["Sphere"] = pData;
}

void cMeshManager::Release()
{
	for each (auto pData in m_mappMeshData)
	{
		pData.second->Release();
		SafeDelete(pData.second);
	}
}

cMeshData * cMeshManager::CreateMeshData(string strKey)
{
	if (m_mappMeshData.find(strKey) != m_mappMeshData.end())
	{
		assert(false, "cMeshManager->GetMesh : SameName");
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

	cMeshData* copy = m_mappMeshData[strMeshName];

	cMeshData* result = new cMeshData;
	result->m_pMesh = copy->m_pMesh;
	for each(auto p in copy->m_vecAttribute)
	{
		result->m_vecAttribute.push_back(p);
	}

	return result;
}
