#pragma once

class cUI	:
	public cObject
{
protected:
	LPDIRECT3DTEXTURE9	m_pTexture;
	D3DXIMAGE_INFO		m_stII;
	RECT				m_rcSize;

public:
	cUI();
	~cUI();
	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

