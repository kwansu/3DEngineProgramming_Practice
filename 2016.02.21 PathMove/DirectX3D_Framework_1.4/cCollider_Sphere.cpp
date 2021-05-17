#include "stdafx.h"
#include "cCollider_Sphere.h"

bool cCollider_Sphere::IsCollisionAsSphere(const D3DXMATRIXA16 * pmatInverse)
{
	return false;
}

bool cCollider_Sphere::IsCollisionAsRay(cRay ray, const D3DXMATRIXA16 * pmatInverse)
{
	if (pmatInverse)
	{
		ray.Transform(pmatInverse);
		D3DXVec3Normalize(&ray.m_vDir, &ray.m_vDir);
	}

	float d = D3DXVec3Dot(&ray.m_vOri, &ray.m_vDir);
	d = D3DXVec3LengthSq(&ray.m_vOri) - d * d;

	if (d <= 1)
		return true;

	return false;
}
