#include "stdafx.h"
#include "cSkinningMesh.h"


cSkinningMesh::cSkinningMesh()
	: m_pRoot(NULL)
	, m_pAnimController(NULL)
	, m_isChangeAnim(false)
{
}


cSkinningMesh::~cSkinningMesh()
{
	cAllocateHierarchy alloc(NULL);
	D3DXFrameDestroy(m_pRoot, &alloc);
}

void cSkinningMesh::Load(char* szFile, char* szPath)
{
	cAllocateHierarchy alloc(szPath);

	string strFullPath = string(szPath) + string(szFile);

	D3DXLoadMeshHierarchyFromX(
		strFullPath.c_str(),
		D3DXMESH_MANAGED,
		g_pDevice,
		&alloc,
		NULL,
		(LPD3DXFRAME*)(&m_pRoot),
		&m_pAnimController);

	SetupBoneMatrixPtrs(m_pRoot);

	SetScale(0.4f, 0.4f, 0.4f);
	UpdateTransform();
}

void cSkinningMesh::Render()
{
	D3DXMATRIXA16 mat;

	D3DXMatrixTranslation(&mat, -10, 0, -5);
	m_pRoot->Render();
}

void cSkinningMesh::Update()
{
	if (g_pInput->IsKeyPress('B'))
		m_vRot.y += 1;

	UpdateTransform();

	if (m_pAnimController)
	{
		if (m_fWeight >= 1)
		{
			m_pAnimController->SetTrackWeight(0, 1);
			m_pAnimController->SetTrackEnable(1, false);
			m_isChangeAnim = false;
		}
		else
		{
			m_pAnimController->SetTrackWeight(0, m_fWeight);
			m_pAnimController->SetTrackWeight(1, 1 - m_fWeight);
			m_fWeight += 0.05f;
		}

		m_pAnimController->AdvanceTime(g_pTimeManger->GetDeltaTime() * 0.001f, NULL);
	}

	Update(m_pRoot, m_matWorld);
	UpdateSkinnedMesh(m_pRoot);
}

void cSkinningMesh::Update(cBone* pBone, const D3DXMATRIXA16 & matWorld)
{
	pBone->m_matCombinedTransformationMatrix = pBone->TransformationMatrix * matWorld;

	if (pBone->pFrameFirstChild)
	{
		Update((cBone*)pBone->pFrameFirstChild, pBone->m_matCombinedTransformationMatrix);
	}

	if (pBone->pFrameSibling)
	{
		Update((cBone*)pBone->pFrameSibling, matWorld);
	}
}

void cSkinningMesh::SetupBoneMatrixPtrs(LPD3DXFRAME pFrame)
{
	stBoneMesh* pBoneMesh = (stBoneMesh*)pFrame->pMeshContainer;

	if (pBoneMesh && pBoneMesh->pSkinInfo)
	{
		int nBone = pBoneMesh->pSkinInfo->GetNumBones();
		cBone* pBone;

		for (int i = 0; i < nBone; ++i)
		{
			pBone = (cBone*)D3DXFrameFind(m_pRoot, pBoneMesh->pSkinInfo->GetBoneName(i));
			pBoneMesh->ppBoneMatrixPtrs[i] = &pBone->m_matCombinedTransformationMatrix;
		}
	}

	if (pFrame->pFrameFirstChild)
	{
		SetupBoneMatrixPtrs(pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		SetupBoneMatrixPtrs(pFrame->pFrameSibling);
	}
}

void cSkinningMesh::UpdateSkinnedMesh(LPD3DXFRAME pFrame)
{
	stBoneMesh* pBoneMesh = (stBoneMesh*)pFrame->pMeshContainer;

	if (pBoneMesh && pBoneMesh->pSkinInfo && pBoneMesh->MeshData.pMesh)
	{
		int nBone = pBoneMesh->pSkinInfo->GetNumBones();

		for (int i = 0; i < nBone; ++i)
		{
			pBoneMesh->pCurrentBoneMatrices[i]
				= pBoneMesh->pBoneOffsetMatrices[i] * *pBoneMesh->ppBoneMatrixPtrs[i];
		}

		BYTE* src = NULL;
		BYTE* dest = NULL;

		pBoneMesh->pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&src);
		pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (void**)&dest);

		//MeshData.pMesh을 업데이트 시켜준다.
		pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
			pBoneMesh->pCurrentBoneMatrices, NULL, src, dest);

		pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
		pBoneMesh->pOrigMesh->UnlockVertexBuffer();
	}
	//재귀적으로 모든 프레임에 대해서 실행.
	if (pFrame->pFrameFirstChild)
	{
		UpdateSkinnedMesh(pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		UpdateSkinnedMesh(pFrame->pFrameSibling);
	}
}

void cSkinningMesh::SetAnimaitonTrack(int index)
{
	LPD3DXANIMATIONSET	pAnimSet =NULL;

	D3DXTRACK_DESC	trackDesc;

	m_pAnimController->GetTrackDesc(0, &trackDesc);

	m_pAnimController->GetTrackAnimationSet(0, &pAnimSet);
	m_pAnimController->SetTrackAnimationSet(1, pAnimSet);
	m_pAnimController->SetTrackDesc(1, &trackDesc);
	SafeRelease(pAnimSet);
	
	m_pAnimController->GetAnimationSet(index, &pAnimSet);
	m_pAnimController->SetTrackAnimationSet(0, pAnimSet);
	m_pAnimController->SetTrackPosition(0, 0);
	SafeRelease(pAnimSet);

	m_pAnimController->SetTrackEnable(1, true);

	m_fWeight = 0;
}

