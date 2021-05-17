#include "stdafx.h"
#include "cUI_Button.h"


cUI_Button::cUI_Button()
	: m_bClicked(false)
{
}


cUI_Button::~cUI_Button()
{
}

void cUI_Button::Update()
{
	cUI_Box::Update();

	// 충돌체 위치 설정
	RECT rcColl(m_rcBox);
	rcColl.right *= m_matWorld._11;
	rcColl.bottom *= m_matWorld._22;
	OffsetRect(&rcColl, m_matWorld._41, m_matWorld._42);

	if (PtInRect(&rcColl, g_pInput->GetMousePos()))
	{
		if (g_pInput->IsKeyDown(VK_LBUTTON))
		{
			m_bClicked = true;
			m_pParent->Event(this, true);
			g_pInput->KeyDown(VK_LBUTTON);
		}
		
		if (g_pInput->IsKeyUp(VK_LBUTTON))
		{
			m_bClicked = false;
			m_pParent->Event(this, false);
		}

		if (m_bClicked)
			m_colorBox = D3DCOLOR_XRGB(80, 200, 255);
		else
			m_colorBox = D3DCOLOR_XRGB(200, 200, 255);
	}
	else
	{
		m_bClicked = false;
		m_colorBox = D3DCOLOR_XRGB(255, 255, 255);
	}
}
