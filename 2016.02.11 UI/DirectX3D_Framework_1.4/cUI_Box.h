#pragma once
#include "cUI.h"

class cUI_Box :
	public cUI
{
protected:
	LPDIRECT3DTEXTURE9	m_pTexture;
	D3DXIMAGE_INFO		m_stImageInfo;
	D3DCOLOR			m_colorBox;
	RECT				m_rcBox;

public:
	cUI_Box();
	~cUI_Box();

	virtual void Setup() override;
	virtual void Render() override;
};

