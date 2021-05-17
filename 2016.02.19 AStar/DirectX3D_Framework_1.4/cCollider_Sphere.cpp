#include "stdafx.h"
#include "cCollider_Sphere.h"


cCollider_Sphere::cCollider_Sphere()
	: m_vOri(0, 0, 0)
	, m_fRadius(1)
{
}


cCollider_Sphere::~cCollider_Sphere()
{
}

D3DXVECTOR3 cCollider_Sphere::GetOriginPos() const
{
	return m_vOri;
}

float cCollider_Sphere::GetRadius() const
{
	return m_fRadius;
}

void cCollider_Sphere::SetOriginPos(const D3DXVECTOR3 & vPos)
{
	m_vOri = vPos;
}

void cCollider_Sphere::SetRadius(float fRadius)
{
	m_fRadius = fRadius;
}

bool cCollider_Sphere::IsCollisionAsSphere(cCollider_Sphere * pColl)
{
	D3DXVECTOR3 vDist = m_vOri - pColl->m_vOri;
	float	radiusSum = m_fRadius + pColl->m_fRadius;

	if (D3DXVec3LengthSq(&vDist) <= radiusSum * radiusSum)
		return true;

	return false;
}
