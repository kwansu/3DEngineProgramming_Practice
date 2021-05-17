#pragma once

#define g_pTextureManager	cTextureManager::GetInstance()

class cTextureManager
{
	SINGLETONE(cTextureManager);

private:
	map<string, LPDIRECT3DTEXTURE9>	m_mapTexture;

public:

};

