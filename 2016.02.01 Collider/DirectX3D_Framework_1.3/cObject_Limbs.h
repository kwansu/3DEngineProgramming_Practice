#pragma once
#include "cObject_Cube.h"

class cObject_Limbs :
	public cObject_Cube
{
protected:
	D3DXMATRIXA16*	m_pmatParent;
	D3DXMATRIXA16	m_matLocal;
	float			m_fSwingSpeed;
	bool			m_bWalk;
	bool			m_bRight;
	
public:
	cObject_Limbs(bool bRight);
	~cObject_Limbs();
	void Setup(D3DXMATRIXA16* pmatParent, float px, float py, float pz);
	void Update();
	void Render();
	void Walking();
};

