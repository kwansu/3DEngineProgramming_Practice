#include "stdafx.h"
#include "cHeap.h"


cHeap::cHeap()
{
}

cHeap::~cHeap()
{
}

void cHeap::Clear()
{
	m_vecNode.clear();
}

void cHeap::Insert(iHeapData * pNode)
{
	int index = m_vecNode.size();

	pNode->m_nHeapIndex = index;
	m_vecNode.push_back(pNode);

//	UpdateNode(index);
}

void cHeap::UpdateNode(iHeapData * pNode)
{
	while (pNode->m_nHeapIndex > 0)
	{
		if (!IsSwapNode(pNode))
			break;
	}
}

iHeapData * cHeap::PopFront()
{
	if (m_vecNode.empty())
		return NULL;

	iHeapData* pResult = m_vecNode[0];

	int size = m_vecNode.size();

	m_vecNode[0] = m_vecNode[--size];
	m_vecNode[0]->m_nHeapIndex = 0;
	m_vecNode.pop_back();

	if (m_vecNode.empty())
		return pResult;

	iHeapData* pNode = m_vecNode[0];
	iHeapData* pChildNodeR = NULL;
	iHeapData* pChildNodeL = NULL;
	int childIndex;

	while (true)
	{
		childIndex = (pNode->m_nHeapIndex * 2) + 1;

		if (childIndex >= size)	break;

		pChildNodeL = m_vecNode[childIndex++];

		if (childIndex >= size)
		{
			IsSwapNode(pChildNodeL);
			break;
		}

		pChildNodeR = m_vecNode[childIndex];

		if (pChildNodeL->IsGreaterCompare(pChildNodeR))
		{
			if (!IsSwapNode(pChildNodeL))
				break;
		}
		else
		{
			if (!IsSwapNode(pChildNodeR))
				break;
		}
	}

	return pResult;
}

bool cHeap::IsSwapNode(iHeapData * pChildNode)
{
	int parentIndex = (pChildNode->m_nHeapIndex - 1) / 2;
	int childIndex = pChildNode->m_nHeapIndex;
	iHeapData* pSwap = pChildNode;

	if (pChildNode->IsGreaterCompare(m_vecNode[parentIndex]))
	{
		pChildNode->m_nHeapIndex = parentIndex;
		m_vecNode[parentIndex]->m_nHeapIndex = childIndex;

		m_vecNode[childIndex] = m_vecNode[parentIndex];
		m_vecNode[parentIndex] = pSwap;

		return true;
	}

	return false;
}


