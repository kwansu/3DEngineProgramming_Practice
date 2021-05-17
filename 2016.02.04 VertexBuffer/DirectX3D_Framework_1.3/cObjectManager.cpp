#include "stdafx.h"
#include "cObjectManager.h"


cObjectManager::cObjectManager()
{
	cObject* pObject = new cObject_ThirdMan;
	pObject->Setup();
	m_apObjects.push_back(pObject);

	pObject = new cObject_SixMan;
	pObject->Setup();
	m_apObjects.push_back(pObject);

	pObject = new cObject_LocalFrame;
	pObject->Setup();
	m_apObjects.push_back(pObject);

	m_pWoman = new cObject_Woman;

	m_pMouseMark = new cObject_MouseMark;

	g_pResourceManager->LoadObjFile("Map.obj", true);

	m_pMap = new cMap;

	g_pResourceManager->LoadObjFile("map_surface.obj", false);

	m_pWoman->m_pTerrain = g_pColliderTerrain;

	g_pCamera->SetTarget(&m_pWoman->m_vPos);


}


cObjectManager::~cObjectManager()
{
}


void cObjectManager::Release()
{
	for each (auto pObject in m_apObjects)
	{
		SafeDelete(pObject);
	}

	SafeDelete(m_pWoman);
	SafeDelete(m_pMouseMark);
	g_pResourceManager->Destroy();
}


void cObjectManager::Update()
{
	g_pCamera->Update();
	g_pCamera->GetMouseLine(&m_vDir, &m_vPos);
	
	m_pMouseMark->SetMark(&m_vDir, &m_vPos);

	for each (auto pObject in m_apObjects)
	{
		pObject->Update();
	}

	m_pWoman->Update();


	//if (m_apObjects[0]->m_pColliderS->IsCollisionSphere(
	//	m_apObjects[1]->m_pColliderS))
	//{
	//	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//}
	//else
	//{
	//	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//}
}


void cObjectManager::Render()
{
	for each (auto pObject in m_apObjects)
	{
		pObject->Render();
	}
	m_pWoman->Render();
	m_pMouseMark->Render();
	m_pMap->Render();
	//g_pColliderTerrain->Render();
}


void cObjectManager::UpdatePickedObject()
{
	
}
