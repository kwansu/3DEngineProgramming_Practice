#pragma once
#include "stdObjects.h"
#include "cTerrain.h"

class cMianGame
{
private:
	cGrid*				m_pGrid;
	cTerrain*			m_pTerrain;

	D3DLIGHT9			m_light;

public:
	cMianGame();
	~cMianGame();

	void Initialize();
	void Release();
	void Run();
	void Update();
	void Render();
	void MessageHandler(HWND hWnd, UINT iMsg, WPARAM wp, LPARAM lp);
};

