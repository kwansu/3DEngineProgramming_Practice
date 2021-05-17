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
	cRay rayMouse = g_pCamera->GetMouseRay();

	if (m_bMove)
	{
		m_vPos += m_vDir * 0.1f;

		if (D3DXVec3LengthSq(&(m_vWayPos - m_vPos)) < 0.2f)
			m_bMove = false;
	}

	if (rayMouse.IsCollisionSphere(m_pColl))
	{
		if (g_pInput->IsKeyDown(VK_LBUTTON))
		{
			m_bDrag = !m_bDrag;

			float ratio = -rayMouse.m_vOri.y / rayMouse.m_vDir.y;
			m_vOffset = m_vPos - (rayMouse.m_vOri + ratio * rayMouse.m_vDir);
		}
	}
	else
	{
		if (m_bDrag && g_pInput->IsKeyDown(VK_LBUTTON))
		{
			float ratio = -rayMouse.m_vOri.y / rayMouse.m_vDir.y;
			m_vWayPos = (rayMouse.m_vOri + ratio * rayMouse.m_vDir);
			m_vDir = m_vWayPos - m_vPos;
			D3DXVec3Normalize(&m_vDir, &m_vDir);
			m_bMove = true;
		}
	}

	if(m_bDrag)
		m_mtl.Emissive = D3DXCOLOR(0, 0, 1, 1);
	else if (m_bCollision)
		m_mtl.Emissive = D3DXCOLOR(0, 1, 0, 1);
	else
		m_mtl.Emissive = D3DXCOLOR(1, 0, 0, 1);

	//if (g_pInput->IsKeyUp(VK_LBUTTON))
	//	m_bDrag = false;

	//if (g_pInput->IsKeyPress(VK_LBUTTON) && m_bDrag)
	//{
	//	m_mtl.Emissive = D3DXCOLOR(0, 0, 1, 1);

	//	float ratio = -rayMouse.m_vOri.y / rayMouse.m_vDir.y;

	//	m_vPos = rayMouse.m_vOri + ratio * rayMouse.m_vDir + m_vOffset;
	//}

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
