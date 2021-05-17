#include "stdafx.h"
#include "cObjFileLoader.h"
//
//
//cObjFileLoader::cObjFileLoader()
//{
//}
//
//
//cObjFileLoader::~cObjFileLoader()
//{
//}
//
//cMeshData* cObjFileLoader::LoadObj(char * szFileName)
//{
//	m_ifObj.open(szFileName, ios::in);
//
//	if (!m_ifObj.is_open())
//		assert(false, "cObjLoader->LoadObj : file open failed");
//
//	while (!m_ifObj.eof())
//	{
//		MYFILELOAD::GetToken(m_ifObj, m_sToken);
//
//		if (!strcmp(m_sToken, "mtllib"))
//		{
//			ProcessMTLLIB();
//		}
//		else if (!strcmp(m_sToken, "v"))
//		{
//			ProcessV();
//		}
//		else if (!strcmp(m_sToken, "vt"))
//		{
//			ProcessVT();
//		}
//		else if (!strcmp(m_sToken, "vn"))
//		{
//			ProcessVN();
//		}
//		else if (!strcmp(m_sToken, "usemtl"))
//		{
//			ProcessUSEMTL();
//		}
//	}
//
//	m_ifObj.close();
//
//	return m_pMeshData;
//}
//
//void cObjFileLoader::ProcessMTLLIB()
//{
//	MYFILELOAD::GetToken(m_ifObj, m_sToken);
//
//	LoadMtl(m_sToken);
//}
//
//void cObjFileLoader::ProcessV()
//{
//
//}
//
//void cObjFileLoader::ProcessVT()
//{
//}
//
//void cObjFileLoader::ProcessVN()
//{
//}
//
//void cObjFileLoader::ProcessUSEMTL()
//{
//}
//
//void cObjFileLoader::ProcessS()
//{
//}
//
//void cObjFileLoader::ProcessF()
//{
//}
//
//void cObjFileLoader::LoadMtl(char * szFileName)
//{
//	m_ifMtl.open(szFileName, ios::in);
//
//	if (!m_ifMtl.is_open())
//		assert(false, "cObjLoader->LoadMtl : file load failed");
//
//	while (!m_ifMtl.eof())
//	{
//		MYFILELOAD::GetToken(m_ifMtl, m_sToken);
//
//		if (!strcmp(m_sToken, "newmtl"))
//		{
//			ProcessNEWMTL();
//		}
//		else if (!strcmp(m_sToken, "Ka"))
//		{
//			ProcessKA();
//		}
//		else if (!strcmp(m_sToken, "Kd"))
//		{
//			ProcessKD();
//		}
//		else if (!strcmp(m_sToken, "Ks"))
//		{
//			ProcessKS();
//		}
//		else if (!strcmp(m_sToken, "map_Kd"))
//		{
//			ProcessMAP_KD();
//		}
//	}
//
//	m_ifMtl.close();
//}
//
//void cObjFileLoader::ProcessNEWMTL()
//{
//	MYFILELOAD::GetToken(m_ifMtl, m_sToken);
//
//	m_pAttribute = &m_mapAttribute[m_sToken];
//}
//
//void cObjFileLoader::ProcessKA()
//{
//	D3DXCOLOR color;
//
//	MYFILELOAD::GetFloat(m_ifMtl, &color.r);
//	MYFILELOAD::GetFloat(m_ifMtl, &color.g);
//	MYFILELOAD::GetFloat(m_ifMtl, &color.b);
//	color.a = 1.0f;
//
//	m_pAttribute->mtl.Ambient = color;
//}
//
//void cObjFileLoader::ProcessKD()
//{
//	D3DXCOLOR color;
//
//	MYFILELOAD::GetFloat(m_ifMtl, &color.r);
//	MYFILELOAD::GetFloat(m_ifMtl, &color.g);
//	MYFILELOAD::GetFloat(m_ifMtl, &color.b);
//	color.a = 1.0f;
//
//	m_pAttribute->mtl.Diffuse = color;
//}
//
//void cObjFileLoader::ProcessKS()
//{
//	D3DXCOLOR color;
//
//	MYFILELOAD::GetFloat(m_ifMtl, &color.r);
//	MYFILELOAD::GetFloat(m_ifMtl, &color.g);
//	MYFILELOAD::GetFloat(m_ifMtl, &color.b);
//	color.a = 1.0f;
//
//	m_pAttribute->mtl.Specular = color;
//}
//
//void cObjFileLoader::ProcessMAP_KD()
//{
//	MYFILELOAD::GetToken(m_ifMtl, m_sToken);
//
//	m_pAttribute->pTexture = (g_pTexture->LoadTextureDate(m_sToken)).pTexture;
//}
