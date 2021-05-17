#include "stdafx.h"
#include "cObjFileLoader.h"


cObjFileLoader::cObjFileLoader()
{
}


cObjFileLoader::~cObjFileLoader()
{
}

cMeshData cObjFileLoader::LoadObj(char * szFileName)
{
	m_ifObj.open(szFileName, ios::in);

	if (m_ifObj.is_open())
		assert("cObjLoader->LoadObj : file open failed");

	while (!m_ifObj.eof())
	{
		MYFILELOAD::GetToken(m_ifObj, m_sToken);

		if (m_sToken == "#")
		{
			m_ifObj.getline(NULL, 1024);
			continue;
		}
		else if (m_sToken == "mtllib")
		{
			ProcessMTLLIB();
		}
		else if (m_sToken == "v")
		{
			ProcessV();
		}
		else if (m_sToken == "vt")
		{
			ProcessVT();
		}
		else if (m_sToken == "vn")
		{
			ProcessVN();
		}
		else if (m_sToken == "usemtl")
		{
			ProcessUSEMTL();
		}
	}

	m_ifObj.close();

	return m_meshData;
}

void cObjFileLoader::ProcessMTLLIB()
{
	MYFILELOAD::GetToken(m_ifObj, m_sToken);

	LoadMtl(m_sToken);
}

void cObjFileLoader::ProcessV()
{
}

void cObjFileLoader::ProcessVT()
{
}

void cObjFileLoader::ProcessVN()
{
}

void cObjFileLoader::ProcessUSEMTL()
{
}

void cObjFileLoader::ProcessS()
{
}

void cObjFileLoader::ProcessF()
{
}

void cObjFileLoader::LoadMtl(char * szFileName)
{
	m_ifMtl.open(szFileName, ios::in);

	if (m_ifMtl.is_open())
		assert("cObjLoader->LoadMtl : file load failed;");



	m_ifMtl.close();
}
