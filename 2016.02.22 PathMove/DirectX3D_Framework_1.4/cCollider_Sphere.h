#pragma once

class cRay;

class cCollider_Sphere
{
public:
	static bool IsCollisionAsSphere(const D3DXMATRIXA16* pmatInverse);
	static bool IsCollisionAsRay(cRay ray, const D3DXMATRIXA16* pmatInverse);
};

