#pragma once
#include "cUI_Box.h"

class cUI_TextBox :
	public cUI_Box
{
private:
	char*		m_szText;
	LPD3DXFONT	m_pFont;
	D3DCOLOR	m_colorText;

public:
	cUI_TextBox();
	~cUI_TextBox();

	void Render() override;
	
	void SetText(char* szText);
};

