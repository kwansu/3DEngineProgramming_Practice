#include "stdafx.h"
#include "cCollider_Box.h"


cCollider_Box::cCollider_Box()
{
	//m_type = COLLIDER_TYPE::BOX;

	D3DXMatrixIdentity(&m_matLocal);
	D3DXMatrixIdentity(&m_matWorld);

	// 순차적 검사를 위해 0, 1, 2, 3인덱스는 인접한 모서리이다.
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
	// TODO  : 직선과 선의 교차. 실험 후, 최고로 효율적인 방법을 사용한다.

	// csae1 : 한면의 안쪽 대각점 v1, v2에 대하여 직선에 수선의발
	// p1, p2와, 그 때의 최단거리 d1, d2를 사용해서
	// if ((d1+d2)^2 > (|v1-v2|^2 - |p1-p2|^2)) return false;

	// case2 : 햔면의 교차 대각점의 수선의발을 각각 (v1, v2) (v3, v4)라
	// 하고, 그 때의 최단거리를 (d1, d2) (d3, d4)라고 할 때,
	// if ( d1 + d2 != d3 + d4) return false;
	// 위에서 직선이 안지나가면 항상 대각점들의 최단거리합이 같고, 아니라면
	// 바깥쪽 대각점의 합이 안쪽 대각점의 합보다 작다.
	// epsilon의 차이 때문에 위의 계산식을 쓸 수 없을 경우 대체하여 사용.

	// case 3 : 가장 무식한 방법 모든 12개의 삼각면과 직선의 교차를 비교.
	// 추신 : 1, 2의 방법은 최대 3번의 시행으로 결과 값을 얻을 수 있다. P(3)

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
		AlignMinMax(fMin, fMax);		// 넣은 두 값을 비교해서 정렬한뒤, 돌려준다.

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
