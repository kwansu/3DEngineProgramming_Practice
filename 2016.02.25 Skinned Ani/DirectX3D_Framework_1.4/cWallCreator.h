#pragma once

class cWallCreator :
	public iInputProcessor
{
	SINGLETONE(cWallCreator);

private:
	struct stLine
	{
		union
		{
			struct
			{
				D3DXVECTOR3		vStart;
				D3DXVECTOR3		vEnd;
			};
			D3DXVECTOR3			vLine[2];
		};

		stLine() {}
		bool IsCrossLine(const stLine& otherLine) const;
	};

private:
	D3DXVECTOR3			m_vCurPos;
	vector<D3DXVECTOR3>	m_vecVertex;
	vector<stLine>		m_vecLine;
	vector<int>			m_vecIndex;

	cMeshData*			m_pMeshData2;
	cMeshData*			m_pMeshData;
	D3DXMATRIXA16		m_matWorld;
//	unsigned			m_uNumber;
	bool isDraw;

public:
	void Setup();
	void DebugRender();

private:
	void CreateWall();
	void CreateMesh(const vector<int>& vecIndexBuffer, bool isUpCross);
	void AddVertex(const D3DXVECTOR3& vPos);
	bool IsDirectionInside(const D3DXVECTOR3& vPos);
	bool IsCutTriangle(const stLine & line, D3DXVECTOR3 vDir, D3DXVECTOR3 vDir2);

	// Input Interface
	void InputProcess(iInputProcessor* pGenerator) override;
};

extern cWallCreator* g_pWallCreator;
