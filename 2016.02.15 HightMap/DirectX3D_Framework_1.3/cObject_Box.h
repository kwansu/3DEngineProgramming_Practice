#pragma once
#include "cObject.h"
class cObject_Box :
	public cObject
{
private:
	ID3DXMesh* mesh;

public:
	cObject_Box();
	virtual ~cObject_Box();

	void Setup() override;
	void Update() override;
	void Render() override;
};

