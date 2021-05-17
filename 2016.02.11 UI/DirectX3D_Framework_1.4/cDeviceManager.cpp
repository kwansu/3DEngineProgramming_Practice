#include "stdafx.h"
#include "cDeviceManager.h"


LPDIRECT3DDEVICE9 g_pDevice = NULL;

cDeviceManager::cDeviceManager()
	: m_pD3D(NULL)
	, m_pD3DDevice(NULL)
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9	stCaps;
	int			nVertexProcessing;
	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stCaps);

	if (stCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS	stD3DPP;
	ZeroMemory(&stD3DPP, sizeof(D3DPRESENT_PARAMETERS));
	stD3DPP.AutoDepthStencilFormat = D3DFMT_D24S8;
	stD3DPP.BackBufferFormat = D3DFMT_UNKNOWN;
	stD3DPP.EnableAutoDepthStencil = TRUE;
	stD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	stD3DPP.Windowed = TRUE;

	m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		g_hWnd, nVertexProcessing, &stD3DPP, &m_pD3DDevice);
}


cDeviceManager::~cDeviceManager()
{
}

LPDIRECT3DDEVICE9 cDeviceManager::GetDivece()
{
	return m_pD3DDevice;
}

void cDeviceManager::Release()
{
	SafeRelease(m_pD3D);
	ULONG ul = m_pD3DDevice->Release();
	assert(ul == 0 && "디바이스를 이용하여 생성된 객채 중 해제되지 않은 자원이 있습니다.");
}
