#include "stdafx.h"
#include "stVertex.h"


stVertex_PC::stVertex_PC()
	: p(0, 0, 0)
	, c(D3DCOLOR_XRGB(0, 0, 0))
{
}

stVertex_PC::stVertex_PC(D3DXVECTOR3 pos, D3DCOLOR color)
	: p(pos)
	, c(color)
{
}
