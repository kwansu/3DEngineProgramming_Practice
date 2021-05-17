#pragma once
#include "cObject.h"
#include "cGeometry.h"
#include "cTerrain.h"
#include "cRay.h"

class cObject_Woman :
	public cObject
{
public:
	cGeometry*	m_pMoveRoot;
	cGeometry*	m_pIdleRoot;

	LPD3DXMESH	m_pShpere;
	
	D3DXVECTOR3	m_vSpeed;
	D3DXVECTOR3	m_vWayPos;
	bool		m_bMove;
	bool		m_bBottom;

	ASELoader*			m_pLoader;
	ASELoader*			m_pLoader2;

public:
	bool		m_bPicked;
	cObject_Woman();
	~cObject_Woman();

	void Setup();
	void Update();
	void Render();

	void UpdatePicked(const D3DXVECTOR3 &vOri, const D3DXVECTOR3 &vDir);
	bool IsPicked(const D3DXVECTOR3 & vOri, const D3DXVECTOR3 & vDir);
};

