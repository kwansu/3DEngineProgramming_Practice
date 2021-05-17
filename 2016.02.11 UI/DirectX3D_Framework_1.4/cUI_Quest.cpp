#include "stdafx.h"
#include "cUI_Quest.h"


cUI_Quest::cUI_Quest()
	: m_bDrag(NULL)
{
}


cUI_Quest::~cUI_Quest()
{
}

void cUI_Quest::Setup()
{
	// �ڽ� UI �߰�
	cUI_Button* pUIB = new cUI_Button;
	pUIB->Setup();
	pUIB->SetParent(this);
	pUIB->SetPosition(200, 200, 0);
	m_apChild.push_back(pUIB);

	pUIB = new cUI_Button;
	pUIB->Setup();
	pUIB->SetParent(this);
	pUIB->SetScale(6, 1, 1);
	m_apChild.push_back(pUIB);


	// �ؽ�Ʈ �ε�
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

void cUI_Quest::Event(cUI * pGenerator)
{
	// �ݱ� ��ư
	if (pGenerator == m_apChild[0])
	{
		g_pUIManager->DisableUI(this);
	}

	if (pGenerator == m_apChild[1])
	{
		m_bDrag = true;
	}
}
