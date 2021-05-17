#include "stdafx.h"
#include "cCollider.h"


cCollider::cCollider()
{
}


cCollider::~cCollider()
{
}


cColliderGroup* cCollider::PushCollider(string name)
{
	pair<map<string, cColliderGroup>::iterator, bool> result;

	result = m_mapColliderData.insert(pair<string
		, cColliderGroup>(name, cColliderGroup()));

	if (result.second)
		return &result.first->second;

	return NULL;
}
