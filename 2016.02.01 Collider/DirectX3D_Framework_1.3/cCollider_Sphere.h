#pragma once
class cCollider_Sphere
{
private:
	ID3DXMesh*		m_pMesh;

	D3DXVECTOR3		m_vOrigin;
	float			m_fRadius;

public:
	cCollider_Sphere();
	~cCollider_Sphere();
	void Update();
	void Render();
};

