#include "stdafx.h"
#include "cTerrain.h"


cTerrain::cTerrain()
{
	ZeroMemory(&m_mtl, sizeof(D3DMATERIAL9));
	m_mtl.Ambient = D3DXCOLOR(0.8f, 0.82f, 0.78f, 1.0f);

	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3( 1, 1, 1), D3DXVECTOR3(0, 1, 0)));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3( 1, 1,-1), D3DXVECTOR3(0, 1, 0)));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(-1, 1, 1), D3DXVECTOR3(0, 1, 0)));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(-1, 1, 1), D3DXVECTOR3(0, 1, 0)));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3( 1, 1,-1), D3DXVECTOR3(0, 1, 0)));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(-1, 1,-1), D3DXVECTOR3(0, 1, 0)));

	D3DXMatrixScaling(&m_matScale, 100, 1, 100);
}


cTerrain::~cTerrain()
{
}


void cTerrain::Render()
{
	g_pDevice->SetMaterial(&m_mtl);
	g_pDevice->SetTexture(0, NULL);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matScale);
	g_pDevice->SetFVF(Vertex_PN::FVF);
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST
		, m_aVertexPN.size() / 3
		, &m_aVertexPN[0]
		, sizeof(Vertex_PN));
}


bool cTerrain::SearchCollision(IN OUT cRay* pray, OUT float* fDist)
{
	pray->m_vOri.y += 1000;

	D3DXVECTOR3 vOri;
	D3DXMATRIXA16 matIn;

	D3DXMatrixInverse(&matIn, NULL, &m_matScale);
	D3DXVec3TransformCoord(&vOri, &pray->m_vOri, &matIn);

	for (int i = 0; i < m_aVertexPN.size(); i += 3)
	{
		if (D3DXIntersectTri(&m_aVertexPN[i].p, &m_aVertexPN[i + 1].p
			, &m_aVertexPN[i + 2].p, &vOri, &pray->m_vDir, NULL, NULL, fDist))
		{
			*fDist -= 1000;
			*fDist *= -1;
			return true;
		}
	}

	return false;
}
