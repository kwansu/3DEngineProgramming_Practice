#include "stdafx.h"
#include "cObject_Pyramid.h"


cObject_Pyramid::cObject_Pyramid(D3DXCOLOR color)
{
	ZeroMemory(&m_mtl, sizeof(D3DMATERIAL9));
	m_mtl.Emissive = color;

	D3DXVECTOR3 n(0, 0, 0);
	D3DXVECTOR3 p;
	p = D3DXVECTOR3(0, 0, 0); m_aVertexPN.push_back(Vertex_PN(p, n));
	p = D3DXVECTOR3(1, 1, -1); m_aVertexPN.push_back(Vertex_PN(p, n));
	p = D3DXVECTOR3(-1, 1, -1); m_aVertexPN.push_back(Vertex_PN(p, n));

	p = D3DXVECTOR3(0, 0, 0); m_aVertexPN.push_back(Vertex_PN(p, n));
	p = D3DXVECTOR3(1, 1, 1); m_aVertexPN.push_back(Vertex_PN(p, n));
	p = D3DXVECTOR3(1, 1, -1); m_aVertexPN.push_back(Vertex_PN(p, n));

	p = D3DXVECTOR3(0, 0, 0); m_aVertexPN.push_back(Vertex_PN(p, n));
	p = D3DXVECTOR3(-1, 1, 1); m_aVertexPN.push_back(Vertex_PN(p, n));
	p = D3DXVECTOR3(1, 1, 1); m_aVertexPN.push_back(Vertex_PN(p, n));

	p = D3DXVECTOR3(0, 0, 0); m_aVertexPN.push_back(Vertex_PN(p, n));
	p = D3DXVECTOR3(-1, 1, -1); m_aVertexPN.push_back(Vertex_PN(p, n));
	p = D3DXVECTOR3(-1, 1, 1); m_aVertexPN.push_back(Vertex_PN(p, n));

	p = D3DXVECTOR3(-1, 1, 1); m_aVertexPN.push_back(Vertex_PN(p, n));
	p = D3DXVECTOR3(-1, 1, -1); m_aVertexPN.push_back(Vertex_PN(p, n));
	p = D3DXVECTOR3(1, 1, -1); m_aVertexPN.push_back(Vertex_PN(p, n));

	p = D3DXVECTOR3(-1, 1, 1); m_aVertexPN.push_back(Vertex_PN(p, n));
	p = D3DXVECTOR3(1, 1, -1); m_aVertexPN.push_back(Vertex_PN(p, n));
	p = D3DXVECTOR3(1, 1, 1); m_aVertexPN.push_back(Vertex_PN(p, n));

	for (size_t i = 0; i < m_aVertexPN.size(); i += 3)
	{
		D3DXVECTOR3 v01 = m_aVertexPN[i + 1].p - m_aVertexPN[i].p;
		D3DXVECTOR3 v02 = m_aVertexPN[i + 2].p - m_aVertexPN[i].p;
		D3DXVec3Cross(&n, &v01, &v02);
		D3DXVec3Normalize(&n, &n);
		m_aVertexPN[i].n = m_aVertexPN[i + 1].n = m_aVertexPN[i + 2].n = n;
	}

	for (size_t i = 0; i < m_aVertexPN.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_aVertexPN[i].p, &m_aVertexPN[i].p, &m_matRot);
		D3DXVec3TransformNormal(&m_aVertexPN[i].n, &m_aVertexPN[i].n, &m_matRot);
	}

	SetScale(0.1f, 1.f, 0.1f);
}


cObject_Pyramid::~cObject_Pyramid()
{
}


void cObject_Pyramid::Update()
{
}


void cObject_Pyramid::Render()
{
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWolrd);
	g_pDevice->SetMaterial(&m_mtl);
	g_pDevice->SetFVF(Vertex_PN::FVF);
	
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_aVertexPN.size() / 3,
		&m_aVertexPN[0],
		sizeof(Vertex_PN));
}
