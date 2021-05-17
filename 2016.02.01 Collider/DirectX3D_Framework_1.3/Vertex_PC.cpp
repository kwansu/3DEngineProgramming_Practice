#include "stdafx.h"
#include "stVertex.h"


Vertex_PC::Vertex_PC()
	: p(0, 0, 0), c(D3DCOLOR_XRGB(0, 0, 0))
{
}


Vertex_PC::Vertex_PC(D3DXVECTOR3 pos, D3DCOLOR color)
	: p(pos), c(color)
{
}



Vertex_PN::Vertex_PN()
	: p(0, 0, 0), n(0, 0, 1)
{
}


Vertex_PN::Vertex_PN(D3DXVECTOR3 pos, D3DXVECTOR3 normal)
	: p(pos), n(normal)
{
}



Vertex_PT::Vertex_PT()
	: p(0, 0, 0), t(0, 0)
{
}


Vertex_PT::Vertex_PT(D3DXVECTOR3 pos, D3DXVECTOR2 tex)
	: p(pos), t(tex)
{
}



Vertex_PNT::Vertex_PNT()
	: p(0, 0, 0), n(0, 0, 0), t(0, 0)
{
}


Vertex_PNT::Vertex_PNT(D3DXVECTOR3 pos)
	: p(pos), n(0, 0, 0), t(0, 0)
{
}


Vertex_PNT::Vertex_PNT(D3DXVECTOR3 pos, D3DXVECTOR3 normal, D3DXVECTOR2 tex)
	: p(pos), n(normal), t(tex)
{
}



MtlTexture::MtlTexture()
: pTex(NULL)
{
	ZeroMemory(&mtl, sizeof(D3DMATERIAL9));
}


MtlTexture::~MtlTexture()
{
	cReferrers::Release();
}