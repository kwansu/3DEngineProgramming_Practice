#include "stdafx.h"
#include "cWallCreator.h"


bool cWallCreator::stLine::IsCrossLine(const stLine & otherLine)
{
	float fBase = (otherLine.vEnd.y - otherLine.vStart.y) * (vEnd.x - vStart.x)
				- (otherLine.vEnd.x - otherLine.vStart.x) * (vEnd.y - vStart.y);

	// 교점이 무수히 많은 경우. 나중에 겹치는지 확인하고 리턴
	if (IsEqual(fBase, 0))
	{
		assert(false && "직선의 방향이 같습니다. 예외처리 해주세요.");
	}

	float t1 = (otherLine.vEnd.x - otherLine.vStart.x) * (vStart.y - otherLine.vStart.y)
			- (otherLine.vEnd.y - otherLine.vStart.y) * (vStart.x - otherLine.vStart.x);

	float t2 =	(vEnd.x - vStart.x) * (vStart.y - otherLine.vStart.y)
			- (vEnd.y - vStart.y) * (vStart.x - otherLine.vStart.x);

	t1 = t1 / fBase;
	t2 = t2 / fBase;

	return false;
//	if(t1 < 0 || )
}


cWallCreator* g_pWallCreator = cWallCreator::GetInstance();

cWallCreator::cWallCreator()
	: m_pMeshData(NULL)
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
}

cMeshData * cWallCreator::CreateWall()
{
	return nullptr;
}

void cWallCreator::ConnectPoint(int nIndex)
{
}

void cWallCreator::AddVertex(const D3DXVECTOR3 & vPos)
{

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
		}
	}

	if (g_pInput->IsKeyDown('C'))
	{
		CreateWall();
	}
}
