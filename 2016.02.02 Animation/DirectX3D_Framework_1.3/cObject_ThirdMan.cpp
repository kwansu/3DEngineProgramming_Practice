#include "stdafx.h"
#include "cObject_ThirdMan.h"


cObject_ThirdMan::cObject_ThirdMan()
{
//	D3DXCreateTeapot(g_pDevice, &m_mesh, NULL);
}


cObject_ThirdMan::~cObject_ThirdMan()
{
//	SafeRelease(m_mesh);
}


void cObject_ThirdMan::Update()
{
	m_tDelta = GetTickCount() - m_tEnd;
	m_tEnd = GetTickCount();
	m_fActionTime += m_tDelta / 1000.f;

	if (m_fActionTime >= ROUND_TIME)
		m_fActionTime = 0;

	D3DXVECTOR3 vBeforePos = m_vPos;

	int wayIndex = m_fActionTime / THIRD_LINE_TIME;
	float ratio = (m_fActionTime - wayIndex * THIRD_LINE_TIME)
		/ THIRD_LINE_TIME;

	D3DXVECTOR3 vStart, vEnd, vDir;
	InterpolationPosition(&vStart, &m_aWayPoint[wayIndex*2]
		, &m_aWayPoint[wayIndex*2 + 1], ratio);
	InterpolationPosition(&vEnd, &m_aWayPoint[wayIndex*2 + 1]
		, &m_aWayPoint[(wayIndex*2 + 2) % 6], ratio);
	InterpolationPosition(&m_vPos, &vStart, &vEnd, ratio);

	vDir = m_vPos - vBeforePos;
	D3DXVec3Normalize(&vDir, &vDir);

	float fCos = D3DXVec3Dot(&vDir, &D3DXVECTOR3(1, 0, 0));
	m_fAngleY = D3DXToDegree(acos(fCos));

	m_fAngleY += 90;

	if (vDir.z > D3DX_16F_EPSILON)
		m_fAngleY *= -1;

	//if (D3DXVec3Cross(&vDir, &vDir, &D3DXVECTOR3(1, 0, 0))->y > 0)
	//	m_fAngleY *= -1;

	cObject_Mario::Update();
}


//void cObject_ThirdMan::Render()
//{
//	cObject_Human::Render();
//
//	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWolrd);
//	g_pDevice->SetFVF(Vertex_PNT::FVF);
//	m_mesh->DrawSubset(0);
//}
