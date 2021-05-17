#include "stdafx.h"
#include "cSpriteManager.h"


cSpriteManager::cSpriteManager()
	: m_pSprite(NULL)
{
	D3DXCreateSprite(g_pDevice, &m_pSprite);
}


cSpriteManager::~cSpriteManager()
{
}

LPD3DXSPRITE cSpriteManager::GetSprite()
{
	return m_pSprite;
}

void cSpriteManager::Release()
{
	SafeRelease(m_pSprite);
}
