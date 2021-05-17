#pragma once
#include "cTransform.h"

class cGameObject	:
	public cTransform, public iCollider, public iObjectMessenger
{
protected:
	bool		m_isActive;

public:
	cGameObject();
	virtual ~cGameObject();

	virtual void Setup()	{}
	virtual void Update()	{}
	virtual void Render()	{}

	bool IsActived();
};

