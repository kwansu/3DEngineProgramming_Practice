#include "stdafx.h"
#include "cUI_Box.h"


cUI_Box::cUI_Box()
	: m_pTexture(NULL)
	, m_colorBox(D3DCOLOR_XRGB(255, 255, 255))
{
	ZeroMemory(&m_stImageInfo, sizeof(D3DXIMAGE_INFO));
	SetRectEmpty(&m_rcBox);
}


cUI_Box::~cUI_Box()
{
	SafeRelease(m_pTexture);
}

void cUI_Box::Setup()
{
	stTextureData data(g_pTexture->LoadTextureDate("./UI/UI_Box.png"));

	m_pTexture = data.pTexture;
	m_stImageInfo = data.stTextureInfo;

	SetRect(&m_rcBox, 0, 0, m_stImageInfo.Width, m_stImageInfo.Height);
}

void cUI_Box::Render()
{
	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	g_pSprite->SetTransform(&m_matWorld);
	g_pSprite->Draw(m_pTexture,
		&m_rcBox,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		m_colorBox);

	g_pSprite->End();

	for each(auto pUI in m_apChild)
	{
		pUI->Render();
	}
}

