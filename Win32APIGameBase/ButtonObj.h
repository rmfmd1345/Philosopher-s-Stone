#pragma once

#define OFF		0
#define OVER	1
#define ON		2

class Button	//버튼!
{
public:
	Button() { }
	~Button() { }

private:
	int stateBtn = OFF;

	HDC hdcImg;
	HBITMAP hBitmap;
	HBITMAP hOnBitmap;
	HBITMAP hOverBitmap;
	COLORREF SpriteColor;
	POINT pos;
	int w;
	int h;

public:
	void Init(HWND hWnd, int x, int y, int w, int h, LPCWSTR FileName, LPCWSTR OnFileName, LPCWSTR OverFileName, COLORREF sprite = RGB(255, 0, 255));	//szFileName 는 비트맵 파일의 이름
	void Draw(HDC hMemDC);	//그리기
	void Ternimate();		//종료!

	void SetPosition(int x, int y);
	void SetSpriteColor(COLORREF color);

	POINT GetPosition();

	bool isOver(int x, int y);
	bool isClickDown(int x, int y);
	bool isClickUp(int x, int y);

};