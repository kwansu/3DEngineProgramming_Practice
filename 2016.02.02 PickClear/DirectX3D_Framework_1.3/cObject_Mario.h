#pragma once
#include "cObject_Limbs.h"
#include "cObject_Mario_Head.h"
#include "cCollider_Sphere.h"

#define GRVITY_ACCELERATION	0.1f
#define MARIO_ACCELERATION	0.03f
#define MARIO_ROTATE_SPEED	3.0f
#define	MARIO_JUMP_HEIGHT	25.f
#define MARIO_JUMP_POWER	sqrt(2.f*GRVITY_ACCELERATION*MARIO_JUMP_HEIGHT)

#define ROUND_TIME	5.0f
#define SIDE_LENGTH	100.0f

class cObject_Mario :
	public cObject_Cube
{
private:
	cObject_Mario_Head*			m_pChildHead;
	cObject_Limbs*				m_pChildLArm;
	cObject_Limbs*				m_pChildRArm;
	cObject_Limbs*				m_pChildLLeg;
	cObject_Limbs*				m_pChildRLeg;

protected:
	vector<D3DXVECTOR3>		m_aWayPoint;
	float					m_fActionTime;
	DWORD					m_tEnd, m_tDelta;

public:
	cObject_Mario();
	~cObject_Mario();
	void Setup();
	void Update();
	void Render();
	void InterpolationPosition(OUT D3DXVECTOR3* pOut, const D3DXVECTOR3* pStartPos
		, const D3DXVECTOR3* pEndPos, const float ratio);
};

