#pragma once

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

	void Release();
	void Initialize();

	void Run();
	void Update();
	void Render();
	void MessageHandler(HWND hWnd, UINT iMsg, WPARAM wp, LPARAM lp);
};

