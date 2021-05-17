#include "stdafx.h"
#include "cLight.h"


cLight::cLight()
{
	ZeroMemory(&m_stLight, sizeof(D3DLIGHT9));
}


cLight::~cLight()
{
}
