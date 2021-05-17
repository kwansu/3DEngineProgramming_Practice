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

stTextureData cTextrueManager::LoadTextureDate(const char* szTextureName)
{
	auto iter = m_mapTextureDate.find(szTextureName);

	if (iter == m_mapTextureDate.end())
	{
		if (m_mapTextureDate[szTextureName].pTexture == NULL)
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
				&m_mapTextureDate[szTextureName].stTextureInfo,
				NULL,
				&m_mapTextureDate[szTextureName].pTexture);
		}
	}

	return m_mapTextureDate[szTextureName];
}
