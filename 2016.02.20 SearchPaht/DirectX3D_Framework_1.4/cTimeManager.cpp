#include "stdafx.h"
#include "cTimeManager.h"


cTimeManager* g_pTimeManger = cTimeManager::GetInstance();

cTimeManager::cTimeManager()
	: m_nCount(0)
	, m_dwElapseTime(0)
{
	m_dwCurrentTime = GetTickCount();
	m_dwBeforeTime = m_dwCurrentTime;
}


cTimeManager::~cTimeManager()
{
}

void cTimeManager::Update()
{
	m_dwCurrentTime = GetTickCount();
	m_dwDeltaTime = m_dwCurrentTime - m_dwBeforeTime;
	m_dwBeforeTime = m_dwCurrentTime;
	m_dwGameTime += m_dwDeltaTime;

	m_dwElapseTime += m_dwDeltaTime;
	++m_nCount;

	if (m_dwElapseTime >= 1000)
	{
		m_fFPS = m_nCount * 1000 / (float)m_dwElapseTime;
		m_dwElapseTime = 0;
		m_nCount = 0;

		cout << "FPS : " << m_fFPS << endl;
	}
}
