#pragma once
#include "cObj_Human.h"

namespace ns_OBJ_ENEMY
{
	const float ENEMY_ATTACK_RANGE = 100;	//sq·Î °è»ê
}

class cObj_Enemy :
	public cObj_Human
{
private:
	cGameObject*	m_pTarget;

public:
	cObj_Enemy();
	~cObj_Enemy();

	void Update() override;

	void SetTarget(cGameObject* pTarget);

private:
	void MoveEnemy();
};

