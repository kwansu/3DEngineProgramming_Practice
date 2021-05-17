#pragma once
#include "stdObjects.h"
#include "ASELoader.h"
#include "cObject_Woman.h"

class cMianGame
{
private:
	cObject*			m_pStructure;
	cObject*			m_pHuman;
	cObject*			m_pHuman2;
	cGrid*				m_pGrid;
	cObject_Woman*		m_pWoman;

	ASELoader*			m_pLoader;

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

