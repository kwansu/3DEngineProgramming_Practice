#include "stdafx.h"
#include "cObj_Mesh.h"


cObj_Mesh::cObj_Mesh()
	: m_pMeshData(NULL)
{
}


cObj_Mesh::~cObj_Mesh()
{
}

void cObj_Mesh::Update()
{
	UpdateTransform();
}

void cObj_Mesh::Render()
{
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pMeshData->Render();
}
