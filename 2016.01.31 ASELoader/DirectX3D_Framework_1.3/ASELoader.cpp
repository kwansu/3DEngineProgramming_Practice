#include "stdafx.h"
#include "ASELoader.h"


ASELoader::ASELoader()
{
}


ASELoader::~ASELoader()
{
}


void ASELoader::SetMtlTexture(ifstream* pIfASE)
{
	MtlTexture* pMtlTex;

	char sLine[1024];
	char *token = NULL, *context = NULL;

	int nRefCount = 1;

	while (nRefCount)
	{
		pIfASE->getline(sLine, 1024);

		token = strtok_s(sLine, "*", &context);
		if (!token)
			continue;

		if (!strncmp(token, "}", 1))
		{
			--nRefCount;
			continue;
		}

		token = strtok_s(NULL, " ", &context);
		if (!token)
		{
			token = strtok_s(sLine, "}", &context);
			if (token)
				--nRefCount;

			continue;
		}

		if (!strcmp(token, "MATERIAL"))
		{
			token = strtok_s(NULL, " ", &context);
			assert(token && "SetMtlTex->MATERIAL");

			pair<map<string, MtlTexture>::iterator, bool> result;
			result = m_mapMtlTex.insert(pair<string, MtlTexture>
				(token, MtlTexture()));

			pMtlTex = &result.first->second;
			++nRefCount;
			continue;
		}

		if (!strcmp(token, "MATERIAL_AMBIENT"))
		{
			pMtlTex->mtl.Ambient = GetColor(context);
			continue;
		}

		if (!strcmp(token, "MATERIAL_DIFFUSE"))
		{
			pMtlTex->mtl.Diffuse = GetColor(context);
			continue;
		}

		if (!strcmp(token, "MATERIAL_SPECULAR"))
		{
			pMtlTex->mtl.Specular = GetColor(context);
			continue;
		}

		if (!strcmp(token, "MAP_DIFFUSE"))
		{
			++nRefCount;
			continue;
		}

		if (!strcmp(token, "BITMAP"))
		{
			/*token = strtok_s(NULL, "\"", &context);
			assert(token && "SetMtlTex->BITMAP");*/
			char* name = context + 1;
			token = strtok_s(NULL, "\"", &name);
			assert(token && "SetMtlTex->BITMAP");

			pair<map<string, LPDIRECT3DTEXTURE9>::iterator, bool> result;
			result = m_mapTexture.insert(pair<string, LPDIRECT3DTEXTURE9>
				(token, LPDIRECT3DTEXTURE9()));

			if (!result.second)
				assert(false && "SetMtlTex->BITMAP"); // 텍스쳐 중복방지, 중복사용시, 제거하고 새로 만들지않고 리턴.

			D3DXCreateTextureFromFile(g_pDevice, token
				, &result.first->second);

			pMtlTex->pTex = result.first->second;
			continue;
		}
	}
}


void ASELoader::SetGeometry(ifstream* pIfASE)
{
	vector<D3DXVECTOR3> aPos;
	vector<D3DXVECTOR2> aTex;
	cGeometry*	pGeo = NULL;
	bool bRoot = true;

	char sLine[1024];
	char *token = NULL, *context = NULL;

	int nRefCount = 1;

	while (nRefCount)
	{
		pIfASE->getline(sLine, 1024);

		token = strtok_s(sLine, "*", &context);
		if (!token)
			continue;

		if (!strncmp(token, "}", 1))
		{
			--nRefCount;
			continue;
		}

		token = strtok_s(NULL, " ", &context);
		if (!token)
			continue;

		if (!strcmp(token, "NODE_NAME"))
		{
			if (!pGeo)
			{
				char* name = context + 1;
				token = strtok_s(NULL, "\"", &name);
				assert(token && "SetGeometry->NODE_NAME");

				pair<map<string, cGeometry>::iterator, bool> result;
				result = m_mapGeometry.insert(pair<string, cGeometry>
					(token, cGeometry()));

				pGeo = &result.first->second;
			}

			continue;
		}

		if (!strcmp(token, "NODE_PARENT"))
		{
			char* name = context + 1;
			token = strtok_s(NULL, "\"", &name);
			assert(token && "SetGeometry->NODE_NAME");

			bRoot = false;

			map<string, cGeometry>::iterator findParent;
			findParent = m_mapGeometry.find(token);

			pGeo->m_pParent = &findParent->second;
			findParent->second.m_apChild.push_back(pGeo);
			continue;
		}

		if (!strcmp(token, "MESH_VERTEX"))
		{
			D3DXVECTOR3 vec;
			token = strtok_s(NULL, "\t", &context);

			vec.x = atof(strtok_s(NULL, "\t", &context));
			vec.z = atof(strtok_s(NULL, "\t", &context));
			vec.y = atof(strtok_s(NULL, "\t", &context));
			aPos.push_back(vec);
			continue;
		}

		if (!strcmp(token, "MESH_FACENORMAL"))
		{
			token = strtok_s(NULL, "\t", &context);
			assert(token && "SetGeometry->MESH_FACENORMAL");
			int vertexIndex = 3 * atoi(token);
			D3DXVECTOR3 vNor[3];

			for (int i = 0; i < 3; ++i)
			{
				pIfASE->getline(sLine, 1024);

				token = strtok_s(sLine, "MESH_VERTEXNORMAL", &context);
				token = strtok_s(NULL, "\t", &context);
				assert(token && "SetGeometry->MESH_FACENORMAL");

				token = strtok_s(NULL, "\t", &context);
				assert(token && "SetGeometry->MESH_FACENORMAL");
				vNor[i].x = atof(token);

				token = strtok_s(NULL, "\t", &context);
				assert(token && "SetGeometry->MESH_FACENORMAL");
				vNor[i].z = atof(token);

				token = strtok_s(NULL, "\t", &context);
				assert(token && "SetGeometry->MESH_FACENORMAL");
				vNor[i].y = atof(token);
			}

			pGeo->m_aVertex[vertexIndex].n = vNor[0];
			pGeo->m_aVertex[vertexIndex + 1].n = vNor[2];
			pGeo->m_aVertex[vertexIndex + 2].n = vNor[1];
			continue;
		}

		if (!strcmp(token, "MESH_FACE"))
		{
			int nWinding[3];
			token = strtok_s(NULL, "A:", &context);
			token = strtok_s(NULL, "B:", &context);
			token = strtok_s(NULL, " ", &context);
			assert(token && "SetGeometry->MESH_FACE");
			nWinding[0] = atoi(token);

			token = strtok_s(NULL, "C:", &context);
			token = strtok_s(NULL, " ", &context);
			assert(token && "SetGeometry->MESH_FACE");
			nWinding[1] = atoi(token);

			token = strtok_s(NULL, "AB:", &context);
			token = strtok_s(NULL, " ", &context);
			assert(token && "SetGeometry->MESH_FACE");
			nWinding[2] = atoi(token);

			pGeo->m_aVertex.push_back(aPos[nWinding[0]]);
			pGeo->m_aVertex.push_back(aPos[nWinding[2]]);
			pGeo->m_aVertex.push_back(aPos[nWinding[1]]);
			continue;
		}

		if (!strcmp(token, "MESH_TVERT"))
		{
			D3DXVECTOR2 tex;
			token = strtok_s(NULL, "\t", &context);
			token = strtok_s(NULL, "\t", &context);
			assert(token && "SetGeometry->MESH_TVERT");
			tex.x = atof(token);

			token = strtok_s(NULL, "\t", &context);
			assert(token && "SetGeometry->MESH_TVERT");
			tex.y = (1.f - atof(token));

			aTex.push_back(tex);
			continue;
		}

		if (!strcmp(token, "MESH_TFACE"))
		{
			token = strtok_s(NULL, "\t", &context);
			assert(token && "SetGeometry->MESH_TFACE");
			int i = 3 * atoi(token);

			int nTexI[3];
			token = strtok_s(NULL, "\t", &context);
			assert(token && "SetGeometry->MESH_TFACE");
			nTexI[0] = atoi(token);

			token = strtok_s(NULL, "\t", &context);
			assert(token && "SetGeometry->MESH_TFACE");
			nTexI[1] = atoi(token);

			token = strtok_s(NULL, "\t", &context);
			assert(token && "SetGeometry->MESH_TFACE");
			nTexI[2] = atoi(token);

			pGeo->m_aVertex[i].t = aTex[nTexI[0]];
			pGeo->m_aVertex[i + 1].t = aTex[nTexI[2]];
			pGeo->m_aVertex[i + 2].t = aTex[nTexI[1]];
			continue;
		}

		if (!strcmp(token, "WIREFRAME_COLOR"))
		{
			pGeo->m_mtl.Diffuse = GetColor(context);

			if (bRoot)
				m_pRoot = pGeo;

			return;
		}

		if (!strcmp(token, "MATERIAL_REF"))
		{
			token = strtok_s(NULL, " ", &context);
			assert(token && "SetGeometry->MESH_TFACE");

			map<string, MtlTexture>::iterator findMtlTex;
			findMtlTex = m_mapMtlTex.find(token);

			pGeo->m_pTexture = findMtlTex->second.pTex;
			pGeo->m_mtl = findMtlTex->second.mtl;

			if (bRoot)
				m_pRoot = pGeo;

			return;
		}
	}
}


cGeometry* ASELoader::LoadASE(char* sFileName)
{
	ifstream ifASE(sFileName);

	if (!ifASE.is_open())
	{
		assert(false && "ASE file load failed.");
		return NULL;
	}

	char sLine[1024];
	char *token = NULL, *context = NULL;

	while (!ifASE.eof())
	{
		ifASE.getline(sLine, 1024);

		//token = strtok_s(sLine, "*", &context);
		//if (token)
		//	continue;

		token = strtok_s(sLine, " ", &context);
		if (!token)
			continue;
		
		if (!strcmp(token, "*MATERIAL_LIST"))
		{
			ifASE.getline(sLine, 1024);
			SetMtlTexture(&ifASE);
			continue;
		}

		if (!strcmp(token, "*GEOMOBJECT"))
		{
			SetGeometry(&ifASE);
			continue;
		}
	}

	ifASE.close();

	return m_pRoot;
}


D3DXCOLOR ASELoader::GetColor(char* context)
{
	D3DXCOLOR color;
	color.a = 1.0f;

	color.r = atof(strtok_s(NULL, "\t", &context));
	color.g = atof(strtok_s(NULL, "\t", &context));
	color.b = atof(strtok_s(NULL, "\t", &context));

	return color;
}


D3DXVECTOR3 ASELoader::GetVector3(char* context)
{
	D3DXVECTOR3 vec;

	vec.x = atof(strtok_s(NULL, "\t", &context));
	vec.y = atof(strtok_s(NULL, "\t", &context));
	vec.z = atof(strtok_s(NULL, "\t", &context));

	return vec;
}


void ASELoader::Release()
{
	for each(auto pT in m_mapTexture)
		SafeRelease(pT.second);
}
