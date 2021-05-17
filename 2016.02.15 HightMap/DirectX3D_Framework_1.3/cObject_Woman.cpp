#include "stdafx.h"
#include "cObject_Woman.h"


cObject_Woman::cObject_Woman()
: m_pHeightMap(NULL)
, m_vSpeed(0, 0, 0)
, m_bRun(false)
{
	//m_fAngleX = -90;
	SetScale(2, 2, 2);
	UpdateWorld();

	m_ray.m_vDir = D3DXVECTOR3(0, -1, 0);

	m_pLoader = new ASELoader;
	m_pLoader->LoadASE("./woman/woman_01_all_stand.ASE");
	m_pStandRoot = m_pLoader->m_pRoot;

	m_pLoader2 = new ASELoader;
	m_pLoader2->LoadASE("./woman/woman_01_all.ASE");
	m_pRunRoot = m_pLoader2->m_pRoot;
}


cObject_Woman::~cObject_Woman()
{
	SafeRelease(m_pLoader);
	SafeRelease(m_pLoader2);
}


void cObject_Woman::Setup()
{
}


void cObject_Woman::Update()
{
	UpdateDirection();

	if (!m_bBottom)
		m_vSpeed.y -= 0.025f;

	if (g_pInput->IsKeyPress('W'))
	{
		m_bRun = true;
		m_vSpeed.x = -m_vLook.x * 0.3f;
		m_vSpeed.z = -m_vLook.z * 0.3f;
	}
	else
	{
		m_bRun = false;
		m_vSpeed.x = 0;
		m_vSpeed.z = 0;
	}

	if (g_pInput->IsKeyPress('A'))
		m_fAngleY -= 3;

	if (g_pInput->IsKeyPress('D'))
		m_fAngleY += 3;

	if (g_pInput->IsKeyPress(VK_SPACE) && m_bBottom)
	{
		m_vSpeed.y = 0.5f;
		m_bBottom = false;
	}

	D3DXVECTOR3 vPrePos = m_vPos + m_vSpeed;

	if (m_pHeightMap)
	{
		float tmpY;
		if (m_pHeightMap->GetHeight(vPrePos.x, vPrePos.z, &tmpY))
		{
			if (vPrePos.y <= tmpY)
			{
				vPrePos.y = tmpY;
				m_bBottom = true;
			}

			m_vPos = vPrePos;
		}
		else
		{
			m_vPos.y += m_vSpeed.y;
			m_pHeightMap->GetHeight(m_vPos.x, m_vPos.z, &tmpY);

			if (m_vPos.y <= tmpY)
			{
				m_vPos.y = tmpY;
				m_bBottom = true;
			}
		}
	}

	//if (m_pTerrain)
	//{
	//	float fDist;
	//	m_ray.m_vOri = vPrePos;
	//	m_bBottom = false;

	//	if (m_pTerrain->SearchCollision(&m_ray, &fDist) && fDist < 1)
	//	{
	//		if (fDist > 0)
	//		{
	//			m_bBottom = true;
	//			vPrePos.y += fDist;
	//			m_vSpeed.y = 0;
	//		}

	//		m_vPos = vPrePos;
	//	}
	//	else
	//	{
	//		m_vPos.y += m_vSpeed.y;
	//		m_ray.m_vOri = m_vPos;
	//		m_pTerrain->SearchCollision(&m_ray, &fDist);

	//		if (fDist > 0)
	//		{
	//			m_vPos.y += fDist;
	//			m_bBottom = true;
	//			m_vSpeed.y = 0;
	//		}
	//	}
	//}

	UpdateWorld();
}


void cObject_Woman::Render()
{
	if (m_bRun)
	{
		m_pRunRoot->s_dwTick = (GetTickCount() * 3) % 2560 + 640;
		m_pRunRoot->Render(&m_matWolrd);
	}
	else
	{
		m_pStandRoot->s_dwTick = (GetTickCount() * 3) % 2560 + 640;
		m_pStandRoot->Render(&m_matWolrd);
	}

	m_ray.Render();
}
