#include "stdafx.h"
#include "cObj_Enemy.h"
#include "cObj_Misile.h"
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
		FindPath(m_pTarget->GetPosition());

		if (m_listPath.empty())
		{
			if (D3DXVec3LengthSq(&(m_vWayPos - m_vPos)) < ENEMY_ATTACK_RANGE)
			{
				m_bMove = false;
				m_bAttack = true;
			}
		}
		else
		{
			m_bAttack = false;
			m_bMove = true;
		}

		if (m_bAttack)
		{
			EnemyMisileShoot();
			float color = m_nCount * 0.01f;
			m_mtl.Diffuse = D3DXCOLOR(color, 1 - color, 0, 1);
		}
		else
		{
			m_mtl.Diffuse = D3DXCOLOR(0, 1, 0, 1);
		}
	}

	cObj_Human::Update();
}

void cObj_Enemy::SetTarget(cObj_Human * pTarget)
{
	m_pTarget = pTarget;
}

void cObj_Enemy::EnemyMisileShoot()
{
	++m_nCount;

	if (m_nCount > 100)
	{
		m_nCount = 0;

		cObj_Misile* pMisile = new cObj_Misile;
		pMisile->Setup(m_pTarget, m_vPos, m_vDir);

		g_pGameObjects->MessageHandler(pMisile, SHOOT);
	}
}

