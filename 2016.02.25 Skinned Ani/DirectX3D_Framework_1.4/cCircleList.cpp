#include "stdafx.h"
#include "cCircleList.h"

cCircleList::cCircleList()
	: m_pRoot(NULL)
{
}


cCircleList::~cCircleList()
{
}

void cCircleList::Push(const int & data)
{
	if (!m_pRoot)
	{
		m_pRoot = new stNode;
		m_pRoot->data = data;
		m_pRoot->pNext = m_pRoot;
		m_pRoot->pPrev = m_pRoot;
		return;
	}

	stNode* pNode = m_pRoot;
	m_pRoot = new stNode;
	m_pRoot->data = data;

	m_pRoot->pNext = pNode;
	m_pRoot->pPrev = pNode->pPrev;

	pNode->pPrev->pNext = m_pRoot;
	pNode->pPrev = m_pRoot;
}

void cCircleList::Erase(stNode * pNode)
{
	if (!pNode)
		return;

	if (pNode->pNext == pNode)
	{
		delete pNode;
		pNode = NULL;
		return;
	}

	if (m_pRoot == pNode)
		m_pRoot = pNode->pPrev;

	pNode->pPrev->pNext = pNode->pNext;
	pNode->pNext->pPrev = pNode->pPrev;

	pNode = NULL;
}

stNode * cCircleList::GetRootNode()
{
	return m_pRoot;
}
