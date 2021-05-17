#pragma once
class cAnimationKey
{
public:
	D3DXVECTOR3		m_vPos;
	D3DXQUATERNION	m_vQuaternion;
	float			m_fKeyTime;

public:
	cAnimationKey();
	~cAnimationKey();
};


struct AnimationKey_R
{
	D3DXQUATERNION	vQuaternion;
	float			fKeyTime;

	AnimationKey_R(D3DXQUATERNION q, float t) : vQuaternion(q), fKeyTime(t)	{}
};


struct AnimationKey_T
{
	D3DXVECTOR3		vPos;
	float			fKeyTime;

	AnimationKey_T(D3DXVECTOR3 p, float t) : vPos(p), fKeyTime(t)	{}
};

