#include "stdafx.h"
#include "stPathNode.h"


stEdge::stEdge()
	: pNode(NULL)
	, cost(0)
{
}

stEdge::stEdge(stPathNode * _pNode, float _cost)
	: pNode(_pNode)
	, cost(_cost)
{
}

stPathNode::stPathNode()
	: F(FLT_MAX)
	, G(FLT_MAX)
	, H(0)
	, isClose(false)
	, vPos(0, 0, 0)
	, pParent(NULL)
{
}

void stPathNode::UpdateF()
{
	F = G + H;
}

void stPathNode::UpdateH(const D3DXVECTOR3 & vDest)
{
	D3DXVECTOR3 vDist = vDest - vPos;

	H = abs(vDist.x) + abs(vDist.y) + abs(vDist.z);
}

void stPathNode::UpdateEdge(list<stPathNode*>& listOpne, stPathNode * pDestination)
{
	stPathNode* pNode;

	for (int i = 0; i < vecEdge.size(); ++i)
	{
		pNode = vecEdge[i].pNode;
		if (pNode->isClose)
			continue;

		if (pNode->pParent == NULL)
		{
			pNode->UpdateH(pDestination->vPos);
			pNode->pParent = this;
			listOpne.push_front(pNode);
		}

		if (pNode->G > G + vecEdge[i].cost)
		{
			pNode->G = G + vecEdge[i].cost;
			pNode->pParent = this;
			pNode->UpdateF();
		}
	}
}

