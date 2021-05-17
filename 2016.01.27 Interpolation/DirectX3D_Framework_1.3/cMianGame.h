#pragma once
#include "stdObjects.h"

class cMianGame
{
private:
	cObject*			m_pStructure;
	cObject*			m_pHuman;
	cObject*			m_pHuman2;
	cGrid*				m_pGrid;

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

