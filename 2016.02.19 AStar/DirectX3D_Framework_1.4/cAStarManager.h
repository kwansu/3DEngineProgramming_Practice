#pragma once
#include "cHeap.h"

struct stAStarNode : public iHeapData
{
	float			f;
	float			g;
	float			h;
	bool			isClose;
	bool			isBlock;
	bool			isPath;
	stAStarNode*	parent;

	int				x, z;
	
	stAStarNode() : isClose(false), parent(NULL)	{}
	void UpdateF() { f = g + h; }

private:
	bool IsGreaterCompare(iHeapData* pOhter) override;
};

#define NUM_LINE	16
#define g_pAStar	cAStarManager::GetInstance()

class cAStarManager
{
	SINGLETONE(cAStarManager)

private:
	stAStarNode**	m_arrMap;
	int				m_nEndi, m_nEndj;
	int				m_nStarti, m_nStartj;
	LPD3DXMESH		m_pMesh;
	D3DMATERIAL9	m_mtl;

	cHeap			openList;

public:
	void LoadFile(char* szFileName);
	void Render();

	void CalcPath(int x, int y, list<D3DXVECTOR3> &listPath);

private:
	void ProcessRoundNode(int x, int z, int px, int pz, float delta);
	//stAStarNode* ListSort();
};
