#pragma once

class Bitmap	//비트맵 객체 예제
{
public:
	Bitmap() { }
	~Bitmap() { }

private:
	HDC hdcImg;				//미리 그려둘 비트맵의 DC
	HBITMAP hBitmap;		//비트맵
	COLORREF SpriteColor;	//투명화 컬러 (마젠타가 기본)
	POINT pos;				//좌표

public:
	int w;					//너비
	int h;					//높이

public:
	void Init(HWND hWnd, int x, int y, int w, int h, LPCWSTR szFileName, COLORREF sprite = RGB(255, 0, 255));	//szFileName 는 비트맵 파일의 이름
	void Draw(HDC hMemDC);	//그리기
	void Ternimate();		//종료!

	void SetPosition(int x, int y);
	void SetSpriteColor(COLORREF color);
};