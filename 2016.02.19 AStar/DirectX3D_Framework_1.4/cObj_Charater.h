#pragma once
#include "cGameObject.h"

class cObj_Charater :
	public cGameObject
{
private:
	LPD3DXMESH	m_pMesh;

public:
	cObj_Charater();
	~cObj_Charater();

	void Render();
};

