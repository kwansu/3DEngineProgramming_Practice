#pragma once
#include "stdGameObjects.h"

class cGameObjectManager :
	public iInputProcessor
{
	SINGLETONE(cGameObjectManager);

private:
	D3DLIGHT9				m_light;
	cGrid*					m_pGrid;

	vector<cGameObject*>	m_vecpGameObjects;

	// 오브젝트 편집기능
	cGameObject*			m_pPickObjec;
	D3DXVECTOR3				m_vOffset;
	bool					m_isDrag;
	float					m_fRatio;

public:
	void Setup();
	void Release();
	void Update();
	void Render();

	void InputProcess(iInputProcessor* pGenerator);
};


extern cGameObjectManager*	g_pGameObjects;
