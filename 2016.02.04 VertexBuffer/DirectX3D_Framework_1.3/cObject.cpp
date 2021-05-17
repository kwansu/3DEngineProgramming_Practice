#include "stdafx.h"
#include "cObject.h"


cObject::cObject()
	: m_vPos(0, 0, 0)
	, m_vLook(0, 0, 1), m_vUp(0, 1, 0), m_vRight(1, 0, 0)
	, m_fAngleX(0), m_fAngleY(0), m_pColliderS(NULL)
{
	D3DXMatrixIdentity(&m_matWolrd);
	m_matScale = m_matWolrd;
	m_matTrl = m_matWolrd;
	m_matRot = m_matWolrd;
}


cObject::~cObject()
{
	SafeDelete(m_pColliderS);
}


void cObject::SetPosition(const D3DXVECTOR3* pvPos)
{
	m_vPos = *pvPos;
}


void cObject::SetDirection(const D3DXVECTOR3* pvDir, const D3DXVECTOR3* pvUp)
{
	if (*pvDir == *pvUp)
		assert("cObject SetDirection Equal dir == up");

	D3DXMatrixLookAtLH(&m_matRot, &D3DXVECTOR3(0, 0, 0)
		, pvDir, pvUp);
}


void cObject::SetPosition(float px, float py, float pz)
{
	m_vPos.x = px;	m_vPos.y = py;	m_vPos.z = pz;
}


void cObject::SetRotation(float rx, float ry, float rz)
{
	m_fAngleX = rx;	m_fAngleY = ry;
}


void cObject::SetScale(float sx, float sy, float sz)
{
	D3DXMatrixScaling(&m_matScale, sx, sy, sz);
}


void cObject::SetWorldMatirx(const D3DXMATRIXA16* pmatWorld)
{
	m_matWolrd = *pmatWorld;
}


void cObject::SetWorldMatirxFromParent(const D3DXMATRIXA16* pmatWorld)
{
	m_matWolrd *= *pmatWorld;
}


//  현재 오브젝트의 위치, 회전값등으로 메트릭스를 변경하는 함수
void cObject::UpdateTranslation()
{
	D3DXMatrixTranslation(&m_matTrl, m_vPos.x
		, m_vPos.y, m_vPos.z);
}


void cObject::UpdateRotation()
{
	D3DXMATRIXA16 matY;
	D3DXMatrixRotationX(&m_matRot, D3DXToRadian(m_fAngleX));
	D3DXMatrixRotationY(&matY, D3DXToRadian(m_fAngleY));

	m_matRot *= matY;
}


void cObject::UpdateWorld()
{
	UpdateTranslation();
	UpdateRotation();
	m_matWolrd = m_matScale * m_matRot * m_matTrl;
}


void cObject::UpdateDirection()
{
	D3DXVec3TransformNormal(&m_vLook, &D3DXVECTOR3(0, 0, 1), &m_matRot);
	D3DXVec3TransformNormal(&m_vUp, &D3DXVECTOR3(0, 0, 1), &m_matRot);
	D3DXVec3TransformNormal(&m_vRight, &D3DXVECTOR3(0, 0, 1), &m_matRot);
}


// 오브젝트의 현재 메트릭스값으로 D3DXVECTOR3를 변환시켜주는 함수
void cObject::TransformPosition(D3DXVECTOR3* pvOut)
{
	D3DXVec3TransformCoord(pvOut, pvOut, &m_matWolrd);
}


void cObject::TransformVector(D3DXVECTOR3* pvOut)
{
	D3DXVec3TransformNormal(pvOut, pvOut, &m_matRot);
}
