#pragma once
#include "iCollider.h"

class cResourceManager;

#define g_pColliderTerrain	cCollider_Terrain::GetInstance()

class cCollider_Terrain :
	public iCollider
{
	friend class cResourceManager;
	SINGLETONE(cCollider_Terrain);

private:
	vector<D3DXVECTOR3>	m_aVertex;
	D3DXMATRIXA16		m_matWorld;

public:
	void Update(D3DXMATRIXA16* pmatOwer);
	void Render();

	bool CollisionCheckOfRay(const cRay* pRay);
	bool CollisionCheckOfCollider(iCollider* pOther);
	bool SearchCollision(IN OUT cRay* pray, OUT float* fDist);

	COLLIDER_TYPE GetType();
};

