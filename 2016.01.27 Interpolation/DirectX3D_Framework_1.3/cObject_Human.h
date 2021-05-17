#pragma once
#include "cObject.h"

#define ROUND_TIME	5.0f
#define SIDE_LENGTH	20.0f

class cObject_Human :
	public cObject
{
protected:
	vector<D3DXVECTOR3>		m_aWayPoint;
	float					m_fActionTime;
	DWORD					m_tEnd, m_tDelta;

public:
	cObject_Human();
	virtual ~cObject_Human();

	void Setup() override;
	void Update() override;
	void Render() override;
	void InterpolationPosition(OUT D3DXVECTOR3* pOut, const D3DXVECTOR3* pStartPos
		, const D3DXVECTOR3* pEndPos, const float ratio);
};

