#pragma once
#include "cRay.h"

class cCollider_Box
{
public:
	cCollider_Box();
	~cCollider_Box();

	bool IsCollisionAtRay(cRay ray, const D3DXMATRIXA16* pmatInverse);

private:
	bool CalcAxisRange(float fAxisPos, float fAxisDir, OUT stRange &rangeAxis) const;
};

