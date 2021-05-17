#pragma once
#include "stdGameObjects.h"
#include "cSkinningMesh.h"

class cGameObjectManager :
	public iInputProcessor, public iObjectMessenger
{
	SINGLETONE(cGameObjectManager);

private:
	D3DLIGHT9				m_light;
	cGrid*					m_pGrid;

	vector<cGameObject*>	m_vecpGameObjects;
	cObj_Player*			m_pPlayer;

	cSkinningMesh*			m_pSkinning;

	// 오브젝트 편집기능
	cGameObject*			m_pPickObjec;
	D3DXVECTOR3				m_vOffset;
	bool					m_isEdit;
	bool					m_isDrag;
	bool					m_isPlay;
	float					m_fRatio;

public:
	void Setup();
	void Release();
	void Update();
	void Render();

	void MessageHandler(iObjectMessenger* pGenerator, eObj_Message eMessage);

private:
	void InputProcess(iInputProcessor* pGenerator);
	void PlayerControl();
	void EditModeProcess();
};


extern cGameObjectManager*	g_pGameObjects;
