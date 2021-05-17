#pragma once
#include "cObj_Sphere.h"

namespace ns_OBJ_HUMAN
{
	const float fHUMAN_MOVE_SPEED = 0.1f;
	const float fHUMAN_STOP_RADIUS = 0.2f;
}

class cObj_Human :
	public cObj_Sphere
{
protected:
	D3DXVECTOR3			m_vWayPos;
	list<D3DXVECTOR3>	m_listPath;
	bool				m_bAttack;
	bool				m_bMove;
	float				m_fMoveSpeed;
	float				m_fHitPoint;

public:
	cObj_Human();
	~cObj_Human();

	void Update() override;

	void AddHitPoint(float fDelta);
	void MoveToWayPath();
	void FindPath(const D3DXVECTOR3& vDestination);

private:
	virtual bool IsCollisionAsRay(cRay* pray) override;
};

