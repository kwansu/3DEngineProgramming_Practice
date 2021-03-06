#include "stdafx.h"
#include "cGameObjectManager.h"


cGameObjectManager* g_pGameObjects = cGameObjectManager::GetInstance();

cGameObjectManager::cGameObjectManager()
	: m_pGrid(NULL)
{
}


cGameObjectManager::~cGameObjectManager()
{
}

void cGameObjectManager::Setup()
{
	g_pCamera->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	// 오브젝트 생성
	cGameObject* pObject = new cObj_Plane;
	pObject->Setup();
	m_vecpGameObjects.push_back(pObject);

	pObject = new cObj_Player;
	pObject->Setup();
	m_vecpGameObjects.push_back(pObject);

	cObj_Enemy* pObject2 = new cObj_Enemy;
	pObject2->Setup();
	pObject2->SetTarget(pObject);
	m_vecpGameObjects.push_back(pObject2);


	// light Setup
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));
	m_light.Type = D3DLIGHT_DIRECTIONAL;
	m_light.Diffuse = m_light.Ambient = D3DXCOLOR(1, 1, 1, 1);
	m_light.Direction = D3DXVECTOR3(-0.7, -1, 0.5f);
	g_pDevice->SetLight(0, &m_light);
	g_pDevice->LightEnable(0, true);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	//g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}

void cGameObjectManager::Release()
{
	for each (cGameObject* pObj in m_vecpGameObjects)
	{
		SafeDelete(pObj);
	}

	SafeDelete(m_pGrid);
}

void cGameObjectManager::Update()
{
	g_pCamera->Update();

	for each (cGameObject* pObj in m_vecpGameObjects)
	{
		pObj->Update();
	}
}

void cGameObjectManager::Render()
{
	m_pGrid->Render();

	for each (cGameObject* pObj in m_vecpGameObjects)
	{
		pObj->Render();
	}

	g_pPathManager->DebugRender();
	g_pWallCreator->DebugRender();
}

void cGameObjectManager::InputProcess(iInputProcessor * pGenerator)
{
	cRay rayMouse = g_pCamera->GetMouseRay();
	D3DXVECTOR3 vPickPos;
	rayMouse.IsCollisionAsPlane(&vPickPos, stPlane());

	if (g_pInput->IsKeyDown(VK_LBUTTON))
	{
		for each(const auto obj in m_vecpGameObjects)
		{
			if (obj->IsCollisionAsRay(&rayMouse))
			{
				m_pPickObjec = obj;
				m_vOffset = obj->GetPosition() - vPickPos;
				m_isDrag = true;
				break;
			}
		}
	}

	if (g_pInput->IsKeyUp(VK_LBUTTON))
	{
		m_fRatio = 1;
		m_isDrag = false;
	}

	if (m_isDrag)
	{
		if (g_pInput->IsKeyPress(VK_CONTROL))
		{
			POINT ptDelta = g_pInput->GetMouseInterval();
			m_fRatio += (ptDelta.x + ptDelta.y)*0.01f;
			m_pPickObjec->SetScale(m_fRatio);
		}
		else
		{
			vPickPos += m_vOffset;
			m_pPickObjec->SetPosition(&vPickPos);
		}
	}
}

