#pragma once

class cRay;

class iCollider
{
public:
	virtual ~iCollider() {}

	virtual bool IsCollisionAsRay(cRay* pray)		{ return false; }
	virtual bool IsCollision(iCollider* pOther)		{ return false; }
};

