#pragma once

enum VERTEX_FVF
{
	P	=	D3DFVF_XYZ,
	PC	=	D3DFVF_XYZ | D3DFVF_DIFFUSE,
};


struct stVertex_PC
{
	D3DXVECTOR3	p;
	D3DCOLOR	c;

public:
	stVertex_PC();
	stVertex_PC(D3DXVECTOR3 pos, D3DCOLOR color = D3DCOLOR_XRGB(0, 0, 0));
};

