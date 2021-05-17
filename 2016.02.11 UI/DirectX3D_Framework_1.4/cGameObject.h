#pragma once
#include "cTransform.h"

class cGameObject	:
	public cTransform
{
public:
	cGameObject();
	~cGameObject();

	virtual void Setup()	{}
	virtual void Update()	{}
	virtual void Render()	{}
};

