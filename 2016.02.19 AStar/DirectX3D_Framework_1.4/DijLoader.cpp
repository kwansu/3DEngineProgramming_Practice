#include "stdafx.h"
#include "DijLoader.h"
#include "Utility.h"

DijLoader::DijLoader()
{
}


DijLoader::~DijLoader()
{
}

void DijLoader::Load(char * szFileName, OUT vector<DijNode>& vecNode, OUT float **& arrEdgeCost)
{
	ifDij.open(szFileName, ios::in);

	if (!ifDij.is_open())
		assert(false && "DijLoader-> Load : file load failed");

	char sToken[1024];

	while (!ifDij.eof())
	{
		MYFILELOAD::GetToken(ifDij, sToken);

		if (!strcmp(sToken, "NUMNODE"))
		{
			int n;
			MYFILELOAD::GetInteger(ifDij, &n);

			arrEdgeCost = new float*[n];

			for (int i = 0; i < n; ++i)
			{
				arrEdgeCost[i] = new float[n];
				for (int j = 0; j < n; ++j)
				{
					arrEdgeCost[i][j] = FLT_MAX;
				}
			}
		}
		else if (!strcmp(sToken, "NODE"))
		{
			ProcessNode(vecNode);
		}
		else if (!strcmp(sToken, "EDGE"))
		{
			ProcessEdge(vecNode, arrEdgeCost);
		}
	}

	ifDij.close();
}

void DijLoader::CopyVertexEdge(vector<stVertex_PC>& vertexCopy)
{
	for each(auto node in vertexEdge)
		vertexCopy.push_back(node);
}

void DijLoader::ProcessNode(OUT vector<DijNode>& vecNode)
{

	D3DXVECTOR3 p;
	MYFILELOAD::GetFloat(ifDij, &p.x);
	MYFILELOAD::GetFloat(ifDij, &p.x);
	MYFILELOAD::GetFloat(ifDij, &p.y);
	MYFILELOAD::GetFloat(ifDij, &p.z);

	vecNode.push_back(DijNode(p));
}

void DijLoader::ProcessEdge(IN OUT vector<DijNode>& vecNode, OUT float **& arrEdgeCost)
{
	int i, j;

	MYFILELOAD::GetInteger(ifDij, &i);
	MYFILELOAD::GetInteger(ifDij, &j);

	float d = D3DXVec3Length(&(vecNode[i].p - vecNode[j].p));

	vecNode[i].vecChild.push_back(&vecNode[j]);
	vecNode[j].parent = &vecNode[i];

	vertexEdge.push_back(stVertex_PC(vecNode[i].p));
	vertexEdge.push_back(stVertex_PC(vecNode[j].p));

	arrEdgeCost[i][j] = arrEdgeCost[j][i] = d;
}

