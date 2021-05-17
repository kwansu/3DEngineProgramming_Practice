#pragma once
#include "cGameObject.h"
#include "cMeshData.h"

class cObj_Mesh :
	public cGameObject
{
protected:
	cMeshData*	m_pMeshData;

public:
	cObj_Mesh();
	~cObj_Mesh();

	virtual void Update() override;
	virtual void Render() override;
};

