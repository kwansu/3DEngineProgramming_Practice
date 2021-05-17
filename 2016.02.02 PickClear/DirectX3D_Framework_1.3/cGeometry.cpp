#include "stdafx.h"
#include "cGeometry.h"


cGeometry::cGeometry()
	: m_pParent(NULL)
	, m_pTexture(NULL)
{
	ZeroMemory(&m_mtl, sizeof(D3DMATERIAL9));
	D3DXMatrixIdentity(&m_matLocal);
	D3DXMatrixIdentity(&m_matWorld);
}


cGeometry::~cGeometry()
{
}

void cGeometry::Update()
{
}


void cGeometry::Render(D3DXMATRIXA16* pmatParent)
{
	m_matWorld = m_matLocal * *pmatParent;

	if (m_pTexture)
	{
		g_pDevice->SetRenderState(D3DRS_LIGHTING, true);

		g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		//g_pDevice->SetTexture(0, m_pTexture);
		g_pDevice->SetTexture(0, NULL);
		g_pDevice->SetMaterial(&m_mtl);
		g_pDevice->SetFVF(Vertex_PNT::FVF);

		g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST
			, m_aVertex.size() / 3
			, &m_aVertex[0]
			, sizeof(Vertex_PNT));
	}

	for (int i = 0; i < m_apChild.size(); ++i)
		m_apChild[i]->Render(&m_matWorld);
}
