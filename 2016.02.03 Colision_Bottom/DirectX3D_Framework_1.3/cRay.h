#pragma once

class cRay
{
public:
	D3DXVECTOR3		m_vDir;		// ��������
	D3DXVECTOR3		m_vOri;		// ��������
	float			m_fDist;

public:
	cRay();
	cRay(D3DXVECTOR3 vDir, D3DXVECTOR3 vOri = D3DXVECTOR3(0, 0, 0));
	~cRay();
	void Render();
};

