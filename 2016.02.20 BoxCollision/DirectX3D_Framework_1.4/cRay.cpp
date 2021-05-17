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

void cRay::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	D3DXVECTOR3 vPos[2];
	vPos[0] = m_vOri;
	vPos[1] = m_vOri + m_vDir * 100.0f;

	g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST,
		1,
		vPos,
		sizeof(D3DXVECTOR3));
}

void cRay::SetRay(const D3DXVECTOR3 & vOri, const D3DXVECTOR3 & vDir)
{
	m_vOri = vOri;
	m_vDir = vDir;
}

void cRay::Transform(const D3DXMATRIXA16 * pmatWorld)
{
	D3DXVec3TransformCoord(&m_vOri, &m_vOri, pmatWorld);
	D3DXVec3TransformNormal(&m_vDir, &m_vDir, pmatWorld);
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
