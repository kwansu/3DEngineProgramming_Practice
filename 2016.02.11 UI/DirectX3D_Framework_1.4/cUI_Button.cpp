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
	cUI::Update();

	// 충돌체 위치 설정
	RECT rcColl(m_rcBox);
	rcColl.right *= m_matWorld._11;
	rcColl.bottom *= m_matWorld._22;
	OffsetRect(&rcColl, m_matWorld._41, m_matWorld._42);

	if (PtInRect(&rcColl, g_pInput->GetMousePos()))
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8001)
		{
			m_bClicked = true;
			m_pParent->Event(this);
		}
		else if (m_bClicked)
		{
			m_pParent->Event(this);
			m_bClicked = false;
		}

		m_colorBox = D3DCOLOR_XRGB(100, 200, 255);
	}
	else
	{
		m_bClicked = false;
		m_colorBox = D3DCOLOR_XRGB(200, 255, 255);
	}
}
