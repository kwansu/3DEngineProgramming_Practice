#pragma once
#include "cObj_Box.h"

class cObj_Wall :
	public cObj_Box
{
public:
	cObj_Wall();
	~cObj_Wall();

	void Setup();

private:
	// ���� ���� �� �𼭸��� ��ã���带 �߰��Ѵ�
	// ���� ��ġ�� ���ϸ� ���� ���ϹǷ�, ��ġ �Ϸ��� �ѹ��� ȣ��
	void AddPathNode();
};

