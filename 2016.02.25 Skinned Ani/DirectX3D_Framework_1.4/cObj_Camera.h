#pragma once
#include "cGameObject.h"

#define CAMERA_MOVE_SPEED	0.5f
#define CAMERA_ROTATE_SPEED	0.35f
#define CAMERA_ZOOM_SPEED	0.5f

enum CAMERA_MODE
{
	FLY_VIEW, ORIGIN_VIEW, TRAIL_VIEW
};

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

	CAMERA_MODE		m_eCameraMode;

public:
	void Setup();
	void Update();
	void UpdateView();
	void UpdateProjection();
	void SetTarget(D3DXVECTOR3* pvTargetPos);
	void MousePickingRay(OUT cRay* prayMouse);
	cRay GetMouseRay() const;

private:
	void UpdateFlyView();
	void UpdateOriginView();
};


extern cObj_Camera* g_pCamera;
