#pragma once

// 랜더에 사용할 버텍스 구조체 정의:

struct Vertex_PC
{
	D3DXVECTOR3	p;
	D3DCOLOR	c;

	Vertex_PC();
	Vertex_PC(D3DXVECTOR3 pos, D3DCOLOR color = D3DCOLOR_XRGB(0, 0, 0));
	enum  { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};



struct Vertex_PN
{
	D3DXVECTOR3	p;
	D3DXVECTOR3 n;

	Vertex_PN();
	Vertex_PN(D3DXVECTOR3 pos, D3DXVECTOR3 normal);
	enum  { FVF = D3DFVF_XYZ | D3DFVF_NORMAL };
};



struct Vertex_PT
{
	D3DXVECTOR3	p;
	D3DXVECTOR2 t;

	Vertex_PT();
	Vertex_PT(D3DXVECTOR3 pos, D3DXVECTOR2 tex);
	enum  { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};



struct Vertex_PNT
{
	D3DXVECTOR3	p;
	D3DXVECTOR3	n;
	D3DXVECTOR2	t;

	Vertex_PNT();
	Vertex_PNT(D3DXVECTOR3 pos);
	Vertex_PNT(D3DXVECTOR3 pos, D3DXVECTOR3 normal, D3DXVECTOR2 tex);
	enum  { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};



struct MtlTexture : public cReferrers
{
	D3DMATERIAL9		mtl;
	LPDIRECT3DTEXTURE9	pTex;

	MtlTexture();
	~MtlTexture();
};