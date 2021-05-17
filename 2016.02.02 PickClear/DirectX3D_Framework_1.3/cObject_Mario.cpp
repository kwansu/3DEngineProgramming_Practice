#include "stdafx.h"
#include "cObject_Mario.h"


cObject_Mario::cObject_Mario()
	: m_pChildHead(NULL), m_pChildLArm(NULL)
	, m_pChildRArm(NULL), m_pChildLLeg(NULL)
	, m_pChildRLeg(NULL)
{
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, D3DXToRadian(60));
	D3DXVECTOR3 wayPos(0, 0, SIDE_LENGTH);

	for (int i = 0; i < 7; ++i)
	{
		m_aWayPoint.push_back(wayPos);
		D3DXVec3TransformCoord(&wayPos, &wayPos, &matR);
	}

	m_pColliderS = new cCollider_Sphere;
}


cObject_Mario::~cObject_Mario()
{
	SafeDelete(m_pChildHead);
	SafeDelete(m_pChildLArm);
	SafeDelete(m_pChildRArm);
	SafeDelete(m_pChildLLeg);
	SafeDelete(m_pChildRLeg);
}


void cObject_Mario::Setup()
{
	SetLocalSize(2.1f, 3.1f, 1);

	m_pChildHead = new cObject_Mario_Head;
	m_pChildHead->SetLocalSize(2.1f, 2.f, 2.f);
	m_pChildHead->Setup(&m_matWolrd, 0, 7.1f, 0);

	m_pChildLArm = new cObject_Limbs(false);
	m_pChildLArm->SetLocalSize(1, 3.2f, 1);
	m_pChildLArm->Setup(&m_matWolrd, 3.2f, 3.1f, 0);

	m_pChildRArm = new cObject_Limbs(true);
	m_pChildRArm->SetLocalSize(1, 3.2f, 1);
	m_pChildRArm->Setup(&m_matWolrd,-3.2f, 3.1f, 0);

	m_pChildLLeg = new cObject_Limbs(false);
	m_pChildLLeg->SetLocalSize(1, 3.2f, 1);
	m_pChildLLeg->Setup(&m_matWolrd, 1.1f,-3.2f, 0);
			
	m_pChildRLeg = new cObject_Limbs(true);
	m_pChildRLeg->SetLocalSize(1, 3.2f, 1);
	m_pChildRLeg->Setup(&m_matWolrd,-1.1f,-3.2f, 0);

	//m_pChildRArm->SetRotation(-70, 0, 0);
	UpdateWorld();
}


void cObject_Mario::Update()
{
	m_pChildLArm->Walking();
	m_pChildRArm->Walking();
	m_pChildLLeg->Walking();
	m_pChildRLeg->Walking();


	UpdateWorld();
	m_pChildHead->Update();
	m_pChildLArm->Update();
	m_pChildRArm->Update();
	m_pChildLLeg->Update();
	m_pChildRLeg->Update();

	m_pColliderS->m_vOrigin = m_vPos;
}


void cObject_Mario::Render()
{
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matScale);

	g_pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 6
		, &m_aWayPoint[0], sizeof(D3DXVECTOR3));

	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWolrd);
	m_pColliderS->Render();

	m_pChildHead->Render();
	m_pChildLArm->Render();
	m_pChildLLeg->Render();
	m_pChildRArm->Render();
	m_pChildRLeg->Render();

	cObject_Cube::Render();
}

void cObject_Mario::InterpolationPosition(OUT D3DXVECTOR3* pOut, const D3DXVECTOR3* pStartPos
	, const D3DXVECTOR3* pEndPos, const float ratio)
{
	*pOut = *pStartPos + ratio * (*pEndPos - *pStartPos);
}
