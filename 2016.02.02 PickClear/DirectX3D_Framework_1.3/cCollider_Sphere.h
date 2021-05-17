#pragma once

class cCollider_Sphere
{
private:
	ID3DXMesh*	m_pMesh;
	float		m_fRadius;

public:
	D3DXVECTOR3	m_vOrigin;
	cCollider_Sphere();
	~cCollider_Sphere();
	void Update();
	void Render();
	bool IsCollisionSphere(cCollider_Sphere* pColl);
};

