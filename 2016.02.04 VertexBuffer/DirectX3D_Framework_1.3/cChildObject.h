#pragma once
#include "cObject.h"

class cChildObject
{
protected:
	cObject*		m_pChild;
	D3DXMATRIXA16*	m_pmatParentT;
	D3DXMATRIXA16*	m_pmatParentR;
	D3DXMATRIXA16	m_matLocal;

public:
	cChildObject();
	~cChildObject();
	void Setup(cObject* pChild, D3DXMATRIXA16* pmatParentT,
		D3DXMATRIXA16* pmatParentR, D3DXMATRIXA16& matLocal);
	void Update();
	void Render();
	cObject* GetChildObject();
};

