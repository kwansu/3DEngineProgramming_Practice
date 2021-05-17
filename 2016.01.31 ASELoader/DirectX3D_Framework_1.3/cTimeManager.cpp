#include "stdafx.h"
#include "cTimeManager.h"


cTimeManager* g_pTimeManager = cTimeManager::GetInstance();

cTimeManager::cTimeManager()
: m_fAverageFPS(0)
, m_fFPS(60)
, m_dwFrameTime(1000 / 60.f)
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
	m_dwTickCurrentTime = GetTickCount();
	m_dwElapseTime = m_dwTickCurrentTime - m_dwTickEndTime;
	m_dwGameTime += m_dwElapseTime;

	//if (m_dwElapseTime < m_dwFrameTime)
		//Sleep(m_dwFrameTime - m_dwElapseTime);
}
