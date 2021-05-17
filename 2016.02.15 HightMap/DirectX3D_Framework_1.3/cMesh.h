#pragma once
#include "cMeshGroup.h"

// 버텍스->폴리곤->파트(그룹)->매쉬(객체의 모습)
// 랜더를 위한 버텍스의 집합체, 객체가 화면에 그려지기위해서는
// 하나이상의 매쉬를 포인터로 가져서 자신의 위치(월드 매트릭스)로
// 랜더함수를 호출하면 된다.

class cMesh
{
private:
	ID3DXMesh*					m_pMesh;
	map<string, cMeshGroup>		m_mapMeshData;
	int							m_p;
	
public:
	cMesh();
	~cMesh();
	cMeshGroup* PushMesh(string name);
	void Render();
	void Setup();
	void MeshProcess();
};

