#include "stdafx.h"
#include "cObjectManager.h"


cObjectManager::cObjectManager()
	: m_pPicked(NULL)
{
	m_pWoman = new cObject_Woman;

	m_pWoman2 = new cObject_Woman;
	m_pWoman2->SetPosition(5, 0, 5);

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
	SafeDelete(m_pWoman2);
	SafeDelete(m_pMouseMark);
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
	m_pWoman2->Update();

	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
	{
		if (m_pWoman->IsPicked(m_vPos, m_vDir))
		{
			m_pPicked = m_pWoman;
			m_pWoman2->m_bPicked = false;
		}
		else if (m_pWoman2->IsPicked(m_vPos, m_vDir))
		{
			m_pPicked = m_pWoman2;
			m_pWoman->m_bPicked = false;
		}
		else if(m_pPicked)
			m_pPicked->UpdatePicked(m_vPos, m_vDir);
	}
}


void cObjectManager::Render()
{
	for each (auto pObject in m_apObjects)
	{
		pObject->Render();
	}

	m_pWoman->Render();
	m_pWoman2->Render();

	m_pMouseMark->Render();
}


void cObjectManager::UpdatePickedObject()
{
	
}
