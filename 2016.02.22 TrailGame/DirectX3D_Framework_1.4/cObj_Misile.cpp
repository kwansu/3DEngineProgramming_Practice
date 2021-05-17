#include "stdafx.h"
#include "cObj_Misile.h"


cObj_Misile::cObj_Misile()
	: m_pTarget(NULL)
	, m_fDamage(10)
	, m_isMove(false)
{
}


cObj_Misile::~cObj_Misile()
{
}

void cObj_Misile::Setup(cObj_Human * pTarget, const D3DXVECTOR3 & vPos, const D3DXVECTOR3 & vDir, float fDamage)
{
	m_pTarget = pTarget;
	m_vPos = vPos;
	m_vDir = vDir;
	m_fDamage = fDamage;

	SetScale(0.2f, 0.2f, 0.7f);
	UpdateScaling();

	D3DXMatrixLookAtLH(&m_matR, &D3DXVECTOR3(0, 0, 0), &m_vDir, &D3DXVECTOR3(0, 1, 0));
	D3DXMatrixTranspose(&m_matR, &m_matR);

	m_isMove = true;
}

void cObj_Misile::Update()
{
	if (m_isActive)
	{
		if (cCollider_Sphere::IsCollisionAsSphere(m_vPos, 0.6f, m_pTarget->GetPosition(), 1))
		{
			m_pTarget->AddHitPoint(-m_fDamage);
			m_isActive = false;
		}

		if (m_isMove)
		{
			m_vPos += m_vDir * ns_MISILE::MISILE_SPEED;
		}
	}

	UpdateTranslation();
	m_matWorld = m_matS * m_matR * m_matT;
}

