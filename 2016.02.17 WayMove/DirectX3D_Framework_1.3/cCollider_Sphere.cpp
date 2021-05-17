#include "stdafx.h"
#include "cCollider_Sphere.h"


cCollider_Sphere::cCollider_Sphere()
	: m_fRadius(5)
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
}


void cCollider_Sphere::Render()
{
	//g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	g_pDevice->SetTexture(0, NULL);
	m_pMesh->DrawSubset(0);
	//g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}


bool cCollider_Sphere::IsCollisionSphere(cCollider_Sphere* pColl)
{
	D3DXVECTOR3 vDist = m_vOrigin - pColl->m_vOrigin;
	float radiusSum = m_fRadius + pColl->m_fRadius;

	if (D3DXVec3LengthSq(&vDist) <= radiusSum * radiusSum)
		return true;

	return false;
}
