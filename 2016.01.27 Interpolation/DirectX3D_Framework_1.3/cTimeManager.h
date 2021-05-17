#pragma once

class cTimeManager
{
	SINGLETONE(cTimeManager);

private:
	float	m_fAverageFPS;			//10프레임의 평균 FPS
	float	m_fFPS;					//설정해주는 FPS
	DWORD	m_dwFrameTime;			//한 프레임 간격

	DWORD	m_dwTickCurrentTime;	//현재 컴퓨터 틱카운터
	DWORD	m_dwTickEndTime;		//프레임 끝날때의 시간
	DWORD	m_dwElapseTime;			//프레임 시작후 경과시간
	DWORD	m_dwGameTime;			//게임의 경과시간

public:
	void SetFPS(float fFPS)		{ m_fFPS = fFPS; }
	void SetEndTime()			{ m_dwTickEndTime = GetTickCount(); }
	float GetFPS()	const		{ return m_fFPS; }
	DWORD GetElapesTime() const	{ return m_dwElapseTime; }
	void WaitFrameTime();
};


extern cTimeManager* g_pTimeManager;