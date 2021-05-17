#include "stdafx.h"
#include "cObject_MouseMark.h"


cObject_MouseMark::cObject_MouseMark()
{
	D3DXCreateSphere(g_pDevice, 3, 2, 8, &m_pMesh, NULL);
	
	ZeroMemory(&m_mtl, sizeof(D3DMATERIAL9));
	m_mtl.Emissive = D3DXCOLOR(0, 1.0f, 0, 1.0f);

	D3DXMatrixRotationZ(&m_matRot, D3DXToRadian(90));
}


cObject_MouseMark::~cObject_MouseMark()
{
	SafeRelease(m_pMesh);
}


void cObject_MouseMark::Setup()
{
}


void cObject_MouseMark::Update()
{
}


void cObject_MouseMark::Render()
{
	g_pDevice->SetMaterial(&m_mtl);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWolrd);
	m_pMesh->DrawSubset(0);
}


void cObject_MouseMark::SetMark(const D3DXVECTOR3* pvDir, const D3DXVECTOR3* pvPos)
{
	float ratio = -pvPos->y / pvDir->y;

	m_vPos = *pvPos + ratio * *pvDir;
	UpdateTranslation();

	m_matWolrd = m_matRot * m_matTrl;
}
