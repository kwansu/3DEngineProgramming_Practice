#pragma once

// ������� ���� Edge��������
// ����Ǵ� �� ����� �ε����� ��´�.
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
	
	// ������ġ�� ������ ã�����ؼ� �������� �̿�
	// �ߺ��� ���� ���ؼ� �ٽ� �ִ´�.
	// Ű�� x���̸�, ���� ������ �ε��� ��ȣ
	map<float, int>			m_mapXAxisSort;

	//���� ��ġ�� ���ȭ. �θ𰡾���, ���尡��� ��带 �ڽ����� �Ѵ�. ��ġ���� ������ ��.
	stPathNode				m_nodeStart;
	stPathNode*				m_pDestination;		// �� ��ġ�� ���尡��� ���
	D3DXVECTOR3				m_vDestiation;

	// ��� ���� ���(����׿�)
	stPathNode*				m_pPickNode;
	cMeshData*				m_pMeshData;
	D3DXMATRIXA16			m_matWorld;
	D3DXMATRIXA16			m_mat;

	vector<D3DXVECTOR3>		m_vecCore;			// �������� ���� ��ǥ

	int						m_nPicked;
	int						m_nPick;
	bool					m_isViewCore;

public:
	void Setup();
	void DebugRender();
	void SaveDataFile();
	void LoadDataFile();

	void AddPathNode(const stPathNode &node);	// ������Ʈ ��ġ ��, ��� �ڵ�����. �̱���.
	bool CalcShortestPath(OUT list<D3DXVECTOR3> &listPath, const D3DXVECTOR3 &vS, const D3DXVECTOR3 &vD);

private:
	void ConnectEdge(stPathNode* pOther);
	void CreatePathNode(const D3DXVECTOR3 & vPickPos);
	void EmplaceOutlineCore(const D3DXVECTOR3 & vPickPos);	// �浹 ������ ���� �߽� ����. �ظ��ϸ� ���� �ѹ��� ȣ��
	void CalcFastPath(OUT list<D3DXVECTOR3> &listPath);

	// Find Path
	stPathNode* FindNearNode(int x);
	stPathNode* FindNearNode(const D3DXVECTOR3& vOri);
	stPathNode*	FindSmallestFNode(list<stPathNode*> &listOpen);

	// Input Interface
	void InputProcess(iInputProcessor* pGenerator);
};


extern cPathManager* g_pPathManager;