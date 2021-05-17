#pragma once
#include "cGameObject.h"

#define CAMERA_MOVE_SPEED	0.1f
#define CAMERA_ROTATE_SPEED	0.35f
#define CAMERA_ZOOM_SPEED	0.01f

class cObj_Camera	:
	public cGameObject
{
	SINGLETONE(cObj_Camera);

private:
	float			m_fFoV;
	float			m_fNear;
	float			m_fFar;
	float			m_fDist;
	float			m_fZBuffer;

	D3DXVECTOR3		*m_pvTargetPos, m_vDefault;
	D3DXMATRIXA16	m_matView;
	D3DXMATRIXA16	m_matProj;
	RECT			m_rcClient;
	cRay			m_rayMouse;

public:
	void Setup();
	void Update();
	void UpdateView();
	void UpdateProjection();
	void SetTarget(D3DXVECTOR3* pvTargetPos);
	void MousePickingRay(OUT cRay* prayMouse);
	cRay GetMouseRay() const;
};


extern cObj_Camera* g_pCamera;
