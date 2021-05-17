#include "stdafx.h"
#include "cUI_QuestWindow.h"


cUI_QuestWindow::cUI_QuestWindow()
{
	m_pClose = new cUI_Button;
	m_pClose->Setup();
	m_pClose->SetPosition(240, 0, 0);

	m_pYes = new cUI_Button;
	m_pYes->Setup();
	m_pYes->SetPosition(60, 250, 0);

	m_pNo = new cUI_Button;
	m_pNo->Setup();
	m_pNo->SetPosition(200, 250, 0);

	D3DXCreateTextureFromFileEx(
		g_pDevice,
		"UI_Quest.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,//D3DCOLOR_XRGB(255, 255, 255),
		&m_stII,
		NULL,
		&m_pTexture);

	SetRect(&m_rcSize, 0, 0, m_stII.Width, m_stII.Height);
}


cUI_QuestWindow::~cUI_QuestWindow()
{
	SafeDelete(m_pClose);
	SafeDelete(m_pYes);
	SafeDelete(m_pNo);
}

void cUI_QuestWindow::Update()
{

	m_pClose->Update();
}

void cUI_QuestWindow::Render()
{
	g_pSprite->SetTransform(&m_matWolrd);
	g_pSprite->Draw(m_pTexture,
		&m_rcSize,
		&D3DXVECTOR3(0, 0, 0),
		&m_vPos,
		D3DCOLOR_XRGB(255, 255, 255));

	m_pClose->Render();
	m_pYes->Render();
	m_pNo->Render();
}
