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

bool cRay::IsCollisionAsPlane(OUT D3DXVECTOR3 * pvPos, const stPlane & plane) const
{
	float t = D3DXVec3Dot(&m_vDir, &plane.vNormal);

	if (IsEqual(t, 0))
		return false;

	t = D3DXVec3Dot(&(plane.vAnyPos - m_vOri), &plane.vNormal) / t;

	if (t < EPSILON)
		return false;

	if (pvPos)
		*pvPos = m_vOri + t * m_vDir;

	return true;
}

void cRay::DebugRender()
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
