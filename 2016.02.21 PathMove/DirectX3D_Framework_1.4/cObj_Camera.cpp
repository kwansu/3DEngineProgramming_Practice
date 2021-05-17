#include "stdafx.h"
#include "cObj_Camera.h"


cObj_Camera* g_pCamera = cObj_Camera::GetInstance();

cObj_Camera::cObj_Camera()
	: m_fDist(1)
	, m_fFoV(60)
	, m_fFar(1000)
	, m_fNear(1)
	, m_vDefault(0, 0, 0)
	, m_rayMouse()
	, m_eCameraMode(FLY_VIEW)
{
	D3DXMatrixIdentity(&m_matProj);
	m_matView = m_matProj;
	m_pvTargetPos = &m_vDefault;
}


cObj_Camera::~cObj_Camera()
{
}

void cObj_Camera::Setup()
{
	UpdateProjection();
	SetPosition(10, 10, 10);
}

void cObj_Camera::Update()
{
	if (g_pInput->IsKeyDown('F'))
		m_eCameraMode = CAMERA_MODE::FLY_VIEW;

	if (g_pInput->IsKeyDown('G'))
	{
		m_eCameraMode = CAMERA_MODE::ORIGIN_VIEW;
		m_vDefault = D3DXVECTOR3(0, 0, 0);
	}

	switch (m_eCameraMode)
	{
	case CAMERA_MODE::FLY_VIEW:
		UpdateFlyView();
		break;

	case CAMERA_MODE::ORIGIN_VIEW:
		UpdateOriginView();
		break;
	}

	UpdateView();
	MousePickingRay(&m_rayMouse);
}


void cObj_Camera::UpdateView()
{
	D3DXMatrixLookAtLH(&m_matView, &m_vPos, m_pvTargetPos, &D3DXVECTOR3(0, 1, 0));
	g_pDevice->SetTransform(D3DTS_VIEW, &m_matView);
}

void cObj_Camera::UpdateProjection()
{
	GetClientRect(g_hWnd, &m_rcClient);
	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DXToRadian(m_fFoV),
		m_rcClient.right / (float)m_rcClient.bottom, m_fNear, m_fFar);

	g_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);

	m_fZBuffer = 1.0f / tan(D3DXToRadian(m_fFoV / 2.0f));
}

void cObj_Camera::SetTarget(D3DXVECTOR3 * pvTargetPos)
{
	m_pvTargetPos = pvTargetPos;
}

void cObj_Camera::MousePickingRay(OUT cRay * prayMouse)
{
	D3DXMATRIXA16 matViewIn;
	D3DXMatrixInverse(&matViewIn, NULL, &m_matView);

	POINT mousePos = g_pInput->GetMousePos();

	prayMouse->m_vDir.x = mousePos.x * 2.f - m_rcClient.right;
	prayMouse->m_vDir.y = m_rcClient.bottom - mousePos.y * 2.f;
	prayMouse->m_vDir.z = (float)m_rcClient.bottom * m_fZBuffer;

	D3DXVec3TransformNormal(&prayMouse->m_vDir, &prayMouse->m_vDir, &matViewIn);
	D3DXVec3Normalize(&prayMouse->m_vDir, &prayMouse->m_vDir);

	prayMouse->m_vOri = m_vPos;
}

cRay cObj_Camera::GetMouseRay() const
{
	return  m_rayMouse;
}

void cObj_Camera::UpdateFlyView()
{
	if (g_pInput->IsKeyPress(VK_RBUTTON))
	{
		m_vRot.x += g_pInput->GetMouseInterval().y * CAMERA_ROTATE_SPEED;
		m_vRot.y += g_pInput->GetMouseInterval().x * CAMERA_ROTATE_SPEED;

		if (m_vRot.x > 80) m_vRot.x = 80;
		if (m_vRot.x < -20) m_vRot.x = -20;
	}

	UpdateRotation();
	UpdateDirection();

	if (g_pInput->IsKeyPress('W'))
		m_vPos += m_vDir * CAMERA_MOVE_SPEED;

	if (g_pInput->IsKeyPress('S'))
		m_vPos -= m_vDir * CAMERA_MOVE_SPEED;

	D3DXVec3TransformCoord(&m_vDefault
		, &D3DXVECTOR3(0, 0, m_fDist), &m_matR);

	m_vDefault += m_vPos;
}

void cObj_Camera::UpdateOriginView()
{
	if (g_pInput->IsKeyPress(VK_RBUTTON))
	{
		m_vRot.x += g_pInput->GetMouseInterval().y * CAMERA_ROTATE_SPEED;
		m_vRot.y += g_pInput->GetMouseInterval().x * CAMERA_ROTATE_SPEED;

		if (m_vRot.x > 80) m_vRot.x = 80;
		if (m_vRot.x < -20) m_vRot.x = -20;
	}

	if (g_pInput->GetMouseWheel())
		m_fDist -= g_pInput->GetMouseWheel() * CAMERA_ZOOM_SPEED;

	if (m_fDist < 5)
		m_fDist = 5;

	UpdateRotation();

	D3DXVec3TransformCoord(&m_vPos
		, &D3DXVECTOR3(0, 0, -m_fDist), &m_matR);
}
