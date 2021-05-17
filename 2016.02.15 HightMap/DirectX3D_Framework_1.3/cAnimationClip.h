#pragma once
#include "cAnimationKey.h"

class cAnimationClip
{
private:
	vector<cAnimationKey>	m_aAnimationKey;
	D3DXMATRIXA16			m_matT;
	D3DXMATRIXA16			m_matR;

public:
	cAnimationClip();
	~cAnimationClip();
	void PushAnimationKey(cAnimationKey* pAniKey);
	D3DXMATRIXA16 GetAnimationLocalTM(DWORD dwKeyTime);
};

