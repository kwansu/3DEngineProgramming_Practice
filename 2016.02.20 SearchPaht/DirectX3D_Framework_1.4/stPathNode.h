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
	float			F;			// �� ���� ��� G + H
	float			G;			// �� �������� ���
	float			H;			// ���� ���� ���
	bool			isClose;

	D3DXVECTOR3		vPos;
	stPathNode*		pParent;	// ��ã������θ� ���
	vector<stEdge>	vecEdge;

public:
	stPathNode();

	void UpdateF();
	void UpdateH(const D3DXVECTOR3& vDest);
	void UpdateEdge(list<stPathNode*>& listOpne, stPathNode* pDestination);
};

