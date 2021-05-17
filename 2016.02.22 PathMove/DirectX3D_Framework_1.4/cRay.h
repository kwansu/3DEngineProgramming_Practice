#pragma once
#include "iCollider.h"
#include "stdCollider.h"

class cRay :
	public iCollider
{
public:
	D3DXVECTOR3		m_vOri;
	D3DXVECTOR3		m_vDir;

public:
	cRay();
	cRay(D3DXVECTOR3 vOri, D3DXVECTOR3 vDir);
	~cRay();

	void SetRay(const D3DXVECTOR3 &vOri, const D3DXVECTOR3 &vDir);
	void Transform(const D3DXMATRIXA16* pmatWorld);
	bool IsCollisionAsPlane(OUT D3DXVECTOR3* pvPos, const stPlane & plane) const;

	void DebugRender();
};

