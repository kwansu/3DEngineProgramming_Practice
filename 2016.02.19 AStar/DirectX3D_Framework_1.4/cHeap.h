#pragma once

class Heap;

class iHeapData
{
	friend class cHeap;

private:
	int	m_nHeapIndex;

public:
	// 비교해서 ohter가 더 크면 true
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
	iHeapData* PopFront();			// 노드가 하나도 없으면 NULL리턴
	
private:
	bool IsSwapNode(iHeapData* pChildNode);
};

