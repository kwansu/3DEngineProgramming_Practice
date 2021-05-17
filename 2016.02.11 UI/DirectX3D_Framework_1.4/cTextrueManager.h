#pragma once

struct stTextureData
{
	LPDIRECT3DTEXTURE9	pTexture;
	D3DXIMAGE_INFO		stTextureInfo;

	stTextureData() : pTexture(NULL)
	{
		ZeroMemory(&stTextureInfo, sizeof(D3DXIMAGE_INFO));
	}
};

class cTextrueManager
{
	SINGLETONE(cTextrueManager);

private:
	map<string, stTextureData>	m_mapTextureDate;

public:
	void Release();

	stTextureData LoadTextureDate(string textureName);
};

extern cTextrueManager* g_pTexture;
