#pragma once
#include "cObject.h"
#include "cGeometry.h"

class cObject_Woman :
	public cObject
{
public:
	cGeometry*			m_pRoot;
	cCollider_Sphere*	m_pCollider;

public:
	cObject_Woman();
	~cObject_Woman();
	void Setup();
	void Update();
	void Render();
};

