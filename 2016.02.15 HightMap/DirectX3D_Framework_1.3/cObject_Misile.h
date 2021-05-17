#pragma once
#include "cObject.h"

class cObject_Misile :
	public cObject
{
private:
	LPD3DXMESH				m_pMesh;

	float					m_fInverseMass;
	
	D3DXVECTOR3				m_vVelocity;
	D3DXVECTOR3				m_vAcceleration;
	vector<D3DXVECTOR3>		m_avPowerAccount;

public:
	cObject_Misile();
	~cObject_Misile();
	
	void Setup();
	void Update();
	void Render();
};

