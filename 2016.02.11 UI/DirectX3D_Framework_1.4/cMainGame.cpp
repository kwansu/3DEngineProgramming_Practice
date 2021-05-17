#include "stdafx.h"
#include "cMainGame.h"


cMainGame::cMainGame()
{
}


cMainGame::~cMainGame()
{
	SafeRelease(g_pDevice);
}

void cMainGame::Release()
{
	SafeRelease(g_pSprite);
	SafeRelease(g_pFontManager);
	SafeRelease(g_pTexture);
}

void cMainGame::Initialize()
{
	g_pGameObjects->Setup();
	g_pFontManager->Setup();
	g_pUIManager->Setup();

	D3DXCreateSprite(g_pDevice, &g_pSprite);
}

void cMainGame::Run()
{
	g_pTimeManger->Update();

	Update();
	Render();

	g_pInput->Update();
}

void cMainGame::Update()
{
	g_pUIManager->Update();
	g_pGameObjects->Update();
}

void cMainGame::Render()
{
	g_pDevice->Clear(NULL, NULL
		, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER
		, D3DCOLOR_XRGB(190, 190, 190)
		, 1.0f, 0);
	g_pDevice->BeginScene();

	// 오브젝트 랜더링
	g_pGameObjects->Render();

	// 유저인터페이스 랜더링
	g_pUIManager->Render();

	// 랜더링 종료
	g_pDevice->EndScene();
	g_pDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::MessageHandler(HWND hWnd, UINT iMsg, WPARAM wp, LPARAM lp)
{
	switch (iMsg)
	{
	case WM_KEYDOWN:
		g_pInput->KeyDown(wp);
		break;
	case WM_KEYUP:
		g_pInput->KeyUp(wp);
		break;
	//case WM_MOUSEMOVE:
	//	g_pInput->SetMouse(LOWORD(lp), HIWORD(lp));
	//	break;
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
