#pragma once
#include "stdCollider.h"

class cRay
{
public:
	D3DXVECTOR3		m_vOri;
	D3DXVECTOR3		m_vDir;

public:
	cRay();
	cRay(D3DXVECTOR3 vOri, D3DXVECTOR3 vDir);
	~cRay();

	void SetRay(const D3DXVECTOR3 vOri, const D3DXVECTOR3 vDir);
	bool IsCollisionSphere(cCollider_Sphere* pColl) const;
};

