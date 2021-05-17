#pragma once

struct stPathNode;

struct stEdge
{
	stPathNode*	pNode;
	D3DXVECTOR3	vDir;	// 인접 노드로 향하는 벡터
	float		cost;

	stEdge();
	stEdge(stPathNode* _pNode, D3DXVECTOR3 _vDir, float _cost);
};

class cMeshData;

struct stPathNode
{
	float			F;			// 총 예상 비용 G + H
	float			G;			// 이 노드까자의 비용
	float			H;			// 남은 예상 비용
	bool			isClose;

	bool			isBetween;	// 코어벡터와 [0], [1]의 외적의 부호의 곱 부호
	bool			isPositive;	// 코어벡터와 vecEdge[0] 방향과 외적의 부호
	D3DXVECTOR3		vPos;
	stPathNode*		pParent;	// 길찾기용으로만 사용
	vector<stEdge>	vecEdge;

public:
	stPathNode();

	void UpdateF();
	void UpdateH(const D3DXVECTOR3& vDest);
	void UpdateEdge(list<stPathNode*>& listOpne, const D3DXVECTOR3& vDestination);

	// 파일 입출력
	void OutFile(ofstream& outFile);
	void InFile(ifstream& inFile);
};

