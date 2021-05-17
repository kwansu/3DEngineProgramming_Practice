#include "stdafx.h"
#include "cCollider_Box.h"


cCollider_Box::cCollider_Box()
{
	//m_type = COLLIDER_TYPE::BOX;

	D3DXMatrixIdentity(&m_matLocal);
	D3DXMatrixIdentity(&m_matWorld);

	// ������ �˻縦 ���� 0, 1, 2, 3�ε����� ������ �𼭸��̴�.
	m_aVertex.push_back(D3DXVECTOR3(-1, -1, -1));
	m_aVertex.push_back(D3DXVECTOR3( 1, -1, -1));
	m_aVertex.push_back(D3DXVECTOR3( 1,  1, -1));
	m_aVertex.push_back(D3DXVECTOR3( 1,  1,  1));
	m_aVertex.push_back(D3DXVECTOR3(-1, -1,  1));
	m_aVertex.push_back(D3DXVECTOR3( 1, -1,  1));
	m_aVertex.push_back(D3DXVECTOR3(-1,  1, -1));
	m_aVertex.push_back(D3DXVECTOR3(-1,  1,  1));
}


cCollider_Box::~cCollider_Box()
{
}


void cCollider_Box::Update(const D3DXMATRIXA16* pmatOwer)
{
	m_matWorld = m_matLocal * *pmatOwer;
}


bool cCollider_Box::CollisionCheckOfRay(const cRay* pRay)
{
	// TODO  : ������ ���� ����. ���� ��, �ְ�� ȿ������ ����� ����Ѵ�.

	// csae1 : �Ѹ��� ���� �밢�� v1, v2�� ���Ͽ� ������ �����ǹ�
	// p1, p2��, �� ���� �ִܰŸ� d1, d2�� ����ؼ�
	// if ((d1+d2)^2 > (|v1-v2|^2 - |p1-p2|^2)) return false;

	// case2 : �h���� ���� �밢���� �����ǹ��� ���� (v1, v2) (v3, v4)��
	// �ϰ�, �� ���� �ִܰŸ��� (d1, d2) (d3, d4)��� �� ��,
	// if ( d1 + d2 != d3 + d4) return false;
	// ������ ������ ���������� �׻� �밢������ �ִܰŸ����� ����, �ƴ϶��
	// �ٱ��� �밢���� ���� ���� �밢���� �պ��� �۴�.
	// epsilon�� ���� ������ ���� ������ �� �� ���� ��� ��ü�Ͽ� ���.

	// case 3 : ���� ������ ��� ��� 12���� �ﰢ��� ������ ������ ��.
	// �߽� : 1, 2�� ����� �ִ� 3���� �������� ��� ���� ���� �� �ִ�. P(3)

	D3DXVECTOR3 vDig, vDir, p1, p2;

	D3DXVec3Normalize(&vDir, &pRay->m_vDir);
	vDig = m_aVertex[3] - m_aVertex[6];

	p1 = pRay->m_vOri + D3DXVec3Dot(&(m_aVertex[3] - pRay->m_vOri), &vDir) * vDir;
	p2 = pRay->m_vOri + D3DXVec3Dot(&(m_aVertex[6] - pRay->m_vOri), &vDir) * vDir;

	float fLsq = D3DXVec3Dot(&vDig, &vDir);
	fLsq = D3DXVec3LengthSq(&vDig) - fLsq * fLsq;


	return false;
}


bool cCollider_Box::CollisionCheckOfCollider(iCollider* pOther)
{
	if (pOther->GetType() == BOX)
		return CollisionCheckOfCollider(dynamic_cast<cCollider_Box*>(pOther), true);
	if (pOther->GetType() == SPHERE)
		return CollisionCheckOfCollider(dynamic_cast<cCollider_Sphere*>(pOther));

	assert("Collider_Box::CollisionCheckOfCollider : wrong type.");
	return false;
}


bool cCollider_Box::CollisionCheckOfCollider(const cCollider_Box* pOther, const bool bRepeat) const
{
	for (int i = 0; i < 3; ++i)
	{
		D3DXVECTOR3 vDir = m_aVertex[i] - m_aVertex[i + 1];
		D3DXVec3Normalize(&vDir, &vDir);

		float fMin = D3DXVec3Dot(&m_aVertex[i], &vDir);
		float fMax = D3DXVec3Dot(&m_aVertex[i + 1], &vDir);
		AlignMinMax(fMin, fMax);		// ���� �� ���� ���ؼ� �����ѵ�, �����ش�.

		float fRatio;
		bool  bOverlap = false;

		int size = pOther->m_aVertex.size();
		for (int i = 0; i < size; ++i)
		{
			fRatio = D3DXVec3Dot(&pOther->m_aVertex[i], &vDir);
			if (fRatio > fMin && fRatio < fMax)
				bOverlap = true;
		}

		if (!bOverlap)
			return false;
	}

	if (!pOther->CollisionCheckOfCollider(this, false))
		return false;

	return true;
}


bool cCollider_Box::CollisionCheckOfCollider(const cCollider_Sphere* pOther)
{
	int size = m_aVertex.size();
	for (int i = 0; i < size; ++i)
	{
		if (pOther->CollisionCheckOfPoint(&m_aVertex[i]))
			return true;
	}

	return false;
}
