#pragma once

struct stPathNode;

struct stEdge
{
	stPathNode*	pNode;
	float		cost;

	stEdge();
	stEdge(stPathNode* _pNode, float _cost);
};

class cMeshData;

struct stPathNode
{
	float			F;			// 총 예상 비용 G + H
	float			G;			// 이 노드까자의 비용
	float			H;			// 남은 예상 비용
	bool			isClose;

	D3DXVECTOR3		vPos;
	stPathNode*		pParent;	// 길찾기용으로만 사용
	vector<stEdge>	vecEdge;

public:
	stPathNode();

	void UpdateF();
	void UpdateH(const D3DXVECTOR3& vDest);
	void UpdateEdge(list<stPathNode*>& listOpne, stPathNode* pDestination);
};

