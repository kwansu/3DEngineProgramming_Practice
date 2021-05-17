#include "stdafx.h"
#include "cGrid.h"


cGrid::cGrid()
	: m_nLine(50)
{
	D3DXMatrixIdentity(&m_matInterval);
}


cGrid::~cGrid()
{
}


void cGrid::Setup()
{
	if (!m_aVertex.empty())
		m_aVertex.clear();

	for (int i = -m_nLine; i <= m_nLine; ++i)
	{
		D3DCOLOR color = (i % 5) ? D3DCOLOR_XRGB(128, 128, 128)
			: D3DCOLOR_XRGB(255, 255, 255);

		m_aVertex.push_back(Vertex_PC(D3DXVECTOR3(i, 0, m_nLine), color));
		m_aVertex.push_back(Vertex_PC(D3DXVECTOR3(i, 0, -m_nLine), color));
		m_aVertex.push_back(Vertex_PC(D3DXVECTOR3(m_nLine, 0, i), color));
		m_aVertex.push_back(Vertex_PC(D3DXVECTOR3(-m_nLine, 0, i), color));
	}
}


void cGrid::Render()
{
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pDevice->SetTexture(0, NULL);
	g_pDevice->SetFVF(Vertex_PC::FVF);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matInterval);

	g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST
		, m_aVertex.size() / 2, &m_aVertex[0], sizeof(Vertex_PC));
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
}


// 격자 사이 간격
void cGrid::SetInterval(float fInterval)
{
	D3DXMatrixScaling(&m_matInterval, fInterval, fInterval, fInterval);
}
