#pragma once
#include "cObj_Mesh.h"
#include "cCollider_Box.h"

class cObj_Box :
	public cObj_Mesh
{
private:
	cCollider_Box*	m_pCollBox;

public:
	cObj_Box();
	~cObj_Box();

	void Setup() override;
	void Update() override;
};

