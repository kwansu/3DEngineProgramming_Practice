#pragma once

class cDeviceManager
{
	SINGLETONE(cDeviceManager);
private:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pD3DDevice;

public:
	LPDIRECT3DDEVICE9 GetDevice();
	void Release();
};

// 빈번한 호출로 인한 오버헤드를 줄이기위해
// 매크로대신 전역변수로 선언함.
extern LPDIRECT3DDEVICE9 g_pDevice;

