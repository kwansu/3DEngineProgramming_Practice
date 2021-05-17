#include "stdafx.h"
#include "cSpriteManager.h"


LPD3DXSPRITE g_pSprite = cSpriteManager::GetInstance()->GetSprite();

cSpriteManager::cSpriteManager()
	: m_pSprite(NULL)
{
}


cSpriteManager::~cSpriteManager()
{
	SafeRelease(m_pSprite);
}

LPD3DXSPRITE cSpriteManager::GetSprite()
{
	return m_pSprite;
}
