#include "stdafx.h"
#include "cPathManager.h"


cPathManager* g_pPathManager = cPathManager::GetInstance();

cPathManager::cPathManager()
	: m_pPickNode(NULL)
{
	D3DXMatrixIdentity(&m_mat);
	m_matWorld = m_mat;
}


cPathManager::~cPathManager()
{
}

void cPathManager::Setup()
{
	m_pMeshData = g_pMeshManager->GetMeshData("Sphere");
	m_pMeshData->GetAttributeDate()[0].mtl.Diffuse = D3DXCOLOR(0, 1, 0, 1);
	D3DXMatrixScaling(&m_matWorld, 0.2f, 0.2f, 0.2f);
}

void cPathManager::AddPathNode(const stPathNode & node)
{
	//m_vecPathNode.push_back(node);
	//for (int i = 0; i < node.vecEdge.size(); ++i)
	//{
	//	m_vecpEdge.push_back(&m_vecPathNode.back().vecEdge[i]);
	//}

	//float x = node.vPos.x;

	//while (true)
	//{
	//	auto result = m_mapXAxisSort.insert(pair<float, int>(node.vPos.x, m_vecPathNode.size() - 1));
	//	if (result.second)
	//		return;

	//	x = x + 0.01f;
	//}
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

	m_vDestiation = vD;
	m_pDestination = FindNearNode(vD);

	// 노드가 없을 경우, 일단 넣고 리턴. 나중에 처리할것.
	if (!m_pDestination)
	{
		listPath.push_back(vD);
		return true;
	}

	m_nodeStart.vPos = vS;
	stPathNode* temp = FindNearNode(vS);
	temp->pParent = &m_nodeStart;
	temp->F = 0;
	temp->G = 0;

	m_pDestination->H = 0;

	list<stPathNode*> listOpen;
	listOpen.push_front(temp);

	stPathNode* pCurNode = NULL;

	while (true)
	{
		pCurNode = FindSmallestFNode(listOpen);

		if (!pCurNode)
			return false;

		if (pCurNode == m_pDestination)
			break;

		pCurNode->UpdateEdge(listOpen, m_vDestiation);
	}

	CalcFastPath(listPath);
	//while (true)
	//{
	//	listPath.push_front(m_pDestination->vPos);
	//	m_pDestination = m_pDestination->pParent;

	//	if (!m_pDestination)
	//		break;
	//}

	return true;
}

void cPathManager::DebugRender()
{
	D3DXVECTOR3 v[2];

	for each(const auto node in m_vecPathNode)
	{
		m_matWorld._41 = node.vPos.x;
		m_matWorld._42 = node.vPos.y;
		m_matWorld._43 = node.vPos.z;
		g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		m_pMeshData->Render();
	}

	if (m_isViewCore)
	{
		D3DXMatrixIdentity(&m_mat);

		for each(const auto node in m_vecCore)
		{
			m_mat._41 = node.x;
			m_mat._42 = node.y;
			m_mat._43 = node.z;
			g_pDevice->SetTransform(D3DTS_WORLD, &m_mat);
			m_pMeshData->Render();
		}
	}

	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMatrixIdentity(&m_mat);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_mat);

	for each(const auto connect in m_vecConnectData)
	{
		v[0] = m_vecPathNode[connect.nIndex1].vPos;
		v[1] = m_vecPathNode[connect.nIndex2].vPos;

		g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, &v, sizeof(D3DXVECTOR3));
	}

	if (m_pPickNode)
	{
		m_matWorld._41 = m_pPickNode->vPos.x;
		m_matWorld._42 = m_pPickNode->vPos.y;
		m_matWorld._43 = m_pPickNode->vPos.z;

		g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		m_pMeshData->Render();
	}

	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
}

void cPathManager::SaveDataFile()
{
	ofstream outFile("pathData.txt", ios::binary);

	int nConnectNum = m_vecConnectData.size();
	int nPathNodeNum = m_vecPathNode.size();
	int nCoreNum = m_vecCore.size();

	outFile << nConnectNum << endl;
	outFile << nPathNodeNum << endl;
	outFile << nCoreNum << endl;

	for (int i = 0; i < nConnectNum; ++i)
	{
		m_vecConnectData[i].OutFile(outFile);
	}

	for (int i = 0; i < nPathNodeNum; ++i)
	{
		m_vecPathNode[i].OutFile(outFile);
	}

	for (int i = 0; i < nCoreNum; ++i)
	{
		outFile << m_vecCore[i].x << endl;
		outFile << m_vecCore[i].y << endl;
		outFile << m_vecCore[i].z << endl;
	}
}

void cPathManager::LoadDataFile()
{
	m_vecConnectData.clear();
	m_vecPathNode.clear();
	m_vecCore.clear();

	ifstream inFile("pathData.txt", ios::binary);

	int nConnectNum, nPathNodeNum, nCoreNum;

	inFile >> nConnectNum >> nPathNodeNum >> nCoreNum;

	m_vecConnectData.resize(nConnectNum);
	m_vecPathNode.resize(nPathNodeNum);
	m_vecCore.resize(nCoreNum);

	for (int i = 0; i < nConnectNum; ++i)
	{
		m_vecConnectData[i].InFile(inFile);
	}

	for (int i = 0; i < nPathNodeNum; ++i)
	{
		m_vecPathNode[i].InFile(inFile);
	}

	D3DXVECTOR3 vPos;
	for (int i = 0; i < nCoreNum; ++i)
	{
		inFile >> m_vecCore[i].x >> m_vecCore[i].y >> m_vecCore[i].z;
	}

	stEdge edge;
	for each(const auto& connect in m_vecConnectData)
	{
		edge.cost = connect.cost;
		edge.vDir = m_vecPathNode[connect.nIndex2].vPos - m_vecPathNode[connect.nIndex1].vPos;
		D3DXVec3Normalize(&edge.vDir, &edge.vDir);

		edge.pNode = &m_vecPathNode[connect.nIndex2];
		m_vecPathNode[connect.nIndex1].vecEdge.push_back(edge);

		edge.vDir *= -1;
		edge.pNode = &m_vecPathNode[connect.nIndex1];
		m_vecPathNode[connect.nIndex2].vecEdge.push_back(edge);
	}
}

void cPathManager::ConnectEdge(stPathNode * other)
{
	if (!m_pPickNode)
	{
		m_nPicked = m_nPick;
		m_pPickNode = other;
		return;
	}
	
	if (m_pPickNode == other)
		return;

	D3DXVECTOR3 vDir = m_pPickNode->vPos - other->vPos;
	D3DXVec3Normalize(&vDir, &vDir);
	float fDistance = D3DXVec3Length(&vDir);

	m_pPickNode->vecEdge.push_back(stEdge(other, -vDir, fDistance));
	other->vecEdge.push_back(stEdge(m_pPickNode,  vDir, fDistance));

	stConnectData cd = { m_nPicked, m_nPick, fDistance };
	m_vecConnectData.push_back(cd);
}

void cPathManager::CreatePathNode(const D3DXVECTOR3 & vPickPos)
{
	stPathNode node;

	node.vPos = vPickPos;
	m_vecPathNode.push_back(node);
	m_pPickNode = &m_vecPathNode.back();

	//float x = node.vPos.x;

	//while (true)
	//{
	//	auto result = m_mapXAxisSort.insert(pair<float, int>(node.vPos.x, m_vecPathNode.size() - 1));
	//	if (result.second)
	//		return;

	//	x = x + 0.01f;
	//}
}

void cPathManager::EmplaceOutlineCore(const D3DXVECTOR3 & vPickPos)
{
	if (!m_pPickNode)
		return;

	m_vecCore.push_back(vPickPos);

	stPathNode* pNode = m_pPickNode;
	stPathNode* pPrevNode = NULL;

	D3DXVECTOR3 vTemp, vCross1, vCross2;
	int nCount = 0;

	while (true)
	{
		vTemp = vPickPos - pNode->vPos;
		D3DXVec3Normalize(&vTemp, &vTemp);

		D3DXVec3Cross(&vCross1, &pNode->vecEdge[0].vDir, &vTemp);
		D3DXVec3Cross(&vCross2, &pNode->vecEdge[1].vDir, &vTemp);

		pNode->isPositive = (vCross1.y > 0);
		pNode->isBetween = ((vCross1.y * vCross2.y) > 0);

		if (pNode->vecEdge[0].pNode == pPrevNode)
		{
			pPrevNode = pNode;
			pNode = pNode->vecEdge[1].pNode;
		}
		else
		{
			pPrevNode = pNode;
			pNode = pNode->vecEdge[0].pNode;
		}

		if (pNode == m_pPickNode)
			return;

		assert(++nCount < 30 && "cPathManager->EmplaceOutlineCore : length");
	}
}

// 나중에 이부분 최적화로 계선 할 것.
// 경로 단축을 x-z평면 기준으로 한다. 필요하면 바꿀 것.
void cPathManager::CalcFastPath(OUT list<D3DXVECTOR3>& listPath)
{
	stPathNode* pNode = m_pDestination;
	D3DXVECTOR3 pPrevPos = m_vDestiation;

	m_nodeStart.vPos;
	D3DXVECTOR3 v, d, w1, w2, r;
	float crossVW1, crossVW2, crossVD, dotVD;

	// 처음 마우스 픽킹위치가 벽속인지 판단하기 위해서 한번의 업데이트 실행
	// 반복코드를 줄일 방법을 생각해봐야함
	v = pNode->vPos - pPrevPos;
	d = pNode->pParent->vPos - pNode->vPos;
	w1 = pNode->vecEdge[0].vDir;
	w2 = pNode->vecEdge[1].vDir;

	D3DXVec3Normalize(&v, &v);

	D3DXVec3Cross(&r, &v, &w1);
	crossVW1 = r.y;
	D3DXVec3Cross(&r, &v, &w2);
	crossVW2 = r.y;

	// 벽안으로 들어 갈려는 경우
	if (((crossVW1 * crossVW2) > 0) == pNode->isBetween && (crossVW1 > 0) == pNode->isPositive)
	{
		pPrevPos = pNode->vPos;
		pNode = pNode->pParent;
	}

	listPath.push_front(pPrevPos);

	while (pNode->pParent)
	{
		v = pNode->vPos - pPrevPos;
		d = pNode->pParent->vPos - pNode->vPos;
		w1 = pNode->vecEdge[0].vDir;
		w2 = pNode->vecEdge[1].vDir;

		D3DXVec3Normalize(&v, &v);

		D3DXVec3Cross(&r, &v, &w1);
		crossVW1 = r.y;
		D3DXVec3Cross(&r, &v, &w2);
		crossVW2 = r.y;
		D3DXVec3Cross(&r, &v, &d);
		crossVD = r.y;

		D3DXVec3Normalize(&d, &d);
		dotVD = D3DXVec3Dot(&v, &d);

		// 아웃라인에 붙어서 움직일 경우
		// 어느 쪽이 안쪽인지 알기 위해서 코어벡터가 필요
		if (IsEqual(crossVW1 * crossVW2, 0))
		{
			if ((crossVW1 + crossVW2) * crossVD < EPSILON)// ||
				//!(dotVD >= D3DXVec3Dot(&v, &w1) && dotVD >= D3DXVec3Dot(&v, &w2)))
			{
				pNode = pNode->pParent;
				continue;
			}
		}
		else if ((crossVW1 * crossVW2 < EPSILON) || (crossVW1 + crossVW2) * crossVD < EPSILON
			|| (dotVD <= D3DXVec3Dot(&v, &w1) && dotVD <= D3DXVec3Dot(&v, &w2)))
		{
			// 경로 삭제가 가능한 경우
			pNode = pNode->pParent;
			continue;
		}

		pPrevPos = pNode->vPos;
		pNode = pNode->pParent;
		listPath.push_front(pPrevPos);
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

stPathNode * cPathManager::FindNearNode(const D3DXVECTOR3 & vOri)
{
	if (m_vecPathNode.empty())
		return NULL;

	float fMin = FLT_MAX;
	float fDist;
	int nIndex;

	int size = m_vecPathNode.size();
	for (int i = 0; i < size; ++i)
	{
		fDist = D3DXVec3LengthSq(&(vOri - m_vecPathNode[i].vPos));

		if (fMin > fDist)
		{
			nIndex = i;
			fMin = fDist;
		}
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

void cPathManager::InputProcess(iInputProcessor* pGenerator)
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
					m_nPick = i;
					ConnectEdge(&m_vecPathNode[i]);
				}
				else
				{
					m_nPicked = i;
					m_pPickNode = &m_vecPathNode[i];
				}
				return;
			}
			++i;
		}

		if (g_pInput->IsKeyPress(VK_SHIFT))
		{
			EmplaceOutlineCore(vPickPos);
		}
		else
		{
			if (!g_pInput->IsKeyPress(VK_CONTROL))
			{
				m_nPicked = i;
				CreatePathNode(vPickPos);
			}
		}
	}

	if (g_pInput->IsKeyDown('Q'))
	{
		SaveDataFile();
	}

	if (g_pInput->IsKeyDown('L'))
	{
		LoadDataFile();
	}

	if (g_pInput->IsKeyDown('V'))
	{
		m_isViewCore = m_isViewCore ? false : true;
	}
}

