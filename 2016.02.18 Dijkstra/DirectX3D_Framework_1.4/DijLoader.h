#pragma once

struct DijNode
{
	D3DXVECTOR3			p;
	DijNode*			parent;
	vector<DijNode*>	vecChild;
	bool				isPath;
	bool				isPicked;
	D3DMATERIAL9		mtl;

	DijNode(D3DXVECTOR3 pos) : p(pos), isPath(false), parent(NULL), isPicked(false)
	{
		ZeroMemory(&mtl, sizeof(D3DMATERIAL9));

		mtl.Diffuse = D3DXCOLOR(1, 1, 1, 1);
	}

	void Render(LPD3DXMESH pMesh)
	{
		D3DXMATRIXA16 mat;

		if(isPicked)
			mtl.Diffuse = D3DXCOLOR(1, 0, 0, 1);
		else
			mtl.Diffuse = D3DXCOLOR(1, 1, 1, 1);

		g_pDevice->SetMaterial(&mtl);

		D3DXMatrixTranslation(&mat, p.x, p.y, p.z);
		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		pMesh->DrawSubset(0);

		if (isPath && parent)
		{
			D3DXVECTOR3 v[2];

			v[0] = p;
			v[1] = parent->p;

			D3DXMatrixIdentity(&mat);
			mtl.Diffuse = D3DXCOLOR(0, 1, 0, 1);
			g_pDevice->SetMaterial(&mtl);
			g_pDevice->SetTransform(D3DTS_WORLD, &mat);
			g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, &v, sizeof(D3DXVECTOR3));
		}
	}

};

class DijLoader
{
private:
	ifstream	 ifDij;
	vector<stVertex_PC>	vertexEdge;

public:
	DijLoader();
	~DijLoader();

	void Load(char* szFileName, OUT vector<DijNode>& vecNode, OUT float** &arrEdgeCost);
	void CopyVertexEdge(vector<stVertex_PC> &vertexCopy);

private:
	void ProcessNode(OUT vector<DijNode>& vecNode);
	void ProcessEdge(IN OUT vector<DijNode>& vecNode, OUT float** &arrEdgeCost);
};

