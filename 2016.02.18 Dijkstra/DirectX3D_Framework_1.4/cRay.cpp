#include "stdafx.h"
#include "cRay.h"


cRay::cRay()
	: m_vOri(0, 0, 0)
	, m_vDir(0, 0, 1)
{
}

cRay::cRay(D3DXVECTOR3 vOri, D3DXVECTOR3 vDir)
	: m_vOri(vOri)
	, m_vDir(vDir)
{
}


cRay::~cRay()
{
}

void cRay::SetRay(D3DXVECTOR3 vOri, D3DXVECTOR3 vDir)
{
	m_vOri = vOri;
	m_vDir = vDir;
}

bool cRay::IsCollisionSphere(cCollider_Sphere * pColl) const
{
	D3DXVECTOR3 vU = m_vOri - pColl->GetOriginPos();

	float t = D3DXVec3Dot(&vU, &m_vDir);
	float fDistSq = D3DXVec3Dot(&vU, &vU) - t*t;
	float fRadius = pColl->GetRadius();

	if (fDistSq <= fRadius*fRadius)
		return true;

	return false;
}
