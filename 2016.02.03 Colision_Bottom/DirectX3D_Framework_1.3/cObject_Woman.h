#pragma once
#include "cObject.h"
#include "cGeometry.h"
#include "cTerrain.h"
#include "cRay.h"

class cObject_Woman :
	public cObject
{
public:
	cGeometry*	m_pRoot;
	cTerrain*	m_pTerrain;
	
	D3DXVECTOR3	m_vSpeed;
	bool		m_bBottom;

	cRay		m_ray;

public:
	cObject_Woman();
	~cObject_Woman();
	void Setup();
	void Update();
	void Render();
};

