#pragma once

// 입출력을 위한 Edge연결정보
// 연결되는 두 노드의 인덱스를 담는다.
struct stConnectData
{
	int		nIndex1;
	int		nIndex2;
	float	cost;

	void OutFile(ofstream& outFile)
	{
		outFile << nIndex1 << endl;
		outFile << nIndex2 << endl;
		outFile << cost << endl;
	}

	void InFile(ifstream& inFile)
	{
		inFile >> nIndex1 >> nIndex2 >> cost;
	}
};


class cPathManager
	: public iInputProcessor
{
	SINGLETONE(cPathManager);

private:
	vector<stPathNode>		m_vecPathNode;
	vector<stConnectData>	m_vecConnectData;
	
	// 시작위치를 빠르게 찾기위해서 맵정렬을 이용
	// 중복된 값은 더해서 다시 넣는다.
	// 키는 x값이며, 값은 백터의 인덱스 번호
	map<float, int>			m_mapXAxisSort;

	//시작 위치를 노드화. 부모가없고, 가장가까운 노드를 자식으로 한다. 위치값만 변경할 것.
	stPathNode				m_nodeStart;
	stPathNode*				m_pDestination;		// 끝 위치와 가장가까운 노드
	D3DXVECTOR3				m_vDestiation;

	// 노드 편집 모드(디버그용)
	stPathNode*				m_pPickNode;
	cMeshData*				m_pMeshData;
	D3DXMATRIXA16			m_matWorld;
	D3DXMATRIXA16			m_mat;

	vector<D3DXVECTOR3>		m_vecCore;			// 랜더링을 위한 좌표

	int						m_nPicked;
	int						m_nPick;
	bool					m_isViewCore;

public:
	void Setup();
	void DebugRender();
	void SaveDataFile();
	void LoadDataFile();

	void AddPathNode(const stPathNode &node);	// 오브젝트 설치 후, 노드 자동생성. 미구현.
	bool CalcShortestPath(OUT list<D3DXVECTOR3> &listPath, const D3DXVECTOR3 &vS, const D3DXVECTOR3 &vD);

private:
	void ConnectEdge(stPathNode* pOther);
	void CreatePathNode(const D3DXVECTOR3 & vPickPos);
	void EmplaceOutlineCore(const D3DXVECTOR3 & vPickPos);	// 충돌 설정을 위한 중심 설정. 왠만하면 끝에 한번만 호출
	void CalcFastPath(OUT list<D3DXVECTOR3> &listPath);

	// Find Path
	stPathNode* FindNearNode(int x);
	stPathNode* FindNearNode(const D3DXVECTOR3& vOri);
	stPathNode*	FindSmallestFNode(list<stPathNode*> &listOpen);

	// Input Interface
	void InputProcess(iInputProcessor* pGenerator);
};


extern cPathManager* g_pPathManager;