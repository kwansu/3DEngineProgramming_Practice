#pragma once
#include "cObject.h"
class cObject_MouseMark :
	public cObject
{
private:
	ID3DXMesh*		m_pMesh;
	D3DMATERIAL9	m_mtl;

public:
	cObject_MouseMark();
	~cObject_MouseMark();
	void Setup();
	void Update();
	void Render();
	void SetMark(const D3DXVECTOR3* pvDir, const D3DXVECTOR3* pvPos);
};

