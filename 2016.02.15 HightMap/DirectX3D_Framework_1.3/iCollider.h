#pragma once
#include "cRay.h"


enum COLLIDER_TYPE
{
	SPHERE, BOX, MESH
};


class iCollider
{
protected:
	//COLLIDER_TYPE	m_type;

public:
	virtual bool CollisionCheckOfRay(const cRay* pRay) = 0;
	virtual bool CollisionCheckOfCollider(iCollider* pOther) = 0;

	virtual COLLIDER_TYPE GetType() = 0;
};

