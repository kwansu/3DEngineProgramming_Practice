#pragma once

class cRay
{
public:
	D3DXVECTOR3		m_vDir;		// 광선방향
	D3DXVECTOR3		m_vOri;		// 시작지점
	float			m_fDist;

public:
	cRay();
	cRay(D3DXVECTOR3 vDir, D3DXVECTOR3 vOri = D3DXVECTOR3(0, 0, 0));
	~cRay();
	void Render();
};

