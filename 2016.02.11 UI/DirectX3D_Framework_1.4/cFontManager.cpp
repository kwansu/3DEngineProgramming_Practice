#include "stdafx.h"
#include "cFontManager.h"


cFontManager* g_pFontManager = cFontManager::GetInstance();

cFontManager::cFontManager()
{
}


cFontManager::~cFontManager()
{
}

LPD3DXFONT cFontManager::GetFont(string strFontName)
{
	map<string, LPD3DXFONT>::iterator iterFont;

	iterFont = m_mapFont.find(strFontName);

	if (iterFont == m_mapFont.end())
		return NULL;

	return iterFont->second;
}

void cFontManager::Setup()
{
	LPD3DXFONT pFont = NULL;

	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 25;
	fd.Width = 12;
	fd.Weight = FW_NORMAL;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	//strcpy_s(fd.FaceName, "±º∏≤√º");	//±€≤√ Ω∫≈∏¿œ
	//AddFontResource("umberto.ttf");
	strcpy_s(fd.FaceName, "±√º≠√º");
	D3DXCreateFontIndirect(g_pDevice, &fd, &pFont);

	m_mapFont.insert(pair<string, LPD3DXFONT>("±√º≠√º", pFont));
}

void cFontManager::Release()
{
	for each(auto pmap in m_mapFont)
	{
		SafeRelease(pmap.second);
	}
}
