#include "stdafx.h"
#include "cUI_TextBox.h"


cUI_TextBox::cUI_TextBox()
	: m_szText(NULL)
	, m_colorText(D3DCOLOR_XRGB(0, 0, 0))
{
	m_pFont = g_pFontManager->GetFont("±Ã¼­Ã¼");
}


cUI_TextBox::~cUI_TextBox()
{
}

void cUI_TextBox::Render()
{
	cUI_Box::Render();

	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	if (m_pFont)
		m_pFont->DrawTextA(g_pSprite,
			m_szText,
			strlen(m_szText),
			&m_rcBox,
			DT_CENTER | DT_VCENTER,
			m_colorText);

	g_pSprite->End();
}

void cUI_TextBox::SetText(char * szText)
{
	m_szText = szText;
}
