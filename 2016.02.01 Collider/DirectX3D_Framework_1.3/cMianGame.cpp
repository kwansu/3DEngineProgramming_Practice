#include "stdafx.h"
#include "cMianGame.h"


cMianGame::cMianGame()
	: m_pGrid(NULL)
	, m_pLoader(NULL)
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

	m_pGrid = new cGrid;
	g_pCamera->Setup();
	m_pGrid->Setup();

	m_pLoader = new ASELoader;
	m_pLoader->LoadASE("./woman/woman_01_all.ASE");

	cObject* pObject = new cObject_ThirdMan;
	pObject->Setup();
	m_apObjects.push_back(pObject);

	pObject = new cObject_SixMan;
	pObject->Setup();
	m_apObjects.push_back(pObject);

	//pObject = new cObject_Box;
	//pObject->Setup();
	//m_apObjects.push_back(pObject);

	cObject_Woman* pWoman = new cObject_Woman;
	pWoman->m_pRoot = m_pLoader->m_pRoot;
	m_apObjects.push_back(pWoman);

	ZeroMemory(&m_light, sizeof(D3DLIGHT9));
	m_light.Type = D3DLIGHT_DIRECTIONAL;
	m_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_light.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetLight(0, &m_light);
	g_pDevice->LightEnable(0, true);
}


void cMianGame::Release()
{
	for each(auto pObject in m_apObjects)
	{
		SafeDelete(pObject);
	}

	m_pLoader->Release();
	g_pResourceManager->Destroy();
}


void cMianGame::Run()
{
	g_pTimeManager->WaitFrameTime();

	Update();
	Render();
}


void cMianGame::Update()
{
	g_pInput->Update();
	g_pCamera->Update();

	for each(auto pObject in m_apObjects)
	{
		pObject->Update();
	}
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
	for each(auto pObject in m_apObjects)
	{
		pObject->Render();
	}

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
