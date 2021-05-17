#include "stdafx.h"
#include "cRay.h"


cRay::cRay()
	: m_vDir(0, 0, 1)
	, m_vOri(0, 0, 0)
	, m_fDist(0)
{
}


cRay::cRay(D3DXVECTOR3 vDir, D3DXVECTOR3 vOri)
	: m_vDir(vDir)
	, m_vOri(vOri)
	, m_fDist(0)
{
}


cRay::~cRay()
{
}


void cRay::Render()
{
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	D3DXVECTOR3 vertexLine[2] = { m_vOri, m_vOri + m_vDir*1000 };
	g_pDevice->SetFVF(D3DFVF_XYZ);
	g_pDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP
		, 1
		, vertexLine
		, sizeof(D3DXVECTOR3));
}
