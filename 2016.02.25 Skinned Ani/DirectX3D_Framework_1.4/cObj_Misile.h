#pragma once
#include "cObj_Sphere.h"
#include "cObj_Human.h"

namespace ns_MISILE
{
	const float MISILE_SPEED = 0.6f;
}

class cObj_Misile :
	public cObj_Sphere
{
private:
	bool		m_isMove;
	float		m_fDamage;
	cObj_Human*	m_pTarget;

public:
	cObj_Misile();
	~cObj_Misile();

	void Setup(cObj_Human* pTarget, const D3DXVECTOR3& vPos, const D3DXVECTOR3& vDir, float fDamage = 10);
	void Update() override;
};

