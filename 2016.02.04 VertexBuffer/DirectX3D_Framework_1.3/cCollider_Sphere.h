#pragma once
#include "iCollider.h"

class cCollider_Sphere	:
	public iCollider
{
private:
	ID3DXMesh*		m_pMesh;
	//D3DXVECTOR3		m_vOrigin;
	float			m_fRadius;

public:
	D3DXVECTOR3	m_vOrigin;
	cCollider_Sphere();
	~cCollider_Sphere();

	void Update();
	void Render();
	bool IsCollisionSphere(cCollider_Sphere* pColl);
	bool CollisionCheckOfPoint(const D3DXVECTOR3* pvPos) const;
	bool CollisionCheckOfRay(const cRay* pRay) override;
	bool CollisionCheckOfCollider(iCollider* pOther) override;

	COLLIDER_TYPE GetType() override { return SPHERE; }
};

