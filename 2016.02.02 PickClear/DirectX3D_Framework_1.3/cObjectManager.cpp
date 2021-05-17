#include "stdafx.h"
#include "cObjectManager.h"


cObjectManager::cObjectManager()
	: m_pLoader(NULL)
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

	m_pLoader = new ASELoader;
	m_pLoader->LoadASE("./woman/woman_01_all.ASE");

	m_pWoman = new cObject_Woman;
	m_pWoman->m_pRoot = m_pLoader->m_pRoot;

	m_pMouseMark = new cObject_MouseMark;
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

	m_pLoader->Release();
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

	if (m_apObjects[0]->m_pColliderS->IsCollisionSphere(
		m_apObjects[1]->m_pColliderS))
	{
		g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else
	{
		g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}


void cObjectManager::Render()
{
	for each (auto pObject in m_apObjects)
	{
		pObject->Render();
	}
	m_pWoman->Render();
	m_pMouseMark->Render();
}


void cObjectManager::UpdatePickedObject()
{
	
}
