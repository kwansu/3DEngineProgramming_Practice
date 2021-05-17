#pragma once
#include "cCollider_Sphere.h"
//class cCollider_Sphere;

class cCollider_Box	:
	public iCollider
{
private:
	vector<D3DXVECTOR3>	m_aVertex;
	D3DXMATRIXA16		m_matWorld;
	D3DXMATRIXA16		m_matLocal;

public:
	cCollider_Box();
	~cCollider_Box();

	void Update(const D3DXMATRIXA16* pmatOwer);
	COLLIDER_TYPE GetType()	override { return BOX; }

	bool CollisionCheckOfRay(const cRay* pRay) override;
	bool CollisionCheckOfCollider(iCollider* pOther) override;
	bool CollisionCheckOfCollider(const cCollider_Box* pOther, const bool bRepeat) const;
	bool CollisionCheckOfCollider(const cCollider_Sphere* pOther);
};

