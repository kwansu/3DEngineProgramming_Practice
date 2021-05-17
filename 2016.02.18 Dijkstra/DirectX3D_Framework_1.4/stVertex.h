#pragma once

enum VERTEX_FVF
{
	P	=	D3DFVF_XYZ,
	PC	=	D3DFVF_XYZ | D3DFVF_DIFFUSE,
	PNT =	D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX0
};


struct stVertex_PC
{
	D3DXVECTOR3	p;
	D3DCOLOR	c;

public:
	stVertex_PC();
	stVertex_PC(D3DXVECTOR3 pos, D3DCOLOR color = D3DCOLOR_XRGB(0, 0, 0));
};


struct stVertex_PNT
{
	D3DXVECTOR3	p;
	D3DXVECTOR3	n;
	D3DXVECTOR2	t;

public:
	stVertex_PNT();
	stVertex_PNT(D3DXVECTOR3 pos, D3DXVECTOR3 nor, D3DXVECTOR2 tex);
};
