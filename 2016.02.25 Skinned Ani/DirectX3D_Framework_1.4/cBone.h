#pragma once
#include "d3dx9anim.h"

struct stBoneMesh : public D3DXMESHCONTAINER
{
	vector<LPDIRECT3DTEXTURE9>	vecTexture;

	LPD3DXMESH					pOrigMesh;
	D3DXMATRIX**				ppBoneMatrixPtrs;
	D3DXMATRIX*					pBoneOffsetMatrices;
	D3DXMATRIX*					pCurrentBoneMatrices;
};

class cBone :
	public D3DXFRAME
{
public:
	D3DXMATRIXA16	m_matCombinedTransformationMatrix;

public:
	cBone(LPCSTR Name);
	~cBone();

	void Render();
};

