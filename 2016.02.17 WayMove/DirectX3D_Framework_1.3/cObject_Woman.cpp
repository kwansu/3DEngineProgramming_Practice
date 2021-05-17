#include "stdafx.h"
#include "cObject_Woman.h"


cObject_Woman::cObject_Woman()
	: m_vWayPos(0, 0, 0)
	, m_vSpeed(0, 0, 1)
	, m_bBottom(false)
	, m_bMove(false)
	, m_bPicked(false)
{
	//m_fAngleX = -90;
	SetScale(5, 5, 5);
	UpdateWorld();

	D3DXCreateSphere(g_pDevice, 3.3, 10, 10, &m_pShpere, NULL);

	m_pLoader = new ASELoader;
	m_pLoader->LoadASE("./woman/woman_01_all.ASE");
	m_pLoader2 = new ASELoader;
	m_pLoader2->LoadASE("./woman/woman_01_all_stand.ASE");

	m_pMoveRoot = m_pLoader->m_pRoot;
	m_pIdleRoot = m_pLoader2->m_pRoot;
}


cObject_Woman::~cObject_Woman()
{
	SafeRelease(m_pShpere);
	SafeRelease(m_pLoader);
	SafeRelease(m_pLoader2);
}


void cObject_Woman::Setup()
{
}


void cObject_Woman::Update()
{
	if (m_bMove)
	{
		m_vPos += m_vLook * 0.5f;
		
		if (D3DXVec3LengthSq(&(m_vWayPos - m_vPos)) < 0.5f)
			m_bMove = false;
	}

	UpdateTranslation();
	D3DXMatrixLookAtLH(&m_matRot, &D3DXVECTOR3(0, 0, 0), &m_vSpeed, &D3DXVECTOR3(0, 1, 0));
	
	//D3DXMATRIXA16 matR;
	//D3DXMatrixRotationY(&matR, D3DXToRadian(-90));

	m_matWolrd = m_matScale * m_matRot * m_matTrl;
}


void cObject_Woman::Render()
{
	DWORD dwDuration = (GetTickCount() * 3) % 2560 + 640;

	if (m_bMove)
	{
		m_pMoveRoot->s_dwTick = dwDuration;
		m_pMoveRoot->Render(&m_matWolrd, m_bPicked);
	}
	else
	{
		m_pIdleRoot->s_dwTick = dwDuration;
		m_pIdleRoot->Render(&m_matWolrd, m_bPicked);
	}

	// collider draw
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_matTrl._42 += 3.2;

	g_pDevice->SetTransform(D3DTS_WORLD, &m_matTrl);
	m_pShpere->DrawSubset(0);

	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void cObject_Woman::UpdatePicked(const D3DXVECTOR3 & vOri, const D3DXVECTOR3 & vDir)
{
	float ratio = - vOri.y / vDir.y;
	m_vWayPos = vOri + ratio * vDir;

	m_vLook = m_vWayPos - m_vPos;
	D3DXVec3Normalize(&m_vLook, &m_vLook);

	m_vSpeed = m_vLook;
	m_vSpeed.z *= -1;

	m_bMove = true;
}

bool cObject_Woman::IsPicked(const D3DXVECTOR3 & vOri, const D3DXVECTOR3 & vDir)
{
	D3DXVECTOR3 vSphere(0, 3.2, 0);
	vSphere += m_vPos;

	D3DXVECTOR3 vD = vOri - vSphere;

	float dist = D3DXVec3Dot(&vD, &vD) - D3DXVec3Dot(&vD, &vDir) * D3DXVec3Dot(&vD, &vDir);

	if (dist <= 3.3f * 3.3f)
	{
		m_bPicked = true;
		return true;
	}

	return false;
}
