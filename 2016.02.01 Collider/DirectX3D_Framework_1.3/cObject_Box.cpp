#include "stdafx.h"
#include "cObject_Box.h"


cObject_Box::cObject_Box()
{
	D3DXCreateBox(g_pDevice, 10, 5, 5, &m_mesh, NULL);
	ZeroMemory(&m_mtl, sizeof(D3DMATERIAL9));
	m_mtl.Diffuse = D3DXCOLOR(1.0f, 0, 1.0f, 1.0f);
}


cObject_Box::~cObject_Box()
{
	SafeRelease(m_mesh);
}


void cObject_Box::Setup()
{
}


void cObject_Box::Update()
{
}


void cObject_Box::Render()
{
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWolrd);
	g_pDevice->SetMaterial(&m_mtl);
	m_mesh->DrawSubset(0);
}
