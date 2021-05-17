#include "stdafx.h"
#include "cWallCreator.h"


cWallCreator* g_pWallCreator = cWallCreator::GetInstance();

cWallCreator::cWallCreator()
	: m_pMeshData(NULL)
	, m_pPickPoint(NULL)
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
	D3DXVECTOR3 vPos;

	for (int i = 0; i < m_vecPoint.size(); ++i)
	{
		vPos = m_vecPoint[i].vPos;
		m_matWorld._41 = vPos.x;
		m_matWorld._42 = vPos.y;
		m_matWorld._43 = vPos.z;

		g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		m_pMeshData->Render();
	}

	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);

	D3DXVECTOR3 v[3];

	v[0] = D3DXVECTOR3(0, 1, 0);
	v[1] = D3DXVECTOR3(0, 1, 10);
	v[2] = D3DXVECTOR3(10, 1, 0);
	int index[3];

	index[0] = 0;
	index[1] = 1;
	index[2] = 2;

	if (g_pInput->IsKeyPress('N'))
	{
		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		g_pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST,
			0,
			m_vecIndex.size(),
			m_vecPoint.size(),
			&m_vecIndex[0],
			D3DFMT_INDEX32,
			&m_vecPoint[0],
			sizeof(D3DXVECTOR3));
	}
}

void cWallCreator::CreateWall()
{
	//D3DXCreateMeshFVF(m_vecIndex.size() / 3,
	//	m_vecPoint.size,
	//	D3DPOOL_MANAGED,
	//	VERTEX_FVF::P,
	//	g_pDevice,
	//	&m_pMesh);

	//p
}

void cWallCreator::ConnectPoint(int nIndex)
{
	int nPickIndex = m_pPickPoint->nIndex;

	for each(auto val in m_vecPoint[nIndex].setIndex)
	{
		for each(auto oriIndex in m_vecPoint[val].setIndex)
		{
			if (oriIndex == nPickIndex)
			{
				D3DXVECTOR3 v1 = m_pPickPoint->vPos - m_vecPoint[nIndex].vPos;
				D3DXVECTOR3 v2 = m_vecPoint[oriIndex].vPos - m_vecPoint[nIndex].vPos;
				D3DXVec3Cross(&v1, &v1, &v2);

				m_vecIndex.push_back(nPickIndex);
				if (v1.y > 0)
				{
					m_vecIndex.push_back(nIndex);
					m_vecIndex.push_back(oriIndex);
				}
				else
				{
					m_vecIndex.push_back(oriIndex);
					m_vecIndex.push_back(nIndex);
				}

				m_pPickPoint->setIndex.insert(nIndex);
				m_vecPoint[nIndex].setIndex.insert(nPickIndex);
				break;
			}
		}
	}
}

void cWallCreator::AddPoint(const D3DXVECTOR3 & vPos)
{
	stPoint point;
	point.vPos = vPos;
	point.nIndex = m_vecPoint.size();
	
	m_vecPoint.push_back(point);
	m_pPickPoint = &m_vecPoint.back();
}

void cWallCreator::CalcOutline(stPoint * pPoint, OUT cMeshData * pMeshData)
{
	//int size = pPoint->setIndex.size();
	//for (int i = 0; i < size; ++i)
	//{
	//	if(i)
	//}
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

			int i;
			for (i = 0; i < m_vecPoint.size(); ++i)
			{
				D3DXMatrixTranslation(&matInverse, -m_vecPoint[i].vPos.x,
					-m_vecPoint[i].vPos.y, -m_vecPoint[i].vPos.z);

				if (cCollider_Sphere::IsCollisionAsRay(rayMouse, &matInverse))
				{
					if (g_pInput->IsKeyPress(VK_CONTROL))
						ConnectPoint(i);
					else
						m_pPickPoint = &m_vecPoint[i];

					break;
				}
			}

			if (i == m_vecPoint.size())
				AddPoint(vPos);
		}
	}

	if (g_pInput->IsKeyDown('C'))
	{
		CreateWall();
	}
}
