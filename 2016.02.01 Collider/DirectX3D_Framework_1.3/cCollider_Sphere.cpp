#include "stdafx.h"
#include "cCollider_Sphere.h"


cCollider_Sphere::cCollider_Sphere()
	: m_fRadius(1.0f)
	, m_vOrigin(0, 0, 0)
{
	D3DXCreateSphere(g_pDevice, m_fRadius, 8, 8, &m_pMesh, NULL);
}


cCollider_Sphere::~cCollider_Sphere()
{
	SafeRelease(m_pMesh);
}


void cCollider_Sphere::Update()
{
	if (g_pInput->IsKeyPress(VK_LBUTTON))
	{
	}
}


void cCollider_Sphere::Render()
{
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pMesh->DrawSubset(0);
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}
