#include "stdafx.h"
#include "cGameObject.h"


cGameObject::cGameObject()
	: m_isActive(true)
{
}


cGameObject::~cGameObject()
{
}

bool cGameObject::IsActived()
{
	return m_isActive;
}
