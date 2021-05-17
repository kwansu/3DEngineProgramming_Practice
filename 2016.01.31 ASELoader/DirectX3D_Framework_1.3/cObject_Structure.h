#pragma once
#include "cObject.h"

class cObject_Structure
	: public cObject
{
protected:
	cMesh*		m_pMesh;
	cCollider*	m_pCollider;
	
public:
	cObject_Structure();
	~cObject_Structure();
	void Setup();
	void Update();
	void Render();
};

