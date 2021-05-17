#pragma once
#include "cTransform.h"

class cGameObject	:
	public cTransform
{
public:
	cGameObject();
	virtual ~cGameObject();

	virtual void Setup()	{}
	virtual void Update()	{}
	virtual void Render()	{}
};

