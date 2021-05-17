#include "stdafx.h"
#include "cUIManager.h"


cUIManager* g_pUIManager = cUIManager::GetInstance();
char str[100] = "텍스트 인터페이스 출력 시험용";

cUIManager::cUIManager()
{
}


cUIManager::~cUIManager()
{
	for each(cUI* pUI in m_apUI)
	{
		SafeDelete(pUI);
	}
}

void cUIManager::Setup()
{
	m_pButton = new cUI_Button;
	m_pButton->Setup();

	cUI_TextBox* pUIT = new cUI_TextBox;
	pUIT->Setup();
	pUIT->SetText(str);
	pUIT->SetPosition(100, 100, 0);
	m_apUI.push_back(pUIT);

	cUI_Quest* pUIQ = new cUI_Quest;
	pUIQ->Setup();
	m_apUI.push_back(pUIQ);
}

void cUIManager::Update()
{
	for each(cUI* pUI in m_apUI)
	{
		pUI->Update();
	}

	// AutoReleaseUI에 등록된 비활성화된 UI처리
	for each(cUI* pUI in m_listAutoReleaseUI)
	{
		vector<cUI*>::iterator iterUI;
		for (iterUI = m_apUI.begin(); iterUI != m_apUI.end(); ++iterUI)
		{
			if (*iterUI == pUI)
			{
				m_apUI.erase(iterUI);
				break;
			}
		}
	}
}

void cUIManager::Render()
{
	for each(cUI* pUI in m_apUI)
	{
		pUI->Render();
	}
}

void cUIManager::DisableUI(cUI * pSender)
{
	m_listAutoReleaseUI.push_front(pSender);
}
