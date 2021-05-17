#include "stdafx.h"
#include "cObject_Woman.h"


cObject_Woman::cObject_Woman()
{
	//m_fAngleX = -90;
	SetScale(5, 5, 5);
	UpdateWorld();
	m_pCollider = new cCollider_Sphere;
}


cObject_Woman::~cObject_Woman()
{
	SafeDelete(m_pCollider);
}


void cObject_Woman::Setup()
{
}


void cObject_Woman::Update()
{
}


void cObject_Woman::Render()
{
	m_pRoot->Render(&m_matWolrd);

	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWolrd);
	m_pCollider->Render();
}
