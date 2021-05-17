#include "stdafx.h"
#include "cHeightMap.h"


cHeightMap::cHeightMap()
	: m_pMesh(NULL)
	, m_pTexture(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
	ZeroMemory(&m_mtl, sizeof(D3DMATERIAL9));
}


cHeightMap::~cHeightMap()
{
	SafeRelease(m_pMesh);
	SafeRelease(m_pTexture);
}

void cHeightMap::Setup()
{
	cRawLoader loader;

	m_pMesh = loader.LoadRaw("./HeightMapData/HeightMap.raw", m_vecPos);
	m_uLen = sqrt(m_vecPos.size());

	m_mtl.Diffuse  = D3DXCOLOR(1, 1, 1, 1);

	D3DXCreateTextureFromFile(g_pDevice,
		"./HeightMapData/terrain.jpg",
		&m_pTexture);
}

void cHeightMap::Render()
{
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pDevice->SetTexture(0, m_pTexture);
	g_pDevice->SetMaterial(&m_mtl);
	m_pMesh->DrawSubset(0);
}

bool cHeightMap::GetHeight(const float x, const float y, OUT float* pfResultY)
{
	int row = x;
	int col = y;

	if (row <= 0 || row >= m_uLen || col <= 0 || col >= m_uLen)
		return false;

	float fPointY;
	float fRow_t = x - row;
	float fCol_t = y - col;

	if (fRow_t + fCol_t < 1)
	{
		*pfResultY = fPointY = m_vecPos[row + col*m_uLen].y;
		*pfResultY += (m_vecPos[(row + 1) + col*m_uLen].y - fPointY) * fRow_t;
		*pfResultY += (m_vecPos[row + (col + 1)*m_uLen].y - fPointY) * fCol_t;
	}
	else
	{
		*pfResultY = fPointY = m_vecPos[(row + 1) + (col + 1)*m_uLen].y;
		*pfResultY += (m_vecPos[(row + 1) + col*m_uLen].y - fPointY) * (1 - fCol_t);
		*pfResultY += (m_vecPos[row + (col + 1)*m_uLen].y - fPointY) * (1 - fRow_t);
	}

	return true;
}
