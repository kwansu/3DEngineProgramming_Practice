#include "stdafx.h"
#include "cUI_Box.h"


cUI_Box::cUI_Box()
	: m_pTexture(NULL)
	, m_colorBox(D3DCOLOR_XRGB(255, 255, 255))
	, drag(false)
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
	size.cx = m_stImageInfo.Width;
	size.cy = m_stImageInfo.Height;
	SetScale(size.cx / m_rcBox.right, size.cy / m_rcBox.right, 1);
}

void cUI_Box::Update()
{
	cUI::Update();

	// 충돌체 위치 설정
	RECT rcColl(m_rcBox);
	rcColl.right *= m_matWorld._11;
	rcColl.bottom *= m_matWorld._22;
	OffsetRect(&rcColl, m_matWorld._41, m_matWorld._42);

	if (PtInRect(&rcColl, g_pInput->GetMousePos()))
	{
		if (g_pInput->IsKeyDown(VK_RBUTTON))
		{
			drag = true;
			g_pInput->KeyDown(VK_RBUTTON);
		}
	}

	if (g_pInput->IsKeyUp(VK_RBUTTON))
	{
		drag = false;
	}

	if (drag)
	{
		POINT ptDist = g_pInput->GetMouseInterval();

		if (g_pInput->IsKeyPress(VK_SPACE))
		{
			size.cx += ptDist.x;
			size.cy += ptDist.y;
			SetScale((float)size.cx / m_rcBox.right, (float)size.cy / m_rcBox.right, 1);
		}
		else
		{
			m_vPos.x += ptDist.x;
			m_vPos.y += ptDist.y;
		}
	}
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

void cUI_Box::SetBoxRect(DWORD withd, DWORD height)
{
	m_rcBox.right = withd;
	m_rcBox.bottom = height;
}

void cUI_Box::SetBoxColor(D3DCOLOR color)
{
	m_colorBox = color;
}

void cUI_Box::SetTexture(char * szTextureName)
{
	stTextureData textureData = g_pTexture->LoadTextureDate(szTextureName);
}

