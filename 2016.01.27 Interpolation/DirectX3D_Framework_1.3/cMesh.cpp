#include "stdafx.h"
#include "cMesh.h"


cMesh::cMesh()
{
}


cMesh::~cMesh()
{
}


cMeshGroup* cMesh::PushMesh(string name)
{
	pair<map<string, cMeshGroup>::iterator, bool> result;

	result = m_mapMeshData.insert(pair<string, cMeshGroup>
		(name, cMeshGroup()));

	if (result.second)
		return &result.first->second;

	return NULL;
}

void cMesh::Render()
{
	map<string, cMeshGroup>::iterator iterMesh;

	for (iterMesh = m_mapMeshData.begin();
		iterMesh != m_mapMeshData.end(); ++iterMesh)
	{
		iterMesh->second.Render();
	}
}
