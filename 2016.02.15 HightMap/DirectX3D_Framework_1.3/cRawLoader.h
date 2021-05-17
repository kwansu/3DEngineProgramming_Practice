#pragma once

struct stTerrainPlane
{
	vector<Vertex_PNT>	vertex;
	int					sideLen;

	Vertex_PNT& operator()(int row, int col)
	{
		return vertex[row + col*sideLen];
	}
	Vertex_PNT& operator[](int index)
	{
		return vertex[index];
	}
	void Push(Vertex_PNT pnt)
	{
		vertex.push_back(pnt);
	}
};

template <typename T>
struct stSquareVector
{
	vector<T>	vecData;
	int			sideLen;

	T& operator()(int row, int col)
	{
		return vecData[row + col*sideLen];
	}
};


class cRawLoader
{
	vector<Vertex_PNT>	m_vecVertex;
	LPD3DXMESH			m_pMesh;
	int					m_nLen;
	
public:
	cRawLoader();
	~cRawLoader();

	LPD3DXMESH LoadRaw(char* szFileName, OUT vector<D3DXVECTOR3> &vecPos);

private:
	void CreateMesh();
};

