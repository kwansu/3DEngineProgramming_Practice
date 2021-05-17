#pragma once
#include "cBone.h"

class ASELoader
{
private:
	map<string, cGeometry>			m_mapGeometry;
	map<string, MtlTexture>			m_mapMtlTex;
	map<string, LPDIRECT3DTEXTURE9>	m_mapTexture;

	vector<Vertex_PNT>				m_aVertex;

public:
	cGeometry*						m_pRoot;

private:
	void SetMtlTexture(ifstream* pIfASE);
	void SetGeometry(ifstream* pIfASE);
	D3DXCOLOR GetColor(char* context);
	D3DXVECTOR3 GetVector3(char* context);

public:
	ASELoader();
	~ASELoader();
	cGeometry* LoadASE(char* sFileName);
	void Release();
};

