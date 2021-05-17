#pragma once

struct stNode
{
	friend class cCircleList;

	int		data;
	stNode* pNext;
	stNode* pPrev;

	private:
		stNode() {}
		~stNode() {}
};

class cCircleList
{
private:
	stNode* m_pRoot;

public:
	cCircleList();
	~cCircleList();

	void Push(const int& data);
	void Erase(stNode* pNode);
	stNode* GetRootNode();
};

