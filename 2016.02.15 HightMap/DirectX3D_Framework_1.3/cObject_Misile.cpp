#include "stdafx.h"
#include "cObject_Misile.h"


cObject_Misile::cObject_Misile()
	: m_vVelocity(0, 0, 0)
	, m_vAcceleration(0, 0, 0)
{
}


cObject_Misile::~cObject_Misile()
{
	SafeRelease(m_pMesh);
}

void cObject_Misile::Setup()
{
	m_fInverseMass = 1 / 10.f;

	D3DXCreateSphere(g_pDevice, 1, 12, 12, &m_pMesh, NULL);
}

void cObject_Misile::Update()
{
	m_vAcceleration = D3DXVECTOR3(0, 0, 0);
	for each(auto vPower in m_avPowerAccount)
	{
		m_vAcceleration += vPower;
	}
	m_vAcceleration *= m_fInverseMass;

	m_vVelocity += m_vAcceleration;

	m_vPos += m_vVelocity;
}

void cObject_Misile::Render()
{
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWolrd);
	
	m_pMesh->DrawSubset(0);
}
