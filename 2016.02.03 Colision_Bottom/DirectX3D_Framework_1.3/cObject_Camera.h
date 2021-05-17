#pragma once
#include "cObject.h"

#define g_pCamera	cObject_Camera::GetInstance()
#define CAMERA_MOVE_SPEED	0.1f
#define CAMERA_ROTATE_SPEED	0.35f
#define CAMERA_ZOOM_SPEED	0.01f

class cObject_Camera :
	public cObject
{
	SINGLETONE(cObject_Camera);

private:
	float			m_fDistance;
	float			m_fFOV;
	float			m_fNear;
	float			m_fFar;
	float			m_fZBuffer;

	D3DXVECTOR3		*m_pvTargetPos, m_vDefault;
	D3DXMATRIXA16	m_matView;
	D3DXMATRIXA16	m_matProj;
	RECT			m_rcClient;

public:
	void Setup();
	void Update();
	void Render();
	void SetTarget(D3DXVECTOR3* pvTargetPos);
	void UpdateView();
	void UpdateProjection();
	void GetMouseLine(OUT D3DXVECTOR3* pvDir, OUT D3DXVECTOR3* pvPos);
};

