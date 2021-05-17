#include "stdafx.h"
#include "cInputManager.h"

cInputManager* g_pInput = cInputManager::GetInstance();


cInputManager::cInputManager()
{
}


cInputManager::~cInputManager()
{
}


void cInputManager::Update()
{
	if (m_nMouseWheel)
	{
		m_nMouseWheel *= 0.9f;
		if (abs(m_nMouseWheel) < 10)
			m_nMouseWheel = 0;
	}

	m_ptMouseInterval.x = m_ptMouse.x - m_ptMouseBefore.x;
	m_ptMouseInterval.y = m_ptMouse.y - m_ptMouseBefore.y;
	m_ptMouseBefore = m_ptMouse;
}