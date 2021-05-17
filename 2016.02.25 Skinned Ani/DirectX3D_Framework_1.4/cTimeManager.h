#pragma once

class cTimeManager
{
	SINGLETONE(cTimeManager);

private:
	// fps 계산용
	float	m_fFPS;
	short	m_nCount;
	DWORD	m_dwElapseTime;

	// 게임 시간
	DWORD	m_dwGameTime;
	DWORD	m_dwCurrentTime;
	DWORD	m_dwBeforeTime;
	DWORD	m_dwDeltaTime;

public:
	void Update();
	DWORD GetGameTime()			{ return m_dwGameTime; }
	DWORD GetTickCurrentTime()	{ return m_dwCurrentTime; }
	DWORD GetDeltaTime()		{ return m_dwDeltaTime; }
};

extern cTimeManager* g_pTimeManger;
