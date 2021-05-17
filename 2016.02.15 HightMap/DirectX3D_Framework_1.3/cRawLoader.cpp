#include "stdafx.h"
#include "cRawLoader.h"


cRawLoader::cRawLoader()
	: m_pMesh(NULL)
	, m_nLen(0)
{
}


cRawLoader::~cRawLoader()
{
}

LPD3DXMESH cRawLoader::LoadRaw(char * szFim_nLename, OUT vector<D3DXVECTOR3> &vecPos)
{
	ifstream ifRaw(szFim_nLename, ios::in | ios::binary);

	ifRaw.seekg(0, ios::end);
	m_nLen = ifRaw.tellg();
	m_nLen = sqrt(m_nLen);
	ifRaw.seekg(0, ios::beg);


	if (!ifRaw.is_open())
		assert("cRawLoader->LoadRaw : file open failed");

	D3DXVECTOR2 t;
	unsigned char cHeightData;

	//while (!ifRaw.eof())
	//{
	//	ifRaw.read((char*)&cHeightData, sizeof(char));

	//	m_vecVertex.push_back
	//}

	for (int j = 0; j < m_nLen; ++j)
	{
		for (int i = 0; i < m_nLen; ++i)
		{
			ifRaw.read((char*)&cHeightData, sizeof(char));

			m_vecVertex.push_back(Vertex_PNT(D3DXVECTOR3(i, cHeightData*0.1f, j)));
		}
	}

	ifRaw.close();

	int n = 0;
	for (int j = 0; j < m_nLen; ++j)
	{
		for (int i = 0; i < m_nLen; ++i)
		{
			m_vecVertex[n].t = D3DXVECTOR2(i / (float)m_nLen, j / (float)m_nLen);

			if (i == 0 || i == m_nLen - 1 || j == 0 || j == m_nLen - 1)
			{
				m_vecVertex[n++].n = D3DXVECTOR3(0, 1, 0);
			}
			else
			{
				D3DXVECTOR3 a = m_vecVertex[n + 1].p - m_vecVertex[n - 1].p;
				D3DXVECTOR3 b = m_vecVertex[n + m_nLen].p - m_vecVertex[n - m_nLen].p;
				D3DXVec3Cross(&m_vecVertex[n++].n, &b, &a);
			}
		}
	}

	for each(auto vertex in m_vecVertex)
	{
		vecPos.push_back(vertex.p);
	}

	CreateMesh();

	return m_pMesh;
}

void cRawLoader::CreateMesh()
{
	D3DXCreateMeshFVF((m_nLen - 1) * (m_nLen - 1) * 2,
		m_vecVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		Vertex_PNT::FVF,
		g_pDevice,
		&m_pMesh);

	// vertex buffer
	Vertex_PNT* pVertex;
	m_pMesh->LockVertexBuffer(0, (LPVOID*)&pVertex);
	memcpy(pVertex, &m_vecVertex[0], m_vecVertex.size() * sizeof(Vertex_PNT));
	m_pMesh->UnlockVertexBuffer();

	// index buffer
	unsigned* pI;
	m_pMesh->LockIndexBuffer(0, (LPVOID*)&pI);

	int n = 0;
	for (int j = 0; j < m_nLen - 1; ++j)
	{
		for (int i = 0; i < m_nLen - 1; ++i)
		{
			pI[n++] = i + j*m_nLen;
			pI[n++] = i + (j + 1)*m_nLen;
			pI[n++] = (i + 1) + j*m_nLen;

			pI[n++] = (i + 1) + j*m_nLen;
			pI[n++] = i + (j + 1)*m_nLen;
			pI[n++] = (i + 1) + (j + 1)*m_nLen;
		}
	}

	m_pMesh->UnlockIndexBuffer();

	// attribute buffer
	DWORD* pA;
	m_pMesh->LockAttributeBuffer(0, &pA);

	n = 0;
	for (int j = 0; j < m_nLen - 1; ++j)
	{
		for (int i = 0; i < m_nLen - 1; ++i)
		{
			pA[n++] = 0;
			pA[n++] = 0;
		}
	}

	m_pMesh->UnlockAttributeBuffer();

}
