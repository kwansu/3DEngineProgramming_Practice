#include "stdafx.h"
#include "cCollider_Terrain.h"


cCollider_Terrain::cCollider_Terrain()
{
	D3DXMATRIXA16 matS, matR;

	D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);
	D3DXMatrixRotationX(&matR, D3DXToRadian(-90));

	m_matWorld = matS * matR;
}


cCollider_Terrain::~cCollider_Terrain()
{
}


void cCollider_Terrain::Update(D3DXMATRIXA16* pmatOwer)
{
}


void cCollider_Terrain::Render()
{
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pDevice->SetFVF(D3DFVF_XYZ);
	g_pDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		m_aVertex.size() / 3,
		&m_aVertex[0],
		sizeof(D3DXVECTOR3));
}


bool cCollider_Terrain::CollisionCheckOfRay(const cRay* pRay)
{
	return false;
}


bool cCollider_Terrain::CollisionCheckOfCollider(iCollider* pOther)
{
	return false;
}


bool cCollider_Terrain::SearchCollision(IN OUT cRay* pray, OUT float* fDist)
{
	pray->m_vOri.y += 1000;

	D3DXVECTOR3 vOri, vDir;
	D3DXMATRIXA16 matIn;

	D3DXMatrixInverse(&matIn, NULL, &m_matWorld);
	D3DXVec3TransformCoord(&vOri, &pray->m_vOri, &matIn);
	D3DXVec3TransformNormal(&vDir, &pray->m_vDir, &matIn);
	D3DXVec3Normalize(&vDir, &vDir);

	for (int i = 0; i < m_aVertex.size(); i += 3)
	{
		if (D3DXIntersectTri(&m_aVertex[i], &m_aVertex[i + 1]
			, &m_aVertex[i + 2], &vOri, &vDir, NULL, NULL, fDist))
		{
			*fDist *= -0.1;
			*fDist += 1000;
			return true;
		}
	}

	return false;
}


COLLIDER_TYPE cCollider_Terrain::GetType()
{
	return BOX;
}
