#include "stdafx.h"
#include "stPathNode.h"


stEdge::stEdge()
	: pNode(NULL)
	, vDir(0, 0, 0)
	, cost(0)
{
}

stEdge::stEdge(stPathNode * _pNode, D3DXVECTOR3 _vDir, float _cost)
	: pNode(_pNode)
	, vDir(_vDir)
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

void stPathNode::UpdateEdge(list<stPathNode*>& listOpne, const D3DXVECTOR3& vDestination)
{
	stPathNode* pNode;

	for (int i = 0; i < vecEdge.size(); ++i)
	{
		pNode = vecEdge[i].pNode;
		if (pNode->isClose)
			continue;

		if (pNode->pParent == NULL)
		{
			pNode->UpdateH(vDestination);
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

void stPathNode::OutFile(ofstream & outFile)
{
	outFile << F << endl;
	outFile << G << endl;
	outFile << H << endl;
	//outFile << vNor.x << endl;
	//outFile << vNor.y << endl;
	//outFile << vNor.z << endl;
	outFile << isBetween << endl;
	outFile << isPositive << endl;
	outFile << vPos.x << endl;
	outFile << vPos.y << endl;
	outFile << vPos.z << endl;
}

void stPathNode::InFile(ifstream & inFile)
{
	inFile >> F >> G >> H;
	inFile >> isBetween;
	inFile >> isPositive;
	//inFile >> vNor.x >> vNor.y >> vNor.z;
	inFile >> vPos.x >> vPos.y >> vPos.z;
}

