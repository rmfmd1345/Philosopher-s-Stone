#pragma once

class DrawManager
{
public:
	DrawManager() { };
	~DrawManager() { };

private:
	HWND hWnd;

	HDC hdc;
	HDC hMemDC;

	HBITMAP hBit;

	PAINTSTRUCT ps;

protected:
	void Initialize();
	void Drawing(HWND hWnd);
	void Terminate();

};