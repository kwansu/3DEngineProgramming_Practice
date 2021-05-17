#include "stdafx.h"
#include "cObj_Player.h"


cObj_Player::cObj_Player()
{
}


cObj_Player::~cObj_Player()
{
}

void cObj_Player::Setup()
{
	g_pInput->SetProcessor(this);
	m_mtl.Diffuse = D3DXCOLOR(0.2f, 0.5f, 0.8f, 1);
}

void cObj_Player::Update()
{
	if (g_pInput->IsKeyDown(VK_RETURN))
		g_pInput->SetProcessor(g_pPathManager);

	if (g_pInput->IsKeyDown(VK_SPACE))
		g_pInput->SetProcessor(this);

	cObj_Human::Update();
}

void cObj_Player::InputProcess(iInputProcessor* pGenerator)
{
	if (g_pInput->IsKeyPress(VK_LBUTTON))
	{
		stPlane plane;
		if (g_pCamera->GetMouseRay().IsCollisionAsPlane(&m_vWayPos, plane))
		{
			if (g_pPathManager->CalcShortestPath(m_listPath, m_vPos, m_vWayPos))
			{
				m_vWayPos = m_listPath.front();
				m_vDir = m_vWayPos - m_vPos;
				D3DXVec3Normalize(&m_vDir, &m_vDir);
				m_bMove = true;
			}
			else
			{
				m_listPath.clear();
				m_bMove = false;
			}
			//m_vDir = m_vWayPos - m_vPos;
			//D3DXVec3Normalize(&m_vDir, &m_vDir);
			//m_bMove = true;
		}
	}
}
