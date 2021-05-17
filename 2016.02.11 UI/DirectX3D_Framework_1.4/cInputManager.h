#pragma once

class cInputManager
{
	SINGLETONE(cInputManager);

private:
	bool	m_abInputKey[256];
	bool	m_abInputKeyBefore[256];

	POINT	m_ptMousePos;
	POINT	m_ptMousePosBefore;
	POINT	m_ptMousePosInterval;
	int		m_nMouseWheel;

public:
	void Update();
	void KeyDown(char VK)		{ m_abInputKey[VK] = true; }
	void KeyUp(char VK)			{ m_abInputKey[VK] = false; }
	bool IsKeyPress(char VK)	{ return m_abInputKey[VK]; }
	void SetMouse(int x, int y) { m_ptMousePos = { x, y }; }
	POINT GetMousePos()			{ return m_ptMousePos; }
	POINT GetMouseInterval()	{ return m_ptMousePosInterval; }
	void AddWheel(short val)	{ m_nMouseWheel += val; }
	int GetMouseWheel()			{ return m_nMouseWheel; }
};

extern cInputManager* g_pInput;
