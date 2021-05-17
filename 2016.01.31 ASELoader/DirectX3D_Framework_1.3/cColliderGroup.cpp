#include "stdafx.h"
#include "cColliderGroup.h"


cColliderGroup::cColliderGroup()
{
}


cColliderGroup::~cColliderGroup()
{
	cReferrers::Release();
}


void cColliderGroup::PushVertex(const D3DXVECTOR3* pVec)
{
	m_aVertex.push_back(*pVec);
}
