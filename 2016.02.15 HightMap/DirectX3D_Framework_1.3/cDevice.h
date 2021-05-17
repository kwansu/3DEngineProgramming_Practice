#pragma once

class cDevice
	: public cSingetone<cDevice>
{
private:
	LPDIRECT3D9			m_pDirect3D;
	LPDIRECT3DDEVICE9	m_pDirect3DDevice;

private:
	cDevice();
public:
	~cDevice();
	void Release();
};

