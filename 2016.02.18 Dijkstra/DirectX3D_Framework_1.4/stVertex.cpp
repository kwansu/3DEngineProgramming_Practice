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

stVertex_PNT::stVertex_PNT()
	: p(0, 0, 0)
	, n(0, 1, 0)
	, t(0, 0)
{
}

stVertex_PNT::stVertex_PNT(D3DXVECTOR3 pos, D3DXVECTOR3 nor, D3DXVECTOR2 tex)
	: p(pos)
	, n(nor)
	, t(tex)
{
}
