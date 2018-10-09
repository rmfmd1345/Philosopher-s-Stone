#pragma once

class SpriteHelper
{
private:

	HDC hdcImg;				//미리 그려둘 비트맵의 DC
	HBITMAP hBitmap;		//비트맵
	COLORREF SpriteColor;	//투명화 컬러 (마젠타가 기본)
	POINT pos;				//좌표
	RECT rtImg;				//표시 될 이미지 크기
	int w;					//너비
	int h;					//높이
	int term;				//스프라이트 간격
	int CurrentFrame;		//현재 출력되는 이미지	
	int LastFrame;			//전체 이미지 수	

public:
	void Init(HWND hWnd, int x, int y, int w, int h, int f, LPCWSTR szFileName, COLORREF sprite = RGB(255, 0, 255));
	void Draw(HDC hMemDC);
	void ReverseDraw(HDC hMemDC);
	void Ternimate();

	void SetPosition(int x, int y);
	void SetSpriteColor(COLORREF color);
	void SetCurrentFrame(int f);

	int GetCurrentFrame();
	int GetLastFrame();

	void NextFrameSprite();
	void NextFrameSprite_Trap();
	void SetFrameSprite(int f);
};