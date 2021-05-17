#include "stdafx.h"
#include "cResourceManager.h"


cResourceManager::cResourceManager()
{
}


cResourceManager::~cResourceManager()
{
}


bool cResourceManager::LoadObjFile(char* sFileName, bool isMesh)
{
	pair<map<string, cMesh>::iterator, bool> result;
	result = m_mapMeshData.insert(
		pair< string, cMesh >(sFileName, cMesh()));

	if (!result.second)
		return false;
	
	cMesh* pMesh = &result.first->second;

	pair<map<string, cCollider>::iterator, bool> resultC;
	resultC = m_mapColliderData.insert(
		pair< string, cCollider >(sFileName, cCollider()));

	if (!resultC.second)
		return false;

	cCollider* pColl = &resultC.first->second;

	vector<D3DXVECTOR3>		aPosition;
	vector<D3DXVECTOR3>		aNormal;
	vector<D3DXVECTOR2>		aTexturePos;

	cMeshGroup*				pMeshGroup;
	cColliderGroup*			pCollGroup;

	ifstream ifObj(sFileName);

	if (!ifObj.is_open())
		assert("Obj file Open fialed.");

	char sLine[1024];
	char *token, *context;

	while (!ifObj.eof())
	{
		ifObj.getline(sLine, 1024);
		token = strtok_s(sLine, " ", &context);

		if (!token)
			continue;

		if (!strcmp(token, "#"))
			continue;

		if (!strcmp(token, "g"))
		{
			token = strtok_s(NULL, " ", &context);

			if (token)
			{
				if (isMesh)
				{
					pMeshGroup = pMesh->PushMesh(token);
				}
				else
				{
					pCollGroup = pColl->PushCollider(token);
				}
			}
			continue;
		}

		if (!strcmp(token, "v"))
		{
			D3DXVECTOR3 vec;
			token = strtok_s(NULL, " ", &context);
			assert(token && "v");
			vec.x = atof(token);

			token = strtok_s(NULL, " ", &context);
			assert(token && "v");
			vec.y = atof(token);

			token = strtok_s(NULL, " ", &context);
			assert(token && "v");
			vec.z = atof(token);

			aPosition.push_back(vec);
			continue;
		}

		if (!strcmp(token, "f"))
		{
			int aPNT[3];

			for (int i = 0; i < 3; ++i)
			{
				token = strtok_s(NULL, "/", &context);
				assert(token && "f");
				aPNT[0] = atoi(token) -1;

				token = strtok_s(NULL, "/", &context);
				assert(token && "f");
				aPNT[2] = atoi(token) -1;

				token = strtok_s(NULL, " ", &context);
				assert(token && "f");
				aPNT[1] = atoi(token) -1;

				if (isMesh)
				{
					pMeshGroup->PushVertexPNT(
						&Vertex_PNT(aPosition[aPNT[0]]
						, aNormal[aPNT[1]]
						, aTexturePos[aPNT[2]]));
				}
				else
				{
					pCollGroup->PushVertex(&aPosition[aPNT[0]]);
				}
			}
			continue;
		}

		if (isMesh)
		{
			if (!strcmp(token, "vn"))
			{
				D3DXVECTOR3 vec;
				token = strtok_s(NULL, " ", &context);
				assert(token && "vn");
				vec.x = atof(token);

				token = strtok_s(NULL, " ", &context);
				assert(token && "vn");
				vec.y = atof(token);

				token = strtok_s(NULL, " ", &context);
				assert(token && "vn");
				vec.z = atof(token);

				aNormal.push_back(vec);
				continue;
			}
			if (!strcmp(token, "vt"))
			{
				D3DXVECTOR2 vec;
				token = strtok_s(NULL, " ", &context);
				assert(token && "vt");
				vec.x = atof(token);

				token = strtok_s(NULL, " ", &context);
				assert(token && "vt");
				vec.y = atof(token);

				aTexturePos.push_back(vec);
				continue;
			}

			if (!strcmp(token, "mtllib"))
			{
				token = strtok_s(NULL, " ", &context);
				assert(token && "mtllib");

				if (LoadMtlFile(token))
					assert("mtllib");

				continue;
			}

			if (!strcmp(token, "usemtl"))
			{
				token = strtok_s(NULL, " ", &context);
				assert(token && "usemtl");

				pMeshGroup->SetMtlTex(&m_mapMtlTexData[token]);
				continue;
			}
		}
	}

	ifObj.close();

	return true;
}


bool cResourceManager::LoadMtlFile(char* sFileName)
{
	MtlTexture*	pMtlTexEdit;

	ifstream ifObj(sFileName);

	if (!ifObj.is_open())
		assert("Obj file Open fialed.");

	char sLine[1024];
	char *token, *context;

	while (!ifObj.eof())
	{
		ifObj.getline(sLine, 1024);
		token = strtok_s(sLine, " ", &context);

		if (!token)
			continue;

		if (!strcmp(token, "#"))
			continue;

		if (!strcmp(token, "newmtl"))
		{
			token = strtok_s(NULL, " ", &context);
			assert(token && "newmtl");

			pair<map<string, MtlTexture>::iterator, bool> result;
			result = m_mapMtlTexData.insert(
				pair< string, MtlTexture >(token, MtlTexture()));

			pMtlTexEdit = &result.first->second;
			ZeroMemory(&pMtlTexEdit->mtl, sizeof(D3DMATERIAL9));
			continue;
		}

		if (token[0] == 'K')
		{
			char c = token[1];
			D3DXCOLOR color;
			color.a = 0;

			token = strtok_s(NULL, " ", &context);
			assert(token && "k");
			color.r = atof(token);

			token = strtok_s(NULL, " ", &context);
			assert(token && "k");
			color.g = atof(token);

			token = strtok_s(NULL, " ", &context);
			assert(token && "k");
			color.b = atof(token);

			switch (c)
			{
			case 'a':
				pMtlTexEdit->mtl.Ambient = color;
			case 'd':
				pMtlTexEdit->mtl.Diffuse = color;
			case 's':
				pMtlTexEdit->mtl.Specular = color;
			}
			continue;
		}

		if (!strcmp(token, "map_Kd"))
		{
			token = strtok_s(NULL, " ", &context);
			assert(token && "map_Kd");

			pair<map<string, LPDIRECT3DTEXTURE9>::iterator, bool> result;
			result = m_mapTexture.insert(
				pair< string, LPDIRECT3DTEXTURE9 >(token, NULL));

			if (result.second)
			{
				D3DXCreateTextureFromFile(g_pDevice, token
					, &result.first->second);
			}

			pMtlTexEdit->pTex = result.first->second;
			continue;
		}
	}

	ifObj.close();

	return true;
}


bool cResourceManager::GetMesh(OUT cMesh* &pMesh, string name)
{
	map<string, cMesh>::iterator iterMesh;

	for (iterMesh = m_mapMeshData.begin();
		iterMesh != m_mapMeshData.end(); ++iterMesh)
	{
		map<string, cMesh>::iterator findIter;
		findIter = m_mapMeshData.find(name);

		if (findIter != m_mapMeshData.end())
		{
			pMesh = &(findIter->second);
			return true;
		}
	}

	return false;
}


bool cResourceManager::GetCollider(OUT cCollider* pColl, string name)
{
	map<string, cCollider>::iterator iterColl;

	for (iterColl = m_mapColliderData.begin();
		iterColl != m_mapColliderData.end(); ++iterColl)
	{
		map<string, cCollider>::iterator iterColl;
		iterColl = m_mapColliderData.find(name);

		if (iterColl != m_mapColliderData.end())
		{
			pColl = &iterColl->second;
			return true;
		}
	}

	return false;
}


void cResourceManager::Destroy()
{
	map<string, LPDIRECT3DTEXTURE9>::iterator iterTex;
	for (iterTex = m_mapTexture.begin();
		iterTex != m_mapTexture.end(); ++iterTex)
	{
		SafeRelease(iterTex->second);
	}
}
