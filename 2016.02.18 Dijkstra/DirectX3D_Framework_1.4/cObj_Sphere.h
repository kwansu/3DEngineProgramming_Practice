#pragma once
#include "cCollider_Sphere.h"

class cObj_Sphere	:
	public cGameObject
{
private:
	LPD3DXMESH			m_pMesh;
	cCollider_Sphere*	m_pColl;
	D3DMATERIAL9		m_mtl;

	bool				m_bDrag;
	bool				m_bCollision;
	bool				m_bMove;
	D3DXVECTOR3			m_vOffset;
	D3DXVECTOR3			m_vWayPos;

public:
	cObj_Sphere();
	~cObj_Sphere();
	
	void Update() override;
	void Render() override;

	bool IsCollision(cObj_Sphere* pSphere);
};

