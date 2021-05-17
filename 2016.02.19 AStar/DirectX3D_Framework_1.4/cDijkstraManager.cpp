#include "stdafx.h"
#include "cDijkstraManager.h"


cDijkstraManager::cDijkstraManager()
	: m_arrEdgeCost(NULL)
	, m_pMesh(NULL)
	, m_pRoot(NULL)
{
}


cDijkstraManager::~cDijkstraManager()
{
}

void cDijkstraManager::Setup()
{
	DijLoader load;

	load.Load("dijkstra.txt", m_vecDijNode, m_arrEdgeCost);
	m_pRoot = &m_vecDijNode[0];

	load.CopyVertexEdge(m_vecVertexEdge);

	D3DXCreateSphere(g_pDevice, 0.3f, 10, 10, &m_pMesh, NULL);
}

void cDijkstraManager::Render()
{
	D3DXMATRIXA16 mat;

	g_pDevice->SetFVF(VERTEX_FVF::PC);
	D3DXMatrixIdentity(&mat);
	g_pDevice->SetTexture(0, NULL);
	g_pDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecVertexEdge.size() / 2,
		&m_vecVertexEdge[0],
		sizeof(stVertex_PC));

	g_pDevice->SetFVF(m_pMesh->GetFVF());

	for (int i = 0; i < m_vecDijNode.size(); ++i)
	{
		if (&m_vecDijNode[i] == m_pRoot)
		{
			m_vecDijNode[i].mtl.Diffuse = D3DXCOLOR(1, 0, 0, 1);
		}
		else if(&m_vecDijNode[i] == m_pTarget)
		{
			m_vecDijNode[i].mtl.Diffuse = D3DXCOLOR(0, 0, 1, 1);
		}
		else if(m_vecDijNode[i].isPath)
		{
			m_vecDijNode[i].mtl.Diffuse = D3DXCOLOR(0, 1, 0, 1);
		}
		else
		{
			m_vecDijNode[i].mtl.Diffuse = D3DXCOLOR(1, 1, 1, 1);

		}
		m_vecDijNode[i].Render(m_pMesh);
	}
}

void cDijkstraManager::ProcessMouseClicked(bool bR)
{
	cRay ray = g_pCamera->GetMouseRay();

	cCollider_Sphere coll;
	coll.SetRadius(0.3f);

	for (int i = 0; i < m_vecDijNode.size(); ++i)
	{
		coll.SetOriginPos(m_vecDijNode[i].p);
		if (ray.IsCollisionSphere(&coll))
		{
			if (bR)
			{
				m_pRoot = &m_vecDijNode[i];
				CalcDijkstra();
			}
			else
			{
				m_pTarget = &m_vecDijNode[i];
				ProcessPath();
			}
		}
	}
}

void cDijkstraManager::ProcessPath()
{
	int size = m_vecDijNode.size();
	for (int i = 0; i < size; ++i)
	{
		m_vecDijNode[i].isPath = false;
	}

	DijNode* pNode = m_pTarget;

	while (pNode->parent)
	{
		pNode->isPath = true;
		pNode = pNode->parent;
	}
}

void cDijkstraManager::CalcDijkstra()
{
	int size = m_vecDijNode.size();
	for (int i = 0; i < size; ++i)
	{
		m_vecDijNode[i].vecChild.clear();
		m_vecDijNode[i].parent = NULL;
		m_vecDijNode[i].isPath = false;
	}

	vector<int>		vecVia(size);
	vector<float>	vecCost(size);
	vector<bool>	vecVist(size);

	for (int i = 0; i < size; ++i)
	{
		vecVia[i] = INT_MAX;
	}
	for (int i = 0; i < size; ++i)
	{
		vecCost[i] = FLT_MAX;
	}
	for (int i = 0; i < size; ++i)
	{
		vecVist[i] = false;
	}

	int nCur;

	assert(m_pRoot);

	for (nCur = 0; nCur < size; ++nCur)
	{
		if (m_pRoot == &m_vecDijNode[nCur])
			break;
	}

	vecVist[nCur] = true;
	vecCost[nCur] = 0;
	float fCost;

	while (true)
	{
		for (int i = 0; i < size; ++i)
		{
			if (!vecVist[i])
			{
				fCost = m_arrEdgeCost[nCur][i] + vecCost[nCur];

				if (vecCost[i] > fCost)
				{
					vecCost[i] = fCost;
					vecVia[i] = nCur;
				}
			}
		}

		int nMin = INT_MAX;
		int nNext = -1;
		for (int i = 0; i < size; ++i)
		{
			if (!vecVist[i])
			{
				if (nMin > vecCost[i])
				{
					nMin = vecCost[i];
					nNext = i;
				}
			}
		}

		if (nNext == -1)
			break;

		nCur = nNext;
		vecVist[nCur] = true;
	}

	for (int i = 0; i < size; ++i)
	{
		if (vecVia[i] != INT_MAX)
		{
			m_vecDijNode[i].parent = &m_vecDijNode[vecVia[i]];
			m_vecDijNode[vecVia[i]].vecChild.push_back(&m_vecDijNode[i]);
		}
	}
}
