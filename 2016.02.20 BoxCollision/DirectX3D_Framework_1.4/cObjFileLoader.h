//#pragma once
//
//struct stGroup
//{
//	vector<stVertex_PNT>	vertexPNT;
//	int						nAttriNum;
//};
//
//class cObjFileLoader
//{
//private:
//	ifstream						m_ifObj;
//	ifstream						m_ifMtl;
//	char							m_sToken[1024];
//	int								m_nVertexSize;
//	cMeshData*						m_pMeshData;
//	stMeshAttribute*				m_pAttribute;
//	map<string, stMeshAttribute>	m_mapAttribute;
//
//public:
//	cObjFileLoader();
//	~cObjFileLoader();
//
//	cMeshData* LoadObj(char* szFileName);
//
//private:
//	void ProcessMTLLIB();
//	void ProcessV();
//	void ProcessVT();
//	void ProcessVN();
//	void ProcessUSEMTL();
//	void ProcessS();
//	void ProcessF();
//
//	// mtl Load
//	void LoadMtl(char* szFileName);
//	void ProcessNEWMTL();
//	void ProcessKA();
//	void ProcessKD();
//	void ProcessKS();
//	void ProcessMAP_KD();
//};

