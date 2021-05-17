#include "stdafx.h"
#include "cMeshData.h"


cMeshData::cMeshData()
	: m_pMesh(NULL)
{
}


cMeshData::~cMeshData()
{
	SafeRelease(m_pMesh);
}

void cMeshData::Render()
{
	int size = m_vecAttribute.size();
	for (int i = 0; i < size; ++i)
	{
		g_pDevice->SetTexture(0, m_vecAttribute[i].pTexture);
		g_pDevice->SetMaterial(&m_vecAttribute[i].mtl);

		m_pMesh->DrawSubset(i);
	}
}

void cMeshData::SetMesh(LPD3DXMESH pMesh)
{
	if (m_pMesh)
		assert("cMeshData->SetMesh : mesh != NULL");

	m_pMesh = pMesh;
}

vector<stMeshAttribute>& cMeshData::GetAttributeDate()
{
	return m_vecAttribute;
}
