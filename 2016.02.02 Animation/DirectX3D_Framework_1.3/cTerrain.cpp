#include "stdafx.h"
#include "cTerrain.h"


cTerrain::cTerrain()
{
	D3DXVECTOR3 vNormal(0, 1, 0);
	m_aVerexPN.push_back(Vertex_PN(D3DXVECTOR3(1, -0.1f, 1), vNormal));
	m_aVerexPN.push_back(Vertex_PN(D3DXVECTOR3(1, -0.1f, -1), vNormal));
	m_aVerexPN.push_back(Vertex_PN(D3DXVECTOR3(-1, -0.1f, 1), vNormal));
	m_aVerexPN.push_back(Vertex_PN(D3DXVECTOR3(1, -0.1f, -1), vNormal));
	m_aVerexPN.push_back(Vertex_PN(D3DXVECTOR3(-1, -0.1f, -1), vNormal));
	m_aVerexPN.push_back(Vertex_PN(D3DXVECTOR3(-1, -0.1f, 1), vNormal));
	
	ZeroMemory(&m_mtl, sizeof(D3DMATERIAL9));
	/*m_mtl.Diffuse = */m_mtl.Emissive = D3DXCOLOR(0.75f, 0.8f, 0.7f, 1.0f);

	D3DXMatrixScaling(&m_matScale, 100, 0, 100);
}


cTerrain::~cTerrain()
{
}


void cTerrain::Render()
{
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matScale);
	g_pDevice->SetTexture(0, NULL);
	g_pDevice->SetMaterial(&m_mtl);
	g_pDevice->SetFVF(Vertex_PN::FVF);
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST
		, m_aVerexPN.size() / 3
		, &m_aVerexPN[0]
		, sizeof(Vertex_PN));
}
