#include "stdafx.h"
#include "cAStarManager.h"


bool stAStarNode::IsGreaterCompare(iHeapData * pOhter)
{
	if (dynamic_cast<stAStarNode*>(pOhter)->f <= f)
		return false;

	return true;
}

cAStarManager::cAStarManager()
	: m_arrMap(NULL)
{
	D3DXCreateBox(g_pDevice, 0.8f, 0.4f, 0.8f, &m_pMesh, NULL);
}


cAStarManager::~cAStarManager()
{
}

void cAStarManager::LoadFile(char * szFileName)
{
	ifstream ifAStar(szFileName, ios::in);

	if (!ifAStar.is_open())
		assert(false);

	char c;

	ZeroMemory(&m_mtl, sizeof(D3DMATERIAL9));

	m_mtl.Diffuse = D3DXCOLOR(0, 1, 0, 1);

	m_arrMap = new stAStarNode*[NUM_LINE];
	
	for (int i = 0; i < NUM_LINE; ++i)
	{
		m_arrMap[i] = new stAStarNode[NUM_LINE];

		for (int j = 0; j < NUM_LINE; ++j)
		{
			//srand();
			if (rand() % 80 < 20)
				m_arrMap[i][j].isBlock = true;
			else
				m_arrMap[i][j].isBlock = false;

			m_arrMap[i][j].x = i;
			m_arrMap[i][j].z = j;
		}
	}

	//for (int i = 0; i < NUM_LINE; ++i)
	//{
	//	m_arrMap[i] = new stAStarNode[NUM_LINE];

	//	for (int j = 0; j < NUM_LINE; ++j)
	//	{
	//		c = ifAStar.get();

	//		if(c == '\n')
	//			c = ifAStar.get();

	//		m_arrMap[i][j].isBlock = false;
	//		m_arrMap[i][j].isPath = false;
	//		m_arrMap[i][j].x = i;
	//		m_arrMap[i][j].z = j;
	//		m_arrMap[i][j].g = FLT_MAX;

	//		switch (c)
	//		{
	//		case 'E':
	//			//m_arrMap[i][j].isBlock = false;
	//			break;
	//		case 'B':
	//			m_arrMap[i][j].isBlock = true;
	//			break;
	//		case 'S':
	//			m_nStarti = i;
	//			m_nStartj = j;
	//			break;
	//		case 'D':
	//			m_nEndi = i;
	//			m_nEndj = j;
	//			break;
	//		}
	//	}
	//}
}

void cAStarManager::CalcPath(int px, int pz, list<D3DXVECTOR3> &listPath)
{
	openList.Clear();

	m_nStarti = px;
	m_nStartj = pz;

	cRay rayMouse = g_pCamera->GetMouseRay();

	float ratio = -rayMouse.m_vOri.y / rayMouse.m_vDir.y;
	D3DXVECTOR3 pos = (rayMouse.m_vOri + ratio * rayMouse.m_vDir);

	if(pos.x >0 && pos.x < NUM_LINE)
		m_nEndi = pos.x;
	if (pos.z >0 && pos.z < NUM_LINE)
		m_nEndj = pos.z;

	openList.Insert(&m_arrMap[m_nStarti][m_nStartj]);

	for (int i = 0; i < NUM_LINE; ++i)
	{
		for (int j = 0; j < NUM_LINE; ++j)
		{
			m_arrMap[i][j].h = abs(m_nEndi - i) + abs(m_nEndj - j);
			m_arrMap[i][j].parent = NULL;
			m_arrMap[i][j].isClose = false;
			m_arrMap[i][j].isPath = false;
			m_arrMap[i][j].g = FLT_MAX;
		}
	}

	m_arrMap[m_nStarti][m_nStartj].g = 0;
	m_arrMap[m_nStarti][m_nStartj].UpdateF();
	m_arrMap[m_nStarti][m_nStartj].isBlock = false;

	stAStarNode* pNode;
	int x, z;

	while (true)
	{
		pNode = dynamic_cast<stAStarNode*>(openList.PopFront());
		
		if (!pNode)
			return;

		pNode->isClose = true;

		if (pNode->h == 0)
			break;

		x = pNode->x; z = pNode->z;
		ProcessRoundNode(x + 1, z + 0, x, z, 1);
		ProcessRoundNode(x + 0, z + 1, x, z, 1);
		ProcessRoundNode(x - 1, z + 0, x, z, 1);
		ProcessRoundNode(x + 0, z - 1, x, z, 1);
		ProcessRoundNode(x + 1, z + 1, x, z, 1.414f);
		ProcessRoundNode(x + 1, z - 1, x, z, 1.414f);
		ProcessRoundNode(x - 1, z + 1, x, z, 1.414f);
		ProcessRoundNode(x - 1, z - 1, x, z, 1.414f);
	}

	listPath.clear();
	while (pNode->parent)
	{
		pNode->isPath = true;
		pos.x = pNode->x;
		pos.z = pNode->z;

		listPath.push_front(pos);
		pNode = pNode->parent;
	}
}

void cAStarManager::ProcessRoundNode(int x, int z, int px, int pz, float delta)
{
	if (x < 0 || x >= NUM_LINE || z < 0 || z >= NUM_LINE)
		return;

	if (m_arrMap[x][z].isBlock || m_arrMap[x][z].isClose)
		return;

	if (m_arrMap[x][pz].isBlock || m_arrMap[px][z].isBlock)
		return;

	if (!m_arrMap[x][z].parent)
	{
		openList.Insert(&m_arrMap[x][z]);
	}

	if (m_arrMap[x][z].g > m_arrMap[px][pz].g + delta)
	{
		m_arrMap[x][z].g = m_arrMap[px][pz].g + delta;
		m_arrMap[x][z].parent = &m_arrMap[px][pz];
		m_arrMap[x][z].UpdateF();
		openList.UpdateNode(&m_arrMap[x][z]);
	}
}

//stAStarNode * cAStarManager::ListSort()
//{
//	if (openList.empty())
//		return NULL;
//
//	list<stAStarNode*>::iterator iterMin;
//	float fMin = FLT_MAX;
//
//	for (list<stAStarNode*>::iterator iterList = openList.begin()
//		; iterList != openList.end(); ++iterList)
//	{
//		if (fMin > (*iterList)->f)
//		{
//			iterMin = iterList;
//			fMin = (*iterList)->f;
//		}
//	}
//
//	stAStarNode* result = *iterMin;
//	openList.erase(iterMin);
//
//	return result;
//}

void cAStarManager::Render()
{
	D3DXMATRIXA16 mat;

	for (int i = 0; i < NUM_LINE; ++i)
	{
		for (int j = 0; j < NUM_LINE; ++j)
		{
			if (m_arrMap[i][j].isBlock)
			{
				m_mtl.Diffuse = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1);
			}
			else if (m_arrMap[i][j].isPath)
			{
				m_mtl.Diffuse = D3DXCOLOR(0, 1, 0, 1);
			}
			else if (m_arrMap[i][j].isClose)
			{
				m_mtl.Diffuse = D3DXCOLOR(1, 0, 0, 1);
			}
			else if (m_arrMap[i][j].parent)
			{
				m_mtl.Diffuse = D3DXCOLOR(0, 0, 1, 1);
			}
			else
			{
				m_mtl.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1);
			}

			D3DXMatrixTranslation(&mat, i, 0, j);

			g_pDevice->SetMaterial(&m_mtl);
			g_pDevice->SetTransform(D3DTS_WORLD, &mat);
			m_pMesh->DrawSubset(0);
		}
	}
}
