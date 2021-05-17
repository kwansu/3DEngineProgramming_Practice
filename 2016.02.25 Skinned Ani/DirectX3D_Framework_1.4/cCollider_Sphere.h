#pragma once

class cRay;

class cCollider_Sphere
{
public:
	static bool IsCollisionAsSphere(const D3DXVECTOR3& vOri, float fRadius, const D3DXVECTOR3& vOri2, float fRadius2);
	static bool IsCollisionAsRay(cRay ray, const D3DXMATRIXA16* pmatInverse);
};

