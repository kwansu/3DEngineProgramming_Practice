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
