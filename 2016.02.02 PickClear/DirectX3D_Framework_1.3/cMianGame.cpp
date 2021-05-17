#include "stdafx.h"
#include "cMianGame.h"


cMianGame::cMianGame()
{
}


cMianGame::~cMianGame()
{
	// 메인 게임 해제시 디바이스 해제 및
	// 객체가 제대로 소멸되었는지 확인한다.
	cDeviceManager::GetInstance()->Release();
	g_pRefCounter->Destroy();
}


void cMianGame::Initialize()
{
	g_pResourceManager->LoadObjFile("map.obj", true);
	g_pResourceManager->LoadObjFile("map_surface.obj", false);

	g_pCamera->Setup();
	m_pGrid = new cGrid;
	m_pGrid->Setup();

	ZeroMemory(&m_light, sizeof(D3DLIGHT9));
	m_light.Type = D3DLIGHT_DIRECTIONAL;
	m_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_light.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_light.Direction = D3DXVECTOR3(-1, -1, 0); 

	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetLight(0, &m_light);
	g_pDevice->LightEnable(0, true);

	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
}


void cMianGame::Release()
{
	g_pObjects->Release();
	g_pResourceManager->Destroy();
}


void cMianGame::Run()
{
	g_pTimeManager->WaitFrameTime();

	Update();
	Render();

	g_pTimeManager->SetEndTime();
}


void cMianGame::Update()
{
	g_pInput->Update();
	g_pObjects->Update();
}


void cMianGame::Render()
{
	g_pDevice->Clear(NULL, NULL
		, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER
		, D3DCOLOR_XRGB(190, 190, 190)
		, 1.0f, 0);
	g_pDevice->BeginScene();

	// 랜더링 :
	m_pGrid->Render();
	g_pObjects->Render();


	// 마무리
	g_pDevice->EndScene();
	g_pDevice->Present(NULL, NULL, NULL, NULL);
}


void cMianGame::MessageHandler(HWND hWnd, UINT iMsg, WPARAM wp, LPARAM lp)
{
	switch (iMsg)
	{
	case WM_KEYDOWN:
		g_pInput->KeyDown(wp);
		break;
	case WM_KEYUP:
		g_pInput->KeyUp(wp);
		break;
	case WM_MOUSEMOVE:
		g_pInput->SetMouse(LOWORD(lp), HIWORD(lp));
		break;
	case WM_LBUTTONDOWN:
		g_pInput->KeyDown(VK_LBUTTON);
		SetCapture(g_hWnd);
		break;
	case WM_LBUTTONUP:
		g_pInput->KeyUp(VK_LBUTTON);
		ReleaseCapture();
		break;
	case WM_RBUTTONDOWN:
		g_pInput->KeyDown(VK_RBUTTON);
		SetCapture(g_hWnd);
		break;
	case WM_RBUTTONUP:
		g_pInput->KeyUp(VK_RBUTTON);
		ReleaseCapture();
		break;
	case WM_MOUSEWHEEL:
		g_pInput->AddWheel(HIWORD(wp));
		break;
	}
}
