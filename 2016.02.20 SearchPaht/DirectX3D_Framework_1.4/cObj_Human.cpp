#include "stdafx.h"
#include "cObj_Human.h"
using namespace ns_OBJ_HUMAN;

cObj_Human::cObj_Human()
	: m_vWayPos(0, 0, 0)
	, m_bMove(false)
{
}


cObj_Human::~cObj_Human()
{
}

void cObj_Human::Update()
{
	if (m_bMove)
		MoveToWayPath();

	UpdateTransform();
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

	m_vPos += m_vDir * fHUMAN_MOVE_SPEED;
}
