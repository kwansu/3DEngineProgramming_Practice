#pragma once
#include "cBone.h"
#include "cAllocateHierarchy.h"
#include "cGameObject.h"

class cSkinningMesh :
	public cGameObject
{
private:
	cBone*						m_pRoot;

	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	bool						m_isChangeAnim;
	float						m_fWeight;
	
public:
	cSkinningMesh();
	~cSkinningMesh();

	void Load(char* szFile, char* szPath);
	void Render();
	void Update();

	void Update(cBone* pBone, const D3DXMATRIXA16& matWorld);
	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);
	void SetAnimaitonTrack(int index);
};

