#include "stdafx.h"
#include "cPathManager.h"


cPathManager* g_pPathManager = cPathManager::GetInstance();

cPathManager::cPathManager()
	: m_pPickNode(NULL)
{
	D3DXMatrixIdentity(&m_mat);
	m_matWorld = m_mat;
	ZeroMemory(&m_mtl, sizeof(D3DMATERIAL9));
}


cPathManager::~cPathManager()
{
}

void cPathManager::Setup()
{
	m_pMeshData = g_pMeshManager->GetMeshData("Sphere");
	m_mtl.Diffuse = D3DXCOLOR(1, 0, 0, 1);
	D3DXMatrixScaling(&m_matWorld, 0.2f, 0.2f, 0.2f);
}

void cPathManager::AddPathNode(const stPathNode & node)
{
	m_vecPathNode.push_back(node);

	for (int i = 0; i < node.vecEdge.size(); ++i)
	{
		m_vecpEdge.push_back(&m_vecPathNode.back().vecEdge[i]);
	}

	float x = node.vPos.x;

	while (true)
	{
		auto result = m_mapXAxisSort.insert(pair<float, int>(node.vPos.x, m_vecPathNode.size() - 1));
		if (result.second)
			return;

		x = x + 0.01f;
	}
}

bool cPathManager::CalcShortestPath(OUT list<D3DXVECTOR3>& listPath, const D3DXVECTOR3 & vS, const D3DXVECTOR3 & vD)
{
	listPath.clear();

	auto iterEnd = m_vecPathNode.end();
	for (auto iter = m_vecPathNode.begin(); iter != iterEnd; ++iter)
	{
		iter->F = FLT_MAX;
		iter->G = FLT_MAX;
		iter->pParent = NULL;
		iter->isClose = false;
	}

	m_pStart = FindNearNode(vS.x);
	m_pDestination = FindNearNode(vD.x);

	m_pStart->G = 0;
	m_pStart->F = 0;
	m_pDestination->H = 0;

	list<stPathNode*> listOpen;
	listOpen.push_front(m_pStart);

	stPathNode* pCurNode = NULL;

	while (true)
	{
		pCurNode = FindSmallestFNode(listOpen);

		if (!pCurNode)
			return false;

		if (pCurNode == m_pDestination)
			break;

		pCurNode->UpdateEdge(listOpen, m_pDestination);
	}

	while (m_pDestination->pParent)
	{
		listPath.push_front(m_pDestination->vPos);
		m_pDestination = m_pDestination->pParent;
	}

	return true;
}

void cPathManager::DebugRender()
{
	D3DXVECTOR3 v[2];
	v[0] = D3DXVECTOR3(0, 0, 0);

	for each(const auto node in m_vecPathNode)
	{
		m_matWorld._41 = node.vPos.x;
		m_matWorld._42 = node.vPos.y;
		m_matWorld._43 = node.vPos.z;

		g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		m_pMeshData->Render();

		g_pDevice->SetMaterial(&m_mtl);
		for each(const auto edge in node.vecEdge)
		{
			v[1] = edge.pNode->vPos - node.vPos;

			g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, &v, sizeof(D3DXVECTOR3));
		}
	}

	if (m_pPickNode)
	{
		g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
		m_matWorld._41 = m_pPickNode->vPos.x;
		m_matWorld._42 = m_pPickNode->vPos.y;
		m_matWorld._43 = m_pPickNode->vPos.z;

		g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		m_pMeshData->Render();
		g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	}
}

void cPathManager::ConnectEdge(stPathNode * other)
{
	if (!m_pPickNode)
	{
		m_pPickNode = other;
		return;
	}
	
	if (m_pPickNode == other)
		return;

	D3DXVECTOR3 vDist = m_pPickNode->vPos - other->vPos;
	float fDistance = D3DXVec3Length(&vDist);

	m_pPickNode->vecEdge.push_back(stEdge(other, fDistance));
	other->vecEdge.push_back(stEdge(m_pPickNode, fDistance));

	m_vecpEdge.push_back(&m_pPickNode->vecEdge.back());
	m_vecpEdge.push_back(&other->vecEdge.back());
}

void cPathManager::CreatePathNode(const D3DXVECTOR3 & vPickPos)
{
	stPathNode node;

	node.vPos = vPickPos;
	m_vecPathNode.push_back(node);
	m_pPickNode = &m_vecPathNode.back();

	float x = node.vPos.x;

	while (true)
	{
		auto result = m_mapXAxisSort.insert(pair<float, int>(node.vPos.x, m_vecPathNode.size() - 1));
		if (result.second)
			return;

		x = x + 0.01f;
	}
}

stPathNode * cPathManager::FindNearNode(int x)
{
	int nIndex;
	auto result = m_mapXAxisSort.insert(pair<float, int>(x, -1));
	auto temp = result.first;

	if (result.second)
	{
		temp = result.first;

		if ((--temp) != m_mapXAxisSort.end())
			nIndex = (temp)->second;
		else
		{
			temp = result.first;
			nIndex = (++temp)->second;
		}

		m_mapXAxisSort.erase(result.first);
	}
	else
	{
		nIndex = result.second;
	}

	return &m_vecPathNode[nIndex];
}

stPathNode * cPathManager::FindSmallestFNode(list<stPathNode*>& listOpen)
{
	if (listOpen.empty())
		return NULL;

	float fMinF = FLT_MAX;

	list<stPathNode*>::iterator iterMin;
	for (auto iter = listOpen.begin(); iter != listOpen.end(); ++iter)
	{
		if ((*iter)->F < fMinF)
		{
			iterMin = iter;
			fMinF = (*iter)->F;
		}
	}

	stPathNode* result = (*iterMin);

	listOpen.erase(iterMin);

	result->isClose = true;
	return result;
}

void cPathManager::InputProcess()
{
	if (g_pInput->IsKeyDown(VK_LBUTTON))
	{
		cRay rayMouse = g_pCamera->GetMouseRay();

		D3DXVECTOR3 vPickPos;
		rayMouse.IsCollisionAsPlane(&vPickPos, stPlane());

		int i = 0;
		for each(const auto &node in m_vecPathNode)
		{
			D3DXMatrixTranslation(&m_mat, -node.vPos.x, -node.vPos.y, -node.vPos.z);

			if (cCollider_Sphere::IsCollisionAsRay(rayMouse, &m_mat))
			{
				if (g_pInput->IsKeyPress(VK_CONTROL))
				{
					ConnectEdge(&m_vecPathNode[i]);
				}
				//else if(g_pInput->IsKeyDown(VK_SHIFT))
				//{
				//	DeletePathNodeEdge(&m_vecPathNode[i]);
				//	m_vecPathNode.erase(m_vecPathNode.begin() + i);
				//}
				else
				{
					m_pPickNode = &m_vecPathNode[i];
				}
				return;
			}
			++i;
		}

		CreatePathNode(vPickPos);
	}
}

