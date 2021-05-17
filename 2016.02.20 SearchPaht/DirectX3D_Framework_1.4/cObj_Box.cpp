#include "stdafx.h"
#include "cObj_Box.h"


cObj_Box::cObj_Box()
{
}


cObj_Box::~cObj_Box()
{
	SafeDelete(m_pCollBox);
	SafeDelete(m_pMeshData);
}

void cObj_Box::Setup()
{
	m_pMeshData = g_pMeshManager->GetMeshData("Box");
	
	m_pCollBox = new cCollider_Box;
}

void cObj_Box::Update()
{
	cObj_Mesh::Update();

	D3DXMATRIXA16 matInverse;
	D3DXMatrixTranslation(&matInverse, -m_vPos.x, -m_vPos.y, -m_vPos.z);

	if (m_pCollBox->IsCollisionAsRay(g_pCamera->GetMouseRay(), &matInverse))
	{
		m_pMeshData->GetAttributeDate()[0].mtl.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else
	{
		m_pMeshData->GetAttributeDate()[0].mtl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	}
}
