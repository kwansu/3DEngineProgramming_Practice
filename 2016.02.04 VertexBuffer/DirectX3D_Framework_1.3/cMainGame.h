#pragma once


class cMainGame
{
private:


public:
	cMainGame();
	~cMainGame();

	void Initialize();
	void Release();
	void Run();
	void Update();
	void Render();
	void MessageHandler(HWND hWnd, UINT iMsg, WPARAM wp, LPARAM lp);
};

