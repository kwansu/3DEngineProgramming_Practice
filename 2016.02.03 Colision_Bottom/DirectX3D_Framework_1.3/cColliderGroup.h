#pragma once
#include "cReferrers.h"

class cColliderGroup : public cReferrers
{
private:
	vector<D3DXVECTOR3>	m_aVertex;

public:
	cColliderGroup();
	~cColliderGroup();
	void PushVertex(const D3DXVECTOR3* pVec);
};

