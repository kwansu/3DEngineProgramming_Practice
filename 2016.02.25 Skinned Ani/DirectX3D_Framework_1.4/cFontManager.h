#pragma once

enum eFontType
{

};

class cFontManager
{
	SINGLETONE(cFontManager);

private:
	map<string, LPD3DXFONT>	m_mapFont;

public:
	void Setup();
	void Release();

	LPD3DXFONT GetFont(string strFontName);
};

extern cFontManager* g_pFontManager;
