#include "stdafx.h"
#include "cMap.h"


cMap::cMap()
: m_pmeshMap(NULL)
{
	g_pResourceManager->GetMesh(m_pmeshMap, "Map.obj");
	SetScale(0.1f, 0.1f, 0.1f);
	m_fAngleX = -90;
	UpdateWorld();
}


cMap::~cMap()
{
}


void cMap::Setup()
{

}


void cMap::Update()
{

}


void cMap::Render()
{
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWolrd);

	if (m_pmeshMap)
		m_pmeshMap->Render();
}
