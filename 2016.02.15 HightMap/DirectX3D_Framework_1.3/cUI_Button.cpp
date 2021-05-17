#include "stdafx.h"
#include "cUI_Button.h"


cUI_Button::cUI_Button()
{
}


cUI_Button::~cUI_Button()
{
}

void cUI_Button::Setup()
{
	D3DXCreateTextureFromFileEx(
		g_pDevice,
		"UI_Button.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_stII,
		NULL,
		&m_pTexture);

	SetRect(&m_rcSize, 0, 0, m_stII.Width, m_stII.Height);
}

void cUI_Button::Update()
{
}

void cUI_Button::Render()
{
	g_pSprite->Draw(m_pTexture,
		&m_rcSize,
		&D3DXVECTOR3(0, 0, 0),
		&m_vPos,
		D3DCOLOR_XRGB(255, 255, 255));
}
