#pragma once

class cWallCreator :
	public iInputProcessor
{
	SINGLETONE(cWallCreator);

private:
	struct stLine
	{
		D3DXVECTOR3		vStart;
		D3DXVECTOR3		vEnd;

		bool IsCrossLine(const stLine& otherLine);
	};

private:
	vector<D3DXVECTOR3>	m_vecVertex;
	vector<stLine>		m_vecLine;

	cMeshData*			m_pMeshData;
	D3DXMATRIXA16		m_matWorld;

public:
	void Setup();
	void DebugRender();
	cMeshData* CreateWall();

private:
	void ConnectPoint(int nIndex);
	void AddVertex(const D3DXVECTOR3& vPos);

	// Input Interface
	void InputProcess(iInputProcessor* pGenerator) override;
};

extern cWallCreator* g_pWallCreator;
