#pragma once

struct stPathNode;

struct stEdge
{
	stPathNode*	pNode;
	D3DXVECTOR3	vDir;	// ���� ���� ���ϴ� ����
	float		cost;

	stEdge();
	stEdge(stPathNode* _pNode, D3DXVECTOR3 _vDir, float _cost);
};

class cMeshData;

struct stPathNode
{
	float			F;			// �� ���� ��� G + H
	float			G;			// �� �������� ���
	float			H;			// ���� ���� ���
	bool			isClose;

	bool			isBetween;	// �ھ�Ϳ� [0], [1]�� ������ ��ȣ�� �� ��ȣ
	bool			isPositive;	// �ھ�Ϳ� vecEdge[0] ����� ������ ��ȣ
	D3DXVECTOR3		vPos;
	stPathNode*		pParent;	// ��ã������θ� ���
	vector<stEdge>	vecEdge;

public:
	stPathNode();

	void UpdateF();
	void UpdateH(const D3DXVECTOR3& vDest);
	void UpdateEdge(list<stPathNode*>& listOpne, const D3DXVECTOR3& vDestination);

	// ���� �����
	void OutFile(ofstream& outFile);
	void InFile(ifstream& inFile);
};

