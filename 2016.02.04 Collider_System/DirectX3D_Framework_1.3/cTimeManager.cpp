#include "stdafx.h"
#include "cTimeManager.h"


cTimeManager* g_pTimeManager = cTimeManager::GetInstance();

cTimeManager::cTimeManager()
	: m_fAverageFPS(0)
	, m_fFPS(60)
	, m_dwFrameCount(1000 / 60.f)
	, m_dwTickEndTime(0)
	, m_dwElapseTime(0)
{
	m_dwTickCurrentTime = GetTickCount();
	m_dwGameTime = m_dwTickCurrentTime;
}


cTimeManager::~cTimeManager()
{
}


void cTimeManager::WaitFrameTime()
{
	m_dwTickEndTime = m_dwTickCurrentTime;
	m_dwTickCurrentTime = GetTickCount();
	m_dwTickDeltaTime = m_dwTickCurrentTime - m_dwTickEndTime;
	m_dwGameTime += m_dwTickDeltaTime;

	m_dwElapseTime += m_dwTickDeltaTime;
	++m_dwFrameCount;

	if (m_dwElapseTime > 1000)
	{
		m_fAverageFPS = (float)m_dwFrameCount * 1000 / m_dwElapseTime;
		cout << m_fAverageFPS << endl;
		m_dwElapseTime = 0;
		m_dwFrameCount = 0;
	}
	//if (m_dwElapseTime < m_dwFrameTime)
	//Sleep(m_dwFrameTime - m_dwElapseTime);
}
