#include "stdafx.h"
#include "cObject_Cube.h"


cObject_Cube::cObject_Cube()
: m_pTexture(NULL)
{
	ZeroMemory(&m_stMaterial, sizeof(D3DMATERIAL9));

	m_stMaterial.Ambient = D3DXCOLOR(0.1f, 0.0f, 0.1f, 1.0f);
	m_stMaterial.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//m_stMaterial.Emissive = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	//m_stMaterial.Specular = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	m_stMaterial.Power = 5.0f;

	m_aLocalPos.push_back(D3DXVECTOR3(-1, -1, -1));
	m_aLocalPos.push_back(D3DXVECTOR3(-1, 1, -1));
	m_aLocalPos.push_back(D3DXVECTOR3(1, 1, -1));
	m_aLocalPos.push_back(D3DXVECTOR3(1, -1, -1));
	m_aLocalPos.push_back(D3DXVECTOR3(-1, -1, 1));
	m_aLocalPos.push_back(D3DXVECTOR3(-1, 1, 1));
	m_aLocalPos.push_back(D3DXVECTOR3(1, 1, 1));
	m_aLocalPos.push_back(D3DXVECTOR3(1, -1, 1));

	D3DCOLOR c;
	c = D3DCOLOR_XRGB(210, 210, 210);
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(-1, -1, -1), -m_vLook));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(-1, 1, -1), -m_vLook));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(1, 1, -1), -m_vLook));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(-1, -1, -1), -m_vLook));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(1, 1, -1), -m_vLook));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(1, -1, -1), -m_vLook));

	c = D3DCOLOR_XRGB(83, 83, 83);
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(-1, -1, 1), m_vLook));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(1, 1, 1), m_vLook));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(-1, 1, 1), m_vLook));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(-1, -1, 1), m_vLook));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(1, -1, 1), m_vLook));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(1, 1, 1), m_vLook));

	c = D3DCOLOR_XRGB(113, 113, 113);
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(-1, -1, 1), -m_vRight));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(-1, 1, 1), -m_vRight));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(-1, 1, -1), -m_vRight));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(-1, -1, 1), -m_vRight));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(-1, 1, -1), -m_vRight));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(-1, -1, -1), -m_vRight));

	c = D3DCOLOR_XRGB(143, 143, 143);
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(1, -1, -1), m_vRight));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(1, 1, -1), m_vRight));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(1, 1, 1), m_vRight));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(1, -1, -1), m_vRight));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(1, 1, 1), m_vRight));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(1, -1, 1), m_vRight));

	c = D3DCOLOR_XRGB(173, 173, 173);
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(-1, 1, -1), m_vUp));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(-1, 1, 1), m_vUp));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(1, 1, 1), m_vUp));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(-1, 1, -1), m_vUp));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(1, 1, 1), m_vUp));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(1, 1, -1), m_vUp));

	c = D3DCOLOR_XRGB(203, 203, 203);
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(-1, -1, 1), -m_vUp));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(-1, -1, -1), -m_vUp));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(1, -1, -1), -m_vUp));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(-1, -1, 1), -m_vUp));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(1, -1, -1), -m_vUp));
	m_aVertexPN.push_back(Vertex_PN(D3DXVECTOR3(1, -1, 1), -m_vUp));
}


cObject_Cube::~cObject_Cube()
{
}


void cObject_Cube::Setup()
{
}


void cObject_Cube::Update()
{
}


void cObject_Cube::Render()
{
	g_pDevice->SetMaterial(&m_stMaterial);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWolrd);

	if (m_pTexture)
	{
		g_pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1);
		g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			m_aVertexPNT.size() / 3, &m_aVertexPNT[0], sizeof(Vertex_PNT));
	}
	else
	{
	g_pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL );
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_aVertexPN.size() / 3, &m_aVertexPN[0], sizeof(Vertex_PN));
	}
}


void cObject_Cube::SetLocalSize(float sx, float sy, float sz)
{
	int size = m_aVertexPN.size();
	for (int i = 0; i < size; ++i)
	{
		m_aVertexPN[i].p.x *= sx;
		m_aVertexPN[i].p.y *= sy;
		m_aVertexPN[i].p.z *= sz;
	}
	size = m_aLocalPos.size();
	for (int i = 0; i < size; ++i)
	{
		m_aLocalPos[i].x *= sx;
		m_aLocalPos[i].y *= sy;
		m_aLocalPos[i].z *= sz;
	}
	size = m_aVertexPNT.size();
	for (int i = 0; i < size; ++i)
	{
		m_aVertexPNT[i].p.x *= sx;
		m_aVertexPNT[i].p.y *= sy;
		m_aVertexPNT[i].p.z *= sz;
	}
}
