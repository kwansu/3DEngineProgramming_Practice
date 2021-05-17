#include "stdafx.h"
#include "cAllocateHierarchy.h"


cAllocateHierarchy::cAllocateHierarchy(char * szPath)
{
	if (szPath)
		m_strPath = string(szPath);
}

cAllocateHierarchy::~cAllocateHierarchy()
{
}

STDMETHODIMP cAllocateHierarchy::CreateFrame(LPCSTR Name, LPD3DXFRAME * ppNewFrame)
{
	*ppNewFrame = new cBone(Name);

	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::CreateMeshContainer(LPCSTR Name,
	CONST D3DXMESHDATA * pMeshData,
	CONST D3DXMATERIAL * pMaterials,
	CONST D3DXEFFECTINSTANCE * pEffectInstances,
	DWORD NumMaterials,
	CONST DWORD * pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER * ppNewMeshContainer)
{
	stBoneMesh* pBoneMesh = new stBoneMesh;

	pBoneMesh->Name = NULL;

	if (Name)
	{
		pBoneMesh->Name = new char[strlen(Name) + 1];
		strcpy_s(pBoneMesh->Name, strlen(Name) + 1,  Name);
	}

	if (pMeshData && pMeshData->Type == D3DXMESHTYPE_MESH)
	{
		HRESULT uR = pMeshData->pMesh->CloneMeshFVF(pMeshData->pMesh->GetOptions(),
			pMeshData->pMesh->GetFVF(),
			g_pDevice,
			&pBoneMesh->pOrigMesh);

		if (uR == D3DERR_INVALIDCALL)
		{
			pBoneMesh->MeshData.pMesh = NULL;
			pBoneMesh->pOrigMesh = NULL;
		}
		else
		{
			pMeshData->pMesh->AddRef();
			pBoneMesh->MeshData.pMesh = pMeshData->pMesh;
		}
	}
	else if (pMeshData)
	{
		assert(false, "처리하지 않은 종류의 매쉬가 있습니다.");
	}

	if (pMaterials)
	{
		pBoneMesh->pMaterials = new D3DXMATERIAL[NumMaterials];
		pBoneMesh->vecTexture.resize(NumMaterials);
		for (int i = 0; i < NumMaterials; ++i)
		{
			pBoneMesh->pMaterials[i].MatD3D = pMaterials[i].MatD3D;

			if (pMaterials[i].pTextureFilename)
			{
				string strFullPath = m_strPath + string(pMaterials[i].pTextureFilename);

				pBoneMesh->vecTexture[i] =
					g_pTexture->LoadTextureDate(strFullPath.c_str()).pTexture;
			}
		}
	}

	pBoneMesh->NumMaterials = NumMaterials;
	pBoneMesh->pEffects = NULL;
	pBoneMesh->pAdjacency = NULL;

	if (pSkinInfo)
	{
		pBoneMesh->pSkinInfo = pSkinInfo;
		pSkinInfo->AddRef();

		int nBone = pSkinInfo->GetNumBones();

		pBoneMesh->ppBoneMatrixPtrs = new D3DXMATRIX*[nBone];
		pBoneMesh->pBoneOffsetMatrices = new D3DXMATRIX[nBone];
		pBoneMesh->pCurrentBoneMatrices = new D3DXMATRIX[nBone];

		for (int i = 0; i < nBone; ++i)
		{
			pBoneMesh->pBoneOffsetMatrices[i] = *(pSkinInfo->GetBoneOffsetMatrix(i));
		}
	}
	else
	{
		pBoneMesh->pSkinInfo = NULL;
		pBoneMesh->ppBoneMatrixPtrs = NULL;
		pBoneMesh->pBoneOffsetMatrices = NULL;
		pBoneMesh->pCurrentBoneMatrices = NULL;
	}

	*ppNewMeshContainer = pBoneMesh;

	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	if (pFrameToFree)
	{
		if (pFrameToFree->Name)
			delete[] pFrameToFree->Name;
	}

	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	stBoneMesh* pBoneMesh = (stBoneMesh*)pMeshContainerToFree;

	if (pBoneMesh)
	{
		if (pBoneMesh->Name)
			delete[] pBoneMesh->Name;

		SafeRelease(pBoneMesh->MeshData.pMesh);
		SafeRelease(pBoneMesh->pOrigMesh);
		SafeRelease(pBoneMesh->pSkinInfo);

		if (pBoneMesh->pMaterials)
			delete[] pBoneMesh->pMaterials;

		delete[] pBoneMesh->ppBoneMatrixPtrs;
		delete[] pBoneMesh->pBoneOffsetMatrices;
		delete[] pBoneMesh->pCurrentBoneMatrices;
	}

	return S_OK;
}

