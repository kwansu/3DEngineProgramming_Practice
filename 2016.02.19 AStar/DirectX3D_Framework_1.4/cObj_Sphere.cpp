#include "stdafx.h"
#include "cObj_Sphere.h"


cObj_Sphere::cObj_Sphere()
	: m_bDrag(false)
	, m_bCollision(false)
	, m_bMove(false)
{
	D3DXCreateSphere(g_pDevice, 1, 10, 10, &m_pMesh, NULL);
	m_pColl = new cCollider_Sphere;

	ZeroMemory(&m_mtl, sizeof(D3DMATERIAL9));
	m_mtl.Emissive = D3DXCOLOR(1, 0, 0, 1);
}


cObj_Sphere::~cObj_Sphere()
{
	SafeDelete(m_pColl);
}

void cObj_Sphere::Update()
{
	if (g_pInput->IsKeyDown(VK_LBUTTON))
		g_pAStar->CalcPath(m_vPos.x, m_vPos.z, m_listPath);
		
	if (!m_listPath.empty())
	{
		m_vWayPos = m_listPath.front();
		m_vPos += (m_vWayPos - m_vPos) * 0.1;

		float a = D3DXVec3LengthSq(&(m_vWayPos - m_vPos));

		if (a < 1)
		{
			m_listPath.pop_front();
		}
	}

	m_pColl->SetOriginPos(m_vPos);
	UpdateTransform();
}

void cObj_Sphere::Render()
{
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pDevice->SetMaterial(&m_mtl);
	m_pMesh->DrawSubset(0);
}

bool cObj_Sphere::IsCollision(cObj_Sphere * pSphere)
{
	if (m_pColl->IsCollisionAsSphere(pSphere->m_pColl))
	{
		m_bCollision = true;
		pSphere->m_bCollision = true;
		return true;
	}

	m_bCollision = false;
	pSphere->m_bCollision = false;

	return false;
}
