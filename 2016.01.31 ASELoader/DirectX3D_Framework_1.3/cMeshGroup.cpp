#include "stdafx.h"
#include "cMeshGroup.h"


cMeshGroup::cMeshGroup()
: m_pMtlTex(NULL)
{
}


cMeshGroup::~cMeshGroup()
{
	m_pMtlTex->Release();
	cReferrers::Release();
}


void cMeshGroup::PushVertexPNT(const Vertex_PNT* pVertex)
{
	m_aVertexPNT.push_back(*pVertex);
}


void cMeshGroup::SetMtlTex(MtlTexture* pMtlTex)
{
	pMtlTex->AddRef();
	m_pMtlTex = pMtlTex;
}



void cMeshGroup::Render()
{
	g_pDevice->SetMaterial(&m_pMtlTex->mtl);
	g_pDevice->SetTexture(0, m_pMtlTex->pTex);
	g_pDevice->SetFVF(Vertex_PNT::FVF);

	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST
		, m_aVertexPNT.size() / 3
		, &m_aVertexPNT[0]
		, sizeof(Vertex_PNT));
}
