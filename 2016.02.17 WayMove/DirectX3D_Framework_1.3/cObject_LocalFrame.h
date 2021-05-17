#pragma once
#include "cObject_Pyramid.h"

class cObject_LocalFrame :
	public cObject
{
private:
	cObject_Pyramid*	m_pPyramidUp;
	cObject_Pyramid*	m_pPyramidLook;
	cObject_Pyramid*	m_pPyramidRight;

public:
	cObject_LocalFrame();
	~cObject_LocalFrame();
	void Setup();
	void Update();
	void Render();
};

