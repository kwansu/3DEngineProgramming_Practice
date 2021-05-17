#pragma once
#include "cCollider_Sphere.h"

class cObj_Sphere	:
	public cGameObject
{
protected:
	LPD3DXMESH			m_pMesh;
	D3DMATERIAL9		m_mtl;

public:
	cObj_Sphere();
	~cObj_Sphere();
	
	void Update() override;
	void Render() override;
};

