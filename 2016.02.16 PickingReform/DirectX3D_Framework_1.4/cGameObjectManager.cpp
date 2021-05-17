#include "stdafx.h"
#include "cGameObjectManager.h"


cGameObjectManager* g_pGameObjects = cGameObjectManager::GetInstance();

cGameObjectManager::cGameObjectManager()
	: m_pGrid(NULL)
{
}


cGameObjectManager::~cGameObjectManager()
{
	for each (cGameObject* pObj in m_vecpGameObjects)
	{
		SafeDelete(pObj);
	}

	SafeDelete(m_pGrid);
}

void cGameObjectManager::Setup()
{
	g_pCamera->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	cGameObject* pObject = new cObj_Sphere;
	pObject->Setup();
	m_vecpGameObjects.push_back(pObject);

	pObject = new cObj_Sphere;
	pObject->Setup();
	pObject->SetPosition(5, 0, 5);
	m_vecpGameObjects.push_back(pObject);

	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	//g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}

void cGameObjectManager::Update()
{
	g_pCamera->Update();

	for each (cGameObject* pObj in m_vecpGameObjects)
	{
		pObj->Update();
	}

	dynamic_cast<cObj_Sphere*>(m_vecpGameObjects[0])->IsCollision(dynamic_cast<cObj_Sphere*>(m_vecpGameObjects[1]));
}

void cGameObjectManager::Render()
{
	m_pGrid->Render();

	for each (cGameObject* pObj in m_vecpGameObjects)
	{
		pObj->Render();
	}
}
