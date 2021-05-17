#pragma once

class cObjFileLoader
{
private:
	ifstream						m_ifObj;
	ifstream						m_ifMtl;
	char							m_sToken[1024];

	cMeshData						m_meshData;
	map<string, stMeshAttribute>	m_mapAttribute;

public:
	cObjFileLoader();
	~cObjFileLoader();

	cMeshData LoadObj(char* szFileName);

private:
	void ProcessMTLLIB();
	void ProcessV();
	void ProcessVT();
	void ProcessVN();
	void ProcessUSEMTL();
	void ProcessS();
	void ProcessF();

	// mtl Load
	void LoadMtl(char* szFileName);
};

