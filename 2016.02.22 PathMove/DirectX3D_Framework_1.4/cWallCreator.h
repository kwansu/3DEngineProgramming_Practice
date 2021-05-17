#pragma once

class cWallCreator :
	public iInputProcessor
{
	SINGLETONE(cWallCreator);

private:
	struct stPoint
	{
		D3DXVECTOR3		vPos;
		set<int>		setIndex;
		int				nIndex;
	};

private:
	vector<D3DXVECTOR3>	m_vecBuffer;
	vector<stPoint>		m_vecPoint;
	vector<int>			m_vecIndex;
	cMeshData*			m_pMeshData;
	D3DXMATRIXA16		m_matWorld;
	D3DXVECTOR3			m_arrvLine[2];

	stPoint*			m_pPickPoint;
	LPD3DXMESH			m_pMesh;


public:
	void Setup();
	void DebugRender();
	void CreateWall();

private:
	void ConnectPoint(int nIndex);
	void AddPoint(const D3DXVECTOR3& vPos);
	void CalcOutline(stPoint* pPoint ,OUT cMeshData* pMeshData);

	// Input Interface
	void InputProcess(iInputProcessor* pGenerator) override;
};

extern cWallCreator* g_pWallCreator;
