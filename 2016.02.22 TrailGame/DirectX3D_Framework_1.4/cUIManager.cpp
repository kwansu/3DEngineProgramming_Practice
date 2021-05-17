#include "stdafx.h"
#include "cUIManager.h"


cUIManager* g_pUIManager = cUIManager::GetInstance();
char str[100] = "�ؽ�Ʈ �������̽� ��� �����";

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
	//cUI_Quest* pUIQ = new cUI_Quest;
	//pUIQ->Setup();
	//m_apUI.push_back(pUIQ);
}

void cUIManager::Update()
{
	for each(cUI* pUI in m_apUI)
	{
		pUI->Update();
	}

	// AutoReleaseUI�� ��ϵ� ��Ȱ��ȭ�� UIó��
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
