#pragma once
#include "cAnimationClip.h"

class ASELoader;

class cGeometry
{
	friend class ASELoader;
protected:
	cGeometry*				m_pParent;
	vector<cGeometry*>		m_apChild;

	D3DMATERIAL9			m_mtl;
	LPDIRECT3DTEXTURE9		m_pTexture;
	IDirect3DVertexBuffer9*	m_pVertexBuffer;
	int						m_nVertexSize;

	vector<AnimationKey_R>	m_aAniRot;
	vector<AnimationKey_T>	m_aAniPos;

	D3DXMATRIXA16			m_matLocal;
	D3DXMATRIXA16			m_matWorld;
	D3DXMATRIXA16			m_matR;
	D3DXMATRIXA16			m_matT;

public:
	static DWORD			s_dwTick;

	cGeometry();
	~cGeometry();

	virtual void Update();
	virtual void Render(D3DXMATRIXA16* pmatParent);
	void UpdateLocal(DWORD dwTick = s_dwTick);
};

