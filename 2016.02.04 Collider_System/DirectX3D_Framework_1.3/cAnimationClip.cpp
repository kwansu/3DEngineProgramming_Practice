#include "stdafx.h"
#include "cAnimationClip.h"


cAnimationClip::cAnimationClip()
{
}


cAnimationClip::~cAnimationClip()
{
}


void cAnimationClip::PushAnimationKey(cAnimationKey* pAniKey)
{
	m_aAnimationKey.push_back(*pAniKey);
}


D3DXMATRIXA16 cAnimationClip::GetAnimationLocalTM(DWORD dwKeyTime)
{
	int i;

	for (i = 0; i < m_aAnimationKey.size(); ++i)
	{
		if (m_aAnimationKey[i].m_fKeyTime > dwKeyTime)
			break;
	}

	float t = m_aAnimationKey[i].m_fKeyTime - m_aAnimationKey[i - 1].m_fKeyTime;

	t = (dwKeyTime - m_aAnimationKey[i - 1].m_fKeyTime) / t;

	D3DXVECTOR3 vPos;
	D3DXVec3Lerp(&vPos, &m_aAnimationKey[i].m_vPos, &m_aAnimationKey[i - 1].m_vPos, t);
	D3DXMatrixTranslation(&m_matT, vPos.x, vPos.y, vPos.z);

	D3DXQUATERNION vQua;
	D3DXQuaternionSlerp(&vQua, &m_aAnimationKey[i].m_vQuaternion, &m_aAnimationKey[i - 1].m_vQuaternion, t);
	D3DXMatrixRotationQuaternion(&m_matR, &vQua);

	return (m_matR * m_matT);
}
