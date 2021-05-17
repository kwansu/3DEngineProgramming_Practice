#include "stdafx.h"
#include "cObj_Sphere.h"


cObj_Sphere::cObj_Sphere()
{
	D3DXCreateSphere(g_pDevice, 1, 10, 10, &m_pMesh, NULL);
}


cObj_Sphere::~cObj_Sphere()
{
}

void cObj_Sphere::Render()
{
	m_pMesh->DrawSubset(0);
}
