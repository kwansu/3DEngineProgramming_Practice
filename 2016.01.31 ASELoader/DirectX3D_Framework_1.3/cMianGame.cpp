#include "stdafx.h"
#include "cMianGame.h"


cMianGame::cMianGame()
: m_pStructure(NULL)
{
}


cMianGame::~cMianGame()
{
	// ���� ���� ������ ����̽� ���� ��
	// ��ü�� ����� �Ҹ�Ǿ����� Ȯ���Ѵ�.
	cDeviceManager::GetInstance()->Release();
	g_pRefCounter->Destroy();
}


void cMianGame::Initialize()
{
	g_pResourceManager->LoadObjFile("map.obj", true);
	g_pResourceManager->LoadObjFile("map_surface.obj", false);

	m_pGrid = new cGrid;
	m_pStructure = new cObject_Structure;
	m_pHuman = new cObject_ThirdMan;
	m_pHuman2 = new cObject_SixMan;
	m_pWoman = new cObject_Woman;

	g_pCamera->Setup();
	m_pGrid->Setup();
	m_pHuman->Setup();
	m_pHuman2->Setup();


	m_pLoader = new ASELoader;
	m_pLoader->LoadASE("./woman/woman_01_all.ASE");

	m_pWoman->m_pRoot = m_pLoader->m_pRoot;

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
	SafeDelete(m_pStructure);
	SafeDelete(m_pHuman);
	SafeDelete(m_pHuman2);
	SafeDelete(m_pWoman);

	m_pLoader->Release();
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
	g_pCamera->Update();
	m_pHuman->Update();
	m_pHuman2->Update();
}


void cMianGame::Render()
{
	g_pDevice->Clear(NULL, NULL
		, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER
		, D3DCOLOR_XRGB(190, 190, 190)
		, 1.0f, 0);
	g_pDevice->BeginScene();

	// ������ :
	m_pGrid->Render();
	//m_pStructure->Render();
	m_pHuman->Render();
	m_pHuman2->Render();
	m_pWoman->Render();

	// ������
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