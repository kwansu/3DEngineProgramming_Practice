#include "stdafx.h"
#include "cObject_Human.h"


cObject_Human::cObject_Human()
{
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, D3DXToRadian(60));
	D3DXVECTOR3 wayPos(0, 0, SIDE_LENGTH);

	for (int i = 0; i < 7; ++i)
	{
		m_aWayPoint.push_back(wayPos);
		D3DXVec3TransformCoord(&wayPos, &wayPos, &matR);
	}
}


cObject_Human::~cObject_Human()
{
}


void cObject_Human::Setup()
{
}


void cObject_Human::Update()
{
	UpdateWorld();
}


void cObject_Human::Render()
{
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matScale);

	g_pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 6
		, &m_aWayPoint[0], sizeof(D3DXVECTOR3));
}


void cObject_Human::InterpolationPosition(OUT D3DXVECTOR3* pOut, const D3DXVECTOR3* pStartPos
	, const D3DXVECTOR3* pEndPos, const float ratio)
{
	*pOut = *pStartPos + ratio * (*pEndPos - *pStartPos);
}
