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
	cObject_Woman*		m_pWoman2;
	cObject_Woman*		m_pPicked;

	cObject_MouseMark*	m_pMouseMark;

	// mouse ray
	D3DXVECTOR3			m_vDir;
	D3DXVECTOR3			m_vPos;

public:
	void Release();
	void Update();
	void Render();
	void UpdatePickedObject();
};

