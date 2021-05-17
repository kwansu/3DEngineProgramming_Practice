#include "stdafx.h"
#include "cCollider_Box.h"


cCollider_Box::cCollider_Box()
{
}


cCollider_Box::~cCollider_Box()
{
}

bool cCollider_Box::IsCollisionAtRay(cRay ray, const D3DXMATRIXA16 * pmatInverse)
{
	if (pmatInverse)
		ray.Transform(pmatInverse);

	stRange rangeX, rangeY, rangeZ;

	if (!CalcAxisRange(ray.m_vOri.x, ray.m_vDir.x, rangeX))
		return false;

	if (!CalcAxisRange(ray.m_vOri.y, ray.m_vDir.y, rangeY))
		return false;

	if (!CalcAxisRange(ray.m_vOri.z, ray.m_vDir.z, rangeZ))
		return false;


	if (!stRange::OverlappedRange(rangeX, rangeY, NULL))
		return false;

	if (!stRange::OverlappedRange(rangeZ, rangeY, NULL))
		return false;

	if (!stRange::OverlappedRange(rangeX, rangeZ, NULL))
		return false;

	return true;
}

bool cCollider_Box::CalcAxisRange(float fAxisPos, float fAxisDir, OUT stRange &rangeAxis) const
{
	if (IsEqual(fAxisDir, 0))
	{
		if (fAxisPos > 1 || fAxisPos < 1)
			return false;
	}
	else
	{
		rangeAxis.fMax = (1 - fAxisPos) / fAxisDir;
		rangeAxis.fMin = (-1 - fAxisPos) / fAxisDir;
		rangeAxis.UpdateMinMax();

		if (rangeAxis.fMax <= 0)
			return false;
		
		rangeAxis.fMin = Greater(rangeAxis.fMin, 0.0f);
	}

	return true;
}
