#include "stdafx.h"
#include "cObj_Sphere.h"


cObj_Sphere::cObj_Sphere()
{
	D3DXCreateSphere(g_pDevice, 1, 10, 10, &m_pMesh, NULL);

	ZeroMemory(&m_mtl, sizeof(D3DMATERIAL9));
	m_mtl.Diffuse = D3DXCOLOR(0.8f, 0, 0, 1);
	m_mtl.Emissive = D3DXCOLOR(0.2f, 0.1f, 0.1f, 1);
}


cObj_Sphere::~cObj_Sphere()
{
	SafeRelease(m_pMesh);
}

void cObj_Sphere::Update()
{
	UpdateTransform();
}

void cObj_Sphere::Render()
{
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pDevice->SetMaterial(&m_mtl);
	m_pMesh->DrawSubset(0);
}

