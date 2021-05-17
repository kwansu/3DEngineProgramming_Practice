#pragma once
#include "cObject_Mario.h"

#define THIRD_LINE_TIME	(ROUND_TIME / 3)

class cObject_ThirdMan :
	public cObject_Mario
{
	//ID3DXMesh*				m_mesh;

public:
	cObject_ThirdMan();
	~cObject_ThirdMan();
	void Update() override;
//	void Render();
};

