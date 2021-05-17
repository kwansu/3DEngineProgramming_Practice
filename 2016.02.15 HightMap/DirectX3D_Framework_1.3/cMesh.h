#pragma once
#include "cMeshGroup.h"

// ���ؽ�->������->��Ʈ(�׷�)->�Ž�(��ü�� ���)
// ������ ���� ���ؽ��� ����ü, ��ü�� ȭ�鿡 �׷��������ؼ���
// �ϳ��̻��� �Ž��� �����ͷ� ������ �ڽ��� ��ġ(���� ��Ʈ����)��
// �����Լ��� ȣ���ϸ� �ȴ�.

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

