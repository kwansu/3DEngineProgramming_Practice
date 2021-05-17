#pragma once
#include "stdObjects.h"
#include "ASELoader.h"
#include "cTerrain.h"

#define g_pObjects	cObjectManager::GetInstance()

class cObjectManager
{
	SINGLETONE(cObjectManager);

private:
	vector<cObject*>	m_apObjects;
	cObject_Woman*		m_pWoman;

	cTerrain*			m_pTerrain;
	cObject*			m_pPicked;
	cObject_MouseMark*	m_pMouseMark;

	ASELoader*			m_pLoader;

	// mouse ray
	D3DXVECTOR3			m_vDir;
	D3DXVECTOR3			m_vPos;

public:
	void Release();
	void Update();
	void Render();
	void UpdatePickedObject();
};

