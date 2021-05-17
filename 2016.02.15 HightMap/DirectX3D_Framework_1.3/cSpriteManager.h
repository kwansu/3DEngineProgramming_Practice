#pragma once

#define g_pSprite	cSpriteManager::GetInstance()->GetSprite()

class cSpriteManager
{
	SINGLETONE(cSpriteManager);

private:
	LPD3DXSPRITE	m_pSprite;

public:
	LPD3DXSPRITE GetSprite();
	void Release();
};

