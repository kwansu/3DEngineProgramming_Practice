#include "stdafx.h"
#include "cObj_Human.h"
using namespace ns_OBJ_HUMAN;

cObj_Human::cObj_Human()
	: m_vWayPos(0, 0, 0)
	, m_bMove(false)
	, m_bAttack(false)
	, m_fMoveSpeed(0.2f)
	, m_fHitPoint(100)
{
}


cObj_Human::~cObj_Human()
{
}

void cObj_Human::Update()
{
	if (m_bMove)
		MoveToWayPath();

	if (m_fHitPoint <= 0)
		g_pGameObjects->MessageHandler(this, DEAD);

	UpdateTransform();
}

void cObj_Human::AddHitPoint(float fDelta)
{
	m_fHitPoint += fDelta;
}

void cObj_Human::MoveToWayPath()
{
	if (D3DXVec3LengthSq(&(m_vPos - m_vWayPos)) < fHUMAN_STOP_RADIUS)
	{
		if (m_listPath.empty())
		{
			m_bMove = false;
			return;
		}

		m_vWayPos = m_listPath.front();
		m_listPath.pop_front();
		m_vDir = m_vWayPos - m_vPos;
		D3DXVec3Normalize(&m_vDir, &m_vDir);
	}

	m_vPos += m_vDir * m_fMoveSpeed;
}

void cObj_Human::FindPath(const D3DXVECTOR3 & vDestination)
{
	if (g_pPathManager->CalcShortestPath(m_listPath, m_vPos, vDestination))
	{
		m_vWayPos = m_listPath.front();
		m_vDir = m_vWayPos - m_vPos;
		m_listPath.pop_front();
		D3DXVec3Normalize(&m_vDir, &m_vDir);

		m_bMove = true;
	}
	else
		m_bMove = false;
}

bool cObj_Human::IsCollisionAsRay(cRay * pray)
{
	D3DXMATRIXA16 matInverse;
	D3DXMatrixTranslation(&matInverse, -m_vPos.x, -m_vPos.y, -m_vPos.z);
	if (cCollider_Sphere::IsCollisionAsRay(*pray, &matInverse))
		return true;

	return false;
}
