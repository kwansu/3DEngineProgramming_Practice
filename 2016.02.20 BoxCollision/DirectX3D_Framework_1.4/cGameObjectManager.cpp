#include "stdafx.h"
#include "cGameObjectManager.h"


cGameObjectManager* g_pGameObjects = cGameObjectManager::GetInstance();

cGameObjectManager::cGameObjectManager()
	: m_pGrid(NULL)
{
}


cGameObjectManager::~cGameObjectManager()
{
}

void cGameObjectManager::Setup()
{
	g_pCamera->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	// 오브젝트 생성
	cGameObject* pObject = new cObj_Sphere;
	pObject->Setup();
	m_vecpGameObjects.push_back(pObject);

	pObject = new cObj_Box;
	pObject->Setup();
	pObject->SetPosition(5, 0, 5);
	m_vecpGameObjects.push_back(pObject);

	// light Setup
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));
	m_light.Type = D3DLIGHT_DIRECTIONAL;
	m_light.Diffuse = m_light.Ambient = D3DXCOLOR(1, 1, 1, 1);
	m_light.Direction = D3DXVECTOR3(-0.7, -1, 0.5f);
	g_pDevice->SetLight(0, &m_light);
	g_pDevice->LightEnable(0, true);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	//g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}

void cGameObjectManager::Relese()
{
	for each (cGameObject* pObj in m_vecpGameObjects)
	{
		SafeDelete(pObj);
	}

	SafeDelete(m_pGrid);
}

void cGameObjectManager::Update()
{
	g_pCamera->Update();

	for each (cGameObject* pObj in m_vecpGameObjects)
	{
		pObj->Update();
	}
}

void cGameObjectManager::Render()
{
	m_pGrid->Render();

	for each (cGameObject* pObj in m_vecpGameObjects)
	{
		pObj->Render();
	}
}

