#pragma once
class cDijNode
{
public:
	D3DXVECTOR3			p;
	vector<DijNode*>	vecChild;

public:
	cDijNode();
	~cDijNode();
};

