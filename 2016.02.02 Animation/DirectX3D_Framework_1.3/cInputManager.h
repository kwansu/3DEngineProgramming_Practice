#pragma once

class cInputManager
{
	SINGLETONE(cInputManager);

private:
	bool	m_aInputKey[256];
	POINT	m_ptMouse;
	POINT	m_ptMouseBefore;
	POINT	m_ptMouseInterval;
	int		m_nMouseWheel;

public:
	void Update();
	void KeyDown(char VK)		{ m_aInputKey[VK] = true; }
	void KeyUp(char VK)			{ m_aInputKey[VK] = false; }
	bool IsKeyPress(char VK)	{ return m_aInputKey[VK]; }
	void SetMouse(int x, int y)	{ m_ptMouse = { x, y }; }
	POINT GetMousePos()			{ return m_ptMouse; }
	POINT GetMouseInterval()	{ return m_ptMouseInterval; }
	void AddWheel(short val)	{ m_nMouseWheel += val; }
	int GetMouseWheel()			{ return m_nMouseWheel; }
};

// 빈번한 호출로 인한 오버헤드를 줄이기위해
// 매크로대신 전역변수로 선언함.
extern cInputManager* g_pInput;
