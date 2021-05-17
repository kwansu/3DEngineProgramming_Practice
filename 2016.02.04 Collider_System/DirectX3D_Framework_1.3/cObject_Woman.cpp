#include "stdafx.h"
#include "cObject_Woman.h"


cObject_Woman::cObject_Woman()
: m_pTerrain(NULL)
, m_vSpeed(0, 0, 0)
{
	//m_fAngleX = -90;
	SetScale(5, 5, 5);
	UpdateWorld();

	m_ray.m_vDir = D3DXVECTOR3(0, -1, 0);
}


cObject_Woman::~cObject_Woman()
{
}


void cObject_Woman::Setup()
{
}


void cObject_Woman::Update()
{
	UpdateDirection();

	if (!m_bBottom)
		m_vSpeed.y -= 0.1f;

	if (g_pInput->IsKeyPress('W'))
	{
		m_vSpeed.x = -m_vLook.x * 0.5f;
		m_vSpeed.z = -m_vLook.z * 0.5f;
	}
	else
	{
		m_vSpeed.x = 0;
		m_vSpeed.z = 0;
	}

	if (g_pInput->IsKeyPress('A'))
		m_fAngleY -= 3;

	if (g_pInput->IsKeyPress('D'))
		m_fAngleY += 3;

	D3DXVECTOR3 vPrePos = m_vPos + m_vSpeed;

	if (m_pTerrain)
	{
		float fDist;
		m_ray.m_vOri = vPrePos;

		if (m_pTerrain->SearchCollision(&m_ray, &fDist))
		{
			if (fDist > 0)
			{
				m_bBottom = true;
				vPrePos.y += fDist;
				m_vSpeed.y = 0;
			}

			m_vPos = vPrePos;
		}
	}

	UpdateWorld();
}


void cObject_Woman::Render()
{
	m_pRoot->s_dwTick = (GetTickCount()*3) % 2560 + 640;
	m_pRoot->Render(&m_matWolrd);

	m_ray.Render();
}
