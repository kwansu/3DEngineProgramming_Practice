#include "stdafx.h"
#include "cObject_Structure.h"


cObject_Structure::cObject_Structure()
: m_pCollider(NULL)
, m_pMesh(NULL)
{
	g_pResourceManager->GetMesh(m_pMesh, "map.obj");
	g_pResourceManager->GetCollider(m_pCollider
		, "map_surface.obj");

	SetScale(0.1f, 0.1f, 0.1f);
	m_fAngleX = -90;
	UpdateWorld();
}


cObject_Structure::~cObject_Structure()
{
}


void cObject_Structure::Setup()
{
}


void cObject_Structure::Update()
{
}


void cObject_Structure::Render()
{
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWolrd);
	m_pMesh->Render();
}
