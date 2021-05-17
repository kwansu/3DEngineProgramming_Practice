#pragma once
#include "cObj_Human.h"

namespace ns_OBJ_ENEMY
{
	const float ENEMY_ATTACK_RANGE = 225;	//sq·Î °è»ê
}

class cObj_Enemy :
	public cObj_Human
{
private:
	cObj_Human*		m_pTarget;
	int				m_nCount;

public:
	cObj_Enemy();
	~cObj_Enemy();

	void Update() override;

	void SetTarget(cObj_Human* pTarget);

private:
	void EnemyMisileShoot();
};

