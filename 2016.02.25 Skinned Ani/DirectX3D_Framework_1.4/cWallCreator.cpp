#include "stdafx.h"
#include "cWallCreator.h"
#include "cMeshManager.h"
#include "cCircleList.h"


bool cWallCreator::stLine::IsCrossLine(const stLine & otherLine) const
{
	float fBase = (otherLine.vEnd.z - otherLine.vStart.z) * (vEnd.x - vStart.x)
		- (otherLine.vEnd.x - otherLine.vStart.x) * (vEnd.z - vStart.z);

	// 교점이 무수히 많은 경우. 나중에 겹치는지 확인하고 리턴
	if (IsEqual(fBase, 0))
	{
		assert(false && "직선의 방향이 같습니다. 예외처리 해주세요.");
	}

	float t1 = (otherLine.vEnd.x - otherLine.vStart.x) * (vStart.z - otherLine.vStart.z)
		- (otherLine.vEnd.z - otherLine.vStart.z) * (vStart.x - otherLine.vStart.x);

	float t2 = (vEnd.x - vStart.x) * (vStart.z - otherLine.vStart.z)
		- (vEnd.z - vStart.z) * (vStart.x - otherLine.vStart.x);

	t1 = t1 / fBase;
	t2 = t2 / fBase;

	if (t1 <= 0 || t1 >= 1 || t2 <= 0 || t2 >= 1)
		return false;

	return true;
}


cWallCreator* g_pWallCreator = cWallCreator::GetInstance();

cWallCreator::cWallCreator()
	: m_pMeshData(NULL)
	, m_pMeshData2(NULL)
{
}


cWallCreator::~cWallCreator()
{
}

void cWallCreator::Setup()
{
	m_pMeshData = g_pMeshManager->GetMeshData("Sphere");
	m_pMeshData->GetAttributeDate()[0].mtl.Diffuse = D3DXCOLOR(0.2f, 0.5f, 0.6f, 1.0f);

	D3DXMatrixScaling(&m_matWorld, 0.2f, 0.2f, 0.2f);
}

void cWallCreator::DebugRender()
{
	for each(const auto v in m_vecVertex)
	{
		m_matWorld._41 = v.x;
		m_matWorld._42 = v.y;
		m_matWorld._43 = v.z;
		g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		m_pMeshData->Render();
	}

	D3DXMATRIXA16 mat;

	D3DXMatrixIdentity(&mat);
	g_pDevice->SetTransform(D3DTS_WORLD, &mat);

	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);

	//if (isDraw)
	//{
	//	//m_pMeshData2->Render();

	//	g_pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST,
	//		0,
	//		m_vecVertex.size(),
	//		m_vecIndex.size() / 3,
	//		&m_vecIndex[0],
	//		D3DFMT_INDEX32,
	//		&m_vecVertex[0],
	//		sizeof(D3DXVECTOR3));
	//}

	for each(const auto v in m_vecLine)
	{
		g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, &v, sizeof(D3DXVECTOR3));
	}

	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
}

void cWallCreator::AddVertex(const D3DXVECTOR3 & vPos)
{
	if (m_vecVertex.empty())
	{
		m_vCurPos = vPos;
		m_vecVertex.push_back(m_vCurPos);
		return;
	}

	stLine newLine;
	newLine.vStart = m_vCurPos;
	newLine.vEnd = vPos;

	for each(const auto& line in m_vecLine)
	{
		if (newLine.IsCrossLine(line))
			return;
	}

	m_vCurPos = vPos;
	m_vecVertex.push_back(m_vCurPos);
	m_vecLine.push_back(newLine);
}

void cWallCreator::CreateWall()
{
	if (m_vecVertex.size() < 3)
		return;

	vector<int>	indexBuffer;
	cCircleList	listNonCheck;

	stLine lineCut;
	lineCut.vStart = m_vCurPos;
	lineCut.vEnd = m_vecVertex[0];
	m_vecLine.push_back(lineCut);

	for (int i = 0; i < m_vecVertex.size(); ++i)
		listNonCheck.Push(i);

	stNode* pBack = listNonCheck.GetRootNode();
	stNode* pCenter = pBack->pNext;
	stNode* pFront = pCenter->pNext;

	D3DXVECTOR3 vUpCross;
	D3DXVECTOR3 v1, v2;

	D3DXVec3Normalize(&v1, &(m_vecVertex[0] - m_vecVertex[1]));
	D3DXVec3Normalize(&v2, &(m_vecVertex[2] - m_vecVertex[1]));
	v1 = (v1 + v2)*0.5f;

	D3DXVec3Cross(&vUpCross, &v2, &v1);
	if (vUpCross.y < 0)
		vUpCross *= -1;

	bool isUp = true;//IsDirectionInside(vUpCross);

	while (pFront->pNext != pBack)
	{
		v1 = m_vecVertex[pCenter->data] - m_vecVertex[pBack->data];
		v2 = m_vecVertex[pFront->data] - m_vecVertex[pCenter->data];
		D3DXVec3Cross(&vUpCross, &v1, &v2);

		lineCut.vEnd = m_vecVertex[pBack->data];
		lineCut.vStart = m_vecVertex[pFront->data];

		v1 = m_vecVertex[pFront->pNext->data] - m_vecVertex[pFront->data];

		if ((vUpCross.y < 0) == isUp && IsCutTriangle(lineCut, -v2, v1))
		{
			indexBuffer.push_back(pBack->data);
			indexBuffer.push_back(pFront->data);
			indexBuffer.push_back(pCenter->data);

			listNonCheck.Erase(pCenter);

			pCenter = pFront;
			pFront = pFront->pNext;

			m_vecLine.push_back(lineCut);  //선 확인용 필히 지울것
		}
		else
		{
			stNode* swap = pFront->pNext;
			pBack = pCenter;
			pCenter = pFront;
			pFront = swap;
		}
	}

	stNode* pNode = listNonCheck.GetRootNode();
	indexBuffer.push_back(pNode->data);
	indexBuffer.push_back(pNode->pNext->pNext->data);
	indexBuffer.push_back(pNode->pNext->data);

	isDraw = true;
}

void cWallCreator::CreateMesh(const vector<int>& vecIndexBuffer, bool isUpCross)
{
	LPD3DXMESH pMesh;
	int nHalfVertices = m_vecVertex.size();
	int nIndexSize = vecIndexBuffer.size() * 2 + nHalfVertices * 6;

	D3DXCreateMeshFVF(nIndexSize / 3,
		nHalfVertices * 2,
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		VERTEX_FVF::PNT,
		g_pDevice,
		&pMesh);

	// vertex buffer
	stVertex_PNT* pVertex = NULL;
	pMesh->LockVertexBuffer(0, (LPVOID*)&pVertex);

	for (int n = 0; n < nHalfVertices; ++n)
	{
		pVertex[n].p = m_vecVertex[n];
		pVertex[n + nHalfVertices].p = m_vecVertex[n];
		pVertex[n + nHalfVertices].p.y += 1;
	}


	m_vecVertex.clear();

	m_vecVertex.resize(nHalfVertices * 2);
	for (int n = 0; n < nHalfVertices * 2; ++n)
	{
		m_vecVertex[n] = pVertex[n].p;
	}

	pMesh->UnlockVertexBuffer();

	DWORD* pIndex = NULL;
	pMesh->LockIndexBuffer(0, (LPVOID*)&pIndex);

	int nCount = 0;
	for (int i = 0; i < nHalfVertices - 1; ++i)
	{
		pIndex[nCount++] = i;
		pIndex[nCount++] = i + 1;
		pIndex[nCount++] = i + nHalfVertices;

		pIndex[nCount++] = i + 1;
		pIndex[nCount++] = i + 1 + nHalfVertices;
		pIndex[nCount++] = i + nHalfVertices;
	}

	pIndex[nCount++] = nHalfVertices - 1;
	pIndex[nCount++] = 0;
	pIndex[nCount++] = nHalfVertices * 2 - 1;

	pIndex[nCount++] = 0;
	pIndex[nCount++] = nHalfVertices;
	pIndex[nCount++] = nHalfVertices * 2 - 1;

	for (int i = 0; i < vecIndexBuffer.size(); ++i)
	{
		pIndex[nCount++] = vecIndexBuffer[i];
	}
	for (int i = 0; i < vecIndexBuffer.size(); ++i)
	{
		pIndex[nCount++] = vecIndexBuffer[i] + nHalfVertices;
	}

	// Index buffer
	m_vecIndex.resize(nIndexSize);
	memcpy(&m_vecIndex[0], pIndex, nIndexSize * sizeof(DWORD));
	pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	pMesh->LockAttributeBuffer(0, &pA);
	for (int i = 0; i < nIndexSize / 3; ++i)
	{
		pA[i] = 0;
	}
	pMesh->UnlockAttributeBuffer();

	//vector<DWORD> vecAdj(nHalfVertices*2);
	//pMesh->GenerateAdjacency(0.0f, &vecAdj[0]);

	//pMesh->OptimizeInplace(
	//	D3DXMESHOPT_ATTRSORT |
	//	D3DXMESHOPT_COMPACT |
	//	D3DXMESHOPT_VERTEXCACHE,
	//	&vecAdj[0],
	//	0, 0, 0);

	stMeshAttribute stAtt;
	stAtt.mtl.Diffuse = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);

	//cMeshData* pMeshData = g_pMeshManager->CreateMeshData("wall");
	m_pMeshData2 = g_pMeshManager->CreateMeshData("wall");
	m_pMeshData2->SetMesh(pMesh);
	m_pMeshData2->GetAttributeDate().push_back(stAtt);

	m_vecVertex.clear();
	m_vecLine.clear();
}

bool cWallCreator::IsDirectionInside(const D3DXVECTOR3 & vPos)
{
	double fSumAngle = 0;
	double fAngle;
	D3DXVECTOR3	vPrevPos = m_vecVertex.back();
	D3DXVECTOR3 vD1, vD2;

	D3DXVec3Normalize(&vD2, &(vPrevPos - vPos));

	for each(const D3DXVECTOR3& vCurPos in m_vecVertex)
	{
		D3DXVec3Normalize(&vD1, &(vCurPos - vPos));
		fAngle = acos(D3DXVec3Dot(&vD1, &vD2));

		D3DXVec3Cross(&vD2, &vD1, &(vCurPos - vPrevPos));
		if (vD2.y > 0)
			fSumAngle += fAngle;
		else
			fSumAngle -= fAngle;

		vPrevPos = vCurPos;
		vD2 = vD1;
	}

	fAngle = acos(fSumAngle);
	return IsEqual(fSumAngle, 0);
}

// 다른 선을 자르지 않으면서 삼각형을 만들수 있으면 true
bool cWallCreator::IsCutTriangle(const stLine & _line, D3DXVECTOR3 vDir, D3DXVECTOR3 vDir2)
{
	D3DXVECTOR3 v = _line.vEnd - _line.vStart;

	D3DXVec3Normalize(&v, &v);
	D3DXVec3Normalize(&vDir, &vDir);
	D3DXVec3Normalize(&vDir2, &vDir2);

	float f1 = D3DXVec3Dot(&v, &vDir);
	float f2 = D3DXVec3Dot(&vDir, &vDir2);

	D3DXVec3Cross(&v, &vDir, &v);
	D3DXVec3Cross(&vDir2, &vDir, &vDir2);

	if (v.y * vDir2.y > 0)
	{
		if (f1 <= f2)
			return false;
	}

	for each(const auto& line in m_vecLine)
	{
		if (line.vEnd == _line.vEnd || line.vEnd == _line.vStart)
			continue;

		if (line.IsCrossLine(_line))
			return false;
	}

	return true;
}

void cWallCreator::InputProcess(iInputProcessor * pGenerator)
{
	if (g_pInput->IsKeyDown(VK_LBUTTON))
	{
		cRay rayMouse = g_pCamera->GetMouseRay();
		D3DXVECTOR3 vPos;
		if (rayMouse.IsCollisionAsPlane(&vPos, stPlane()))
		{
			D3DXMATRIXA16 matInverse;

			int i = 0;
			for each(const auto &v in m_vecVertex)
			{
				D3DXMatrixTranslation(&matInverse, -v.x, -v.y, -v.z);

				if (cCollider_Sphere::IsCollisionAsRay(rayMouse, &matInverse))
				{
					if (i == 0)
					{
						CreateWall();
					}
					break;
				}
				++i;
			}

			if (i == m_vecVertex.size())
			{
				AddVertex(vPos);
			}
		}
	}
}
