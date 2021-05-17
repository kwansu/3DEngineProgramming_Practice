#pragma once
#include "d3dx9anim.h"
#include "cBone.h"

class cAllocateHierarchy :
	public ID3DXAllocateHierarchy
{
private:
	string	m_strPath;

public:
	cAllocateHierarchy(char* szPath);
	~cAllocateHierarchy();

	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name,
		LPD3DXFRAME *ppNewFrame);

	STDMETHOD(CreateMeshContainer)(THIS_ 
		LPCSTR Name,
		CONST D3DXMESHDATA *pMeshData, 
		CONST D3DXMATERIAL *pMaterials, 
		CONST D3DXEFFECTINSTANCE *pEffectInstances, 
		DWORD NumMaterials, 
		CONST DWORD *pAdjacency, 
		LPD3DXSKININFO pSkinInfo, 
		LPD3DXMESHCONTAINER *ppNewMeshContainer);

	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree); 

	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree); 
};

