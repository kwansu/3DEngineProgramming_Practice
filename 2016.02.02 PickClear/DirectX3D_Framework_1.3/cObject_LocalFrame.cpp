#include "stdafx.h"
#include "cObject_LocalFrame.h"


cObject_LocalFrame::cObject_LocalFrame()
{
	//D3DXMATRIXA16 mat;
	//D3DXMatrixIdentity(&mat);

	m_pPyramidLook = new cObject_Pyramid(D3DXCOLOR(1.0f, 0, 0, 1.0f));
	m_pPyramidLook->UpdateWorld();

	m_pPyramidUp = new cObject_Pyramid(D3DXCOLOR(0, 1.0f, 0, 1.0f));
	m_pPyramidUp->SetRotation(90, 90, 0);
	m_pPyramidUp->UpdateWorld();

	m_pPyramidRight = new cObject_Pyramid(D3DXCOLOR(0, 0, 1.0f, 1.0f));
	m_pPyramidRight->SetRotation(90, 0, 0);
	m_pPyramidRight->UpdateWorld();
}


cObject_LocalFrame::~cObject_LocalFrame()
{
}


void cObject_LocalFrame::Setup()
{
}


void cObject_LocalFrame::Update()
{
}


void cObject_LocalFrame::Render()
{
	g_pDevice->SetFVF(Vertex_PN::FVF);
	g_pDevice->SetTexture(0, NULL);

	m_pPyramidLook->Render();
	m_pPyramidUp->Render();
	m_pPyramidRight->Render();
}
