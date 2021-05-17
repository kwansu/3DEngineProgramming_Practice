#include "stdafx.h"
#include "cTextrueManager.h"


extern cTextrueManager* g_pTexture = cTextrueManager::GetInstance();

cTextrueManager::cTextrueManager()
{
}


cTextrueManager::~cTextrueManager()
{
}

void cTextrueManager::Release()
{
	for each(auto data in m_mapTextureDate)
	{
		SafeRelease(data.second.pTexture);
	}
}

stTextureData cTextrueManager::LoadTextureDate(char* szTextureName)
{
	stTextureData textureData(m_mapTextureDate[szTextureName]);

	if (textureData.pTexture == NULL)
	{
		D3DXCreateTextureFromFileEx(
			g_pDevice,
			szTextureName,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			NULL,
			&textureData.stTextureInfo,
			NULL,
			&textureData.pTexture);
	}

	return textureData;
}
