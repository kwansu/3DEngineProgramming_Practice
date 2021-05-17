#pragma once
#include "cObject.h"
#include "ASELoader.h"
#include "cCollider_Terrain.h"
#include "cRay.h"

class cObject_Woman :
	public cObject
{
public:
	cGeometry*	m_pStandRoot;
	cGeometry*	m_pRunRoot;
	cCollider_Terrain*		m_pTerrain;
	
	D3DXVECTOR3	m_vSpeed;
	bool		m_bBottom;
	bool		m_bRun;

	cRay		m_ray;

	ASELoader*	m_pLoader;
	ASELoader*	m_pLoader2;

public:
	cObject_Woman();
	~cObject_Woman();
	void Setup();
	void Update();
	void Render();
};

