#pragma once

class cCollider_Sphere
{
private:
	D3DXVECTOR3	m_vOri;
	float		m_fRadius;

public:
	cCollider_Sphere();
	~cCollider_Sphere();

	D3DXVECTOR3 GetOriginPos() const;
	float		GetRadius() const;

	void SetOriginPos(const D3DXVECTOR3 &vPos);

	bool IsCollisionAsSphere(cCollider_Sphere* pColl);
};

