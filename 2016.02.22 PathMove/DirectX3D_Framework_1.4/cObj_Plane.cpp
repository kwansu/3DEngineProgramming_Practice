#include "stdafx.h"
#include "cObj_Plane.h"


cObj_Plane::cObj_Plane()
{
}


cObj_Plane::~cObj_Plane()
{
}

void cObj_Plane::Setup()
{
	cObj_Box::Setup();
	
	m_pMeshData->GetAttributeDate()[0].mtl.Diffuse = D3DXCOLOR(0.9f, 0.9f, 1, 1.0f);

	SetScale(50, 0.1f, 50);
	SetPosition(0, -0.3f, 0);
}

void cObj_Plane::Update()
{
	cObj_Mesh::Update();
}
