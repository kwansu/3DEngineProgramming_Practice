#include "stdafx.h"
#include "cGeometry.h"


DWORD cGeometry::s_dwTick = 0;

cGeometry::cGeometry()
	: m_pParent(NULL)
	, m_pTexture(NULL)
	, m_pVertexBuffer(NULL)
{
	ZeroMemory(&m_mtl, sizeof(D3DMATERIAL9));
	D3DXMatrixIdentity(&m_matLocal);
	D3DXMatrixIdentity(&m_matWorld);
}


cGeometry::~cGeometry()
{
	SafeRelease(m_pVertexBuffer);
}

void cGeometry::Update()
{
}


void cGeometry::Render(D3DXMATRIXA16* pmatParent, bool bTex)
{
	UpdateLocal();

	m_matWorld = m_matLocal * *pmatParent;

	if (m_pTexture)
	{
		if (bTex)
			g_pDevice->SetTexture(0, m_pTexture);

		g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		g_pDevice->SetMaterial(&m_mtl);
		g_pDevice->SetFVF(Vertex_PNT::FVF);

		g_pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(Vertex_PNT));

		g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_nVertexSize / 3);
	}

	for (int i = 0; i < m_apChild.size(); ++i)
		m_apChild[i]->Render(&m_matWorld, bTex);
}


void cGeometry::UpdateLocal(DWORD dwTick)
{
	D3DXVECTOR3 vPos;
	D3DXQUATERNION vQua;

	int size = m_aAniPos.size();
	for (int i = 0; i < size; ++i)
	{
		if (m_aAniPos[i].fKeyTime > dwTick || i + 1 >= size)
		{
			if (i == 0)
			{
				vPos = m_aAniPos[0].vPos;
				D3DXMatrixTranslation(&m_matT, vPos.x, vPos.y, vPos.z);
			}
			else
			{
				float t = m_aAniPos[i].fKeyTime - m_aAniPos[i - 1].fKeyTime;
				t = (dwTick - m_aAniPos[i - 1].fKeyTime) / t;

				if (m_aAniPos[i].fKeyTime < dwTick)
					t = 1;

				D3DXVec3Lerp(&vPos, &m_aAniPos[i - 1].vPos, &m_aAniPos[i].vPos, t);
				D3DXMatrixTranslation(&m_matT, vPos.x, vPos.y, vPos.z);
			}

			break;
		}
	}

	size = m_aAniRot.size();
	for (int i = 0; i < size; ++i)
	{
		if (m_aAniRot[i].fKeyTime > dwTick || i + 1 >= size)
		{
			if (i == 0)
			{
				vQua = m_aAniRot[i].vQuaternion;
				D3DXMatrixRotationQuaternion(&m_matR, &vQua);
			}
			else
			{
				
				float t = m_aAniRot[i].fKeyTime - m_aAniRot[i - 1].fKeyTime;
				t = (dwTick - m_aAniRot[i - 1].fKeyTime) / t;

				if (m_aAniRot[i].fKeyTime < dwTick)
					t = 1;

				D3DXQuaternionSlerp(&vQua, &m_aAniRot[i - 1].vQuaternion, &m_aAniRot[i].vQuaternion, t);
				D3DXMatrixRotationQuaternion(&m_matR, &vQua);
			}

			break;
		}
	}

	m_matLocal = m_matR * m_matT;
}
