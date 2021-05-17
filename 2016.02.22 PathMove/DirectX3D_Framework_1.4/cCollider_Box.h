#pragma once
#include "cRay.h"

class cCollider_Box
{
public:
	static bool IsCollisionAsRay(cRay ray, const D3DXMATRIXA16* pmatInverse);

private:
	static bool CalcAxisRange(float fAxisPos, float fAxisDir, OUT stRange &rangeAxis);
};

