#include "stdafx.h"
#include "cObject_SixMan.h"


cObject_SixMan::cObject_SixMan()
{
}


cObject_SixMan::~cObject_SixMan()
{
}


void cObject_SixMan::Update()
{
	m_tDelta = GetTickCount() - m_tEnd;
	m_tEnd = GetTickCount();
	m_fActionTime += m_tDelta / 1000.f;

	if (m_fActionTime >= ROUND_TIME)
		m_fActionTime = 0;

	D3DXVECTOR3 vBeforePos = m_vPos;

	int wayIndex = m_fActionTime / SIX_LINE_TIME;
	float ratio = (m_fActionTime - wayIndex * SIX_LINE_TIME)
		/ SIX_LINE_TIME;

	InterpolationPosition(&m_vPos, &m_aWayPoint[wayIndex]
		, &m_aWayPoint[(wayIndex+1)%6], ratio);

	D3DXVECTOR3 vDir = m_vPos - vBeforePos;
	D3DXVec3Normalize(&vDir, &vDir);

	float fCos = D3DXVec3Dot(&vDir, &D3DXVECTOR3(1, 0, 0));
	m_fAngleY = D3DXToDegree(acos(fCos));

	m_fAngleY += 90;

	if (vDir.z > D3DX_16F_EPSILON)
		m_fAngleY *= -1;

	/*if (D3DXVec3Cross(&vDir, &vDir, &D3DXVECTOR3(1, 0, 0))->y > 0)
		m_fAngleY *= -1;*/

	cObject_Mario::Update();
}


//void cObject_SixMan::Render()
//{
//	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWolrd);
//	g_pDevice->SetFVF(Vertex_PNT::FVF);
//}
