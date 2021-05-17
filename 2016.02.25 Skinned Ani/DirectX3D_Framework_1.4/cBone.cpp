#include "stdafx.h"
#include "cBone.h"


cBone::cBone(LPCSTR _Name)
{
	Name = NULL;

	if (_Name)
	{
		int lenght = strlen(_Name) + 1;

		Name = new char[lenght];
		memcpy(Name, _Name, sizeof(char) * lenght);
	}

	D3DXMatrixIdentity(&m_matCombinedTransformationMatrix);
}


cBone::~cBone()
{
	if (pFrameSibling)
	{
		SafeDelete(pFrameSibling);
	}

	if (pFrameFirstChild)
	{
		SafeDelete(pFrameFirstChild);
	}
}

void cBone::Render()
{
	stBoneMesh* pBoneMesh = (stBoneMesh*)pMeshContainer;
	if (pBoneMesh)
	{
		g_pDevice->SetFVF(pBoneMesh->MeshData.pMesh->GetFVF());
		g_pDevice->SetTransform(D3DTS_WORLD, &m_matCombinedTransformationMatrix);

		for (int i = 0; i < pBoneMesh->NumMaterials; ++i)
		{
			g_pDevice->SetTexture(0, pBoneMesh->vecTexture[i]);
			g_pDevice->SetMaterial(&pBoneMesh->pMaterials[i].MatD3D);
			pBoneMesh->MeshData.pMesh->DrawSubset(i);
		}
	}


	if (pFrameSibling)
	{
		((cBone*)pFrameSibling)->Render();
	}

	if (pFrameFirstChild)
	{
		((cBone*)pFrameFirstChild)->Render();
	}
}

