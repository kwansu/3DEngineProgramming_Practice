#include "stdafx.h"
#include "cObj_Enemy.h"
using namespace ns_OBJ_ENEMY;


cObj_Enemy::cObj_Enemy()
	: m_pTarget(NULL)
{
	m_fMoveSpeed = 0.1f;
}


cObj_Enemy::~cObj_Enemy()
{
}

void cObj_Enemy::Update()
{
	if (m_pTarget)
	{
		if (m_listPath.empty())
		{
			if (D3DXVec3LengthSq(&(m_pTarget->GetPosition() - m_vPos)) < ENEMY_ATTACK_RANGE)
			{
				if (m_bAttack)
				{
					m_mtl.Diffuse = D3DXCOLOR(1, 0, 0, 1);
				}
				else
					m_bAttack = true;

				m_bMove = false;
			}
			else
			{
				m_mtl.Diffuse = D3DXCOLOR(0, 1, 0, 1);
				m_bAttack = false;
				MoveEnemy();
			}
		}
		else
		{
			MoveEnemy();
		}
	}
}

void cObj_Enemy::SetTarget(cGameObject * pTarget)
{
	m_pTarget = pTarget;
}

void cObj_Enemy::MoveEnemy()
{
	if (g_pPathManager->CalcShortestPath(m_listPath, m_vPos, m_pTarget->GetPosition()))
	{
		m_vDir = m_listPath.front() - m_vPos;
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		m_listPath.pop_front();

		m_bMove = true;
	}

	cObj_Human::Update();
}
