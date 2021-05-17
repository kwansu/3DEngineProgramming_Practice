#pragma once

class cPathManager
	: public iInputProcessor
{
	SINGLETONE(cPathManager);

private:
	vector<stPathNode>	m_vecPathNode;
	vector<stEdge*>		m_vecpEdge;

	// 시작위치를 빠르게 찾기위해서 맵정렬을 이용
	// 중복된 값은 더해서 다시 넣는다.
	// 키는 x값이며, 값은 백터의 인덱스 번호
	map<float, int>		m_mapXAxisSort;

	stPathNode*			m_pStart;
	stPathNode*			m_pDestination;

	D3DXMATRIXA16		m_mat;

	// 노드 편집 모드(디버그용)
	stPathNode*			m_pPickNode;
	cMeshData*			m_pMeshData;
	D3DMATERIAL9		m_mtl;
	D3DXMATRIXA16		m_matWorld;

public:
	void Setup();
	void AddPathNode(const stPathNode &node);
	bool CalcShortestPath(OUT list<D3DXVECTOR3> &listPath, const D3DXVECTOR3 &vS, const D3DXVECTOR3 &vD);

	void DebugRender();

private:
	void ConnectEdge(stPathNode* pOther);
	void CreatePathNode(const D3DXVECTOR3 & vPickPos);

	// Find Path
	stPathNode* FindNearNode(int x);
	stPathNode*	FindSmallestFNode(list<stPathNode*> &listOpen);

	// Input Interface
	void InputProcess();
};


extern cPathManager* g_pPathManager;