#include "stdafx.h"
#include "cGameObjectManager.h"


cGameObjectManager* g_pGameObjects = cGameObjectManager::GetInstance();

cGameObjectManager::cGameObjectManager()
	: m_pGrid(NULL)
	, m_pMesh(NULL)
	, m_pPicked(NULL)
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

	cGameObject* pObject = new cObj_Sphere;
	pObject->Setup();
	m_vecpGameObjects.push_back(pObject);

	pObject = new cObj_Sphere;
	pObject->Setup();
	pObject->SetPosition(5, 0, 5);
	m_vecpGameObjects.push_back(pObject);

	D3DXCreateSphere(g_pDevice, 0.3f, 10, 10, &m_pMesh, NULL);

	DijNode node(D3DXVECTOR3(0, 0, 0));
	node.isPicked = true;
	m_vecNode.push_back(node);
	m_pPicked = &m_vecNode[0];

	//a.Setup();

	// light Setup
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));
	m_light.Type = D3DLIGHT_DIRECTIONAL;
	m_light.Diffuse = m_light.Ambient = D3DXCOLOR(1, 1, 1, 1);
	m_light.Direction = D3DXVECTOR3(-1, -1, -1);
	g_pDevice->SetLight(0, &m_light);
	g_pDevice->LightEnable(0, true);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	//g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}

void cGameObjectManager::Relese()
{
	for each (cGameObject* pObj in m_vecpGameObjects)
	{
		SafeDelete(pObj);
	}

	SafeRelease(m_pMesh);
	SafeDelete(m_pGrid);
}

void cGameObjectManager::Update()
{
	g_pCamera->Update();

	for each (cGameObject* pObj in m_vecpGameObjects)
	{
		pObj->Update();
	}

	if (g_pInput->IsKeyDown(VK_LBUTTON))
	{
		ProcessClick();
	}

	if (g_pInput->IsKeyDown(VK_SPACE))
	{
		cRay rayMouse = g_pCamera->GetMouseRay();

		float ratio = -rayMouse.m_vOri.y / rayMouse.m_vDir.y;

		m_vecNode.push_back(DijNode(rayMouse.m_vOri + ratio * rayMouse.m_vDir));
	}

	//if (g_pInput->IsKeyDown(VK_LBUTTON))
	//	a.ProcessMouseClicked(false);

	//if (g_pInput->IsKeyDown(VK_RBUTTON))
	//	a.ProcessMouseClicked(true);

	//dynamic_cast<cObj_Sphere*>(m_vecpGameObjects[0])->IsCollision(dynamic_cast<cObj_Sphere*>(m_vecpGameObjects[1]));
}

void cGameObjectManager::Render()
{
	m_pGrid->Render();

	//for each (cGameObject* pObj in m_vecpGameObjects)
	//{
	//	pObj->Render();
	//}

	//a.Render();

	for each(auto p in m_vecNode)
		p.Render(m_pMesh);

	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);

	g_pDevice->SetFVF(VERTEX_FVF::PC);
	//g_pDevice->SetTexture(0, NULL);
	//g_pDevice->SetTransform(D3DTS_WORLD, &mat);
	//g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST,
	//	m_vecEdge.size() / 2,
	//	&m_vecEdge[0],
	//	sizeof(stVertex_PC));
}

void cGameObjectManager::ProcessClick()
{
	cRay ray = g_pCamera->GetMouseRay();

	cCollider_Sphere coll;
	coll.SetRadius(0.3f);

	for (int i = 0; i < m_vecNode.size(); ++i)
	{
		coll.SetOriginPos(m_vecNode[i].p);

		if (ray.IsCollisionSphere(&coll))
		{
			if (g_pInput->IsKeyPress(VK_CONTROL))
			{
				m_pPicked->vecChild.push_back(&m_vecNode[i]);
				m_vecNode[i].vecChild.push_back(m_pPicked);
				m_vecEdge.push_back(stVertex_PC(m_pPicked->p));
				m_vecEdge.push_back(stVertex_PC(m_vecNode[i].p));
			}
			else
			{
				m_pPicked->isPicked = false;
				m_pPicked = &m_vecNode[i];
				m_vecNode[i].isPicked = true;
			}
			break;
		}
	}
}
