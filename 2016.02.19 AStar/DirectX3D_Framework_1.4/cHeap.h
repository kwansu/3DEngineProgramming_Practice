#pragma once

class Heap;

class iHeapData
{
	friend class cHeap;

private:
	int	m_nHeapIndex;

public:
	// ���ؼ� ohter�� �� ũ�� true
	virtual bool IsGreaterCompare(iHeapData* pOhter) = 0;
};


class cHeap
{
private:
	vector<iHeapData*>	m_vecNode;

public:
	cHeap();
	~cHeap();

	void Clear();
	void Insert(iHeapData* pNode);
	void UpdateNode(iHeapData* pNode);
	iHeapData* PopFront();			// ��尡 �ϳ��� ������ NULL����
	
private:
	bool IsSwapNode(iHeapData* pChildNode);
};

