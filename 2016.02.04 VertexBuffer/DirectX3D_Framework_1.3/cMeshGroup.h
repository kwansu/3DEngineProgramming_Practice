#pragma once
#include "stVertex.h"

class cMeshGroup : public cReferrers
{
private:
	vector<Vertex_PNT>	m_aVertexPNT;
	MtlTexture*			m_pMtlTex;

public:
	cMeshGroup();
	~cMeshGroup();
	void PushVertexPNT(const Vertex_PNT* pVertex);
	void SetMtlTex(MtlTexture* pMtlTex);
	void Render();
};

