#pragma once

class cObj_Sphere	:
	public cGameObject
{
private:
	LPD3DXMESH	m_pMesh;

public:
	cObj_Sphere();
	~cObj_Sphere();
	
	void Render();
};

