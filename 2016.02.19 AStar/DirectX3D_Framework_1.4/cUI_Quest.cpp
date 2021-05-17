#include "stdafx.h"
#include "cUI_Quest.h"


char szQuest[64] = "퀘스트 수락?";
char szQuestY[64] = "수락";
char szQuestN[64] = "거절";

cUI_Quest::cUI_Quest()
	: m_bDrag(NULL)
{
}


cUI_Quest::~cUI_Quest()
{
}

void cUI_Quest::Setup()
{
	// 자식 UI 추가
	cUI_Button* pUIB = new cUI_Button;
	pUIB->Setup();
	pUIB->SetParent(this);
	pUIB->SetScale(6, 1, 1);
	m_apChild.push_back(pUIB);

	pUIB = new cUI_Button;
	pUIB->Setup();
	pUIB->SetParent(this);
	pUIB->SetPosition(100, 200, 0);
	m_apChild.push_back(pUIB);

	pUIB = new cUI_Button;
	pUIB->Setup();
	pUIB->SetParent(this);
	pUIB->SetPosition(200, 200, 0);
	m_apChild.push_back(pUIB);

	pUIB = new cUI_Button;
	pUIB->Setup();
	pUIB->SetParent(this);
	pUIB->SetPosition(300, 200, 0);
	m_apChild.push_back(pUIB);

	cUI_TextBox* pUIT = new cUI_TextBox;
	pUIT->Setup();
	pUIT->SetText(szQuest);
	pUIT->SetParent(this);
	pUIT->SetScale(3, 1, 1);
	pUIT->SetPosition(200, 100, 0);
	m_apChild.push_back(pUIT);

	// 텍스쳐 로드
	stTextureData data(g_pTexture->LoadTextureDate("./UI/UI_Quest.png"));

	m_pTexture = data.pTexture;
	m_stImageInfo = data.stTextureInfo;

	SetRect(&m_rcBox, 0, 0, m_stImageInfo.Width, m_stImageInfo.Height);
}

void cUI_Quest::Update()
{
	if (g_pInput->IsKeyPress(VK_LBUTTON))
	{
		if (m_bDrag)
		{
			POINT ptDist = g_pInput->GetMouseInterval();
			m_vPos.x += ptDist.x;
			m_vPos.y += ptDist.y;
		}
	}
	else
		m_bDrag = false;

	cUI::Update();
}

void cUI_Quest::Event(cUI * pGenerator, bool bDown)
{
	// 드래그 버튼
	if (pGenerator == m_apChild[0])
	{
		m_bDrag = bDown;
	}

	// 닫기 버튼
	if (pGenerator == m_apChild[1])
	{
		if(!bDown)
			g_pUIManager->DisableUI(this);
	}

	// 확인 버튼
	if (pGenerator == m_apChild[2])
	{
		if (!bDown)
			dynamic_cast<cUI_TextBox*>(m_apChild[4])->SetText(szQuestY);
	}

	// 취소 버튼
	if (pGenerator == m_apChild[3])
	{
		if (!bDown)
			dynamic_cast<cUI_TextBox*>(m_apChild[4])->SetText(szQuestN);
	}
}
