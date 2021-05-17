#pragma once

class cSpriteManager
{
	SINGLETONE(cSpriteManager);

private:
	LPD3DXSPRITE	m_pSprite;

public:
	LPD3DXSPRITE GetSprite();
};


extern LPD3DXSPRITE g_pSprite;
