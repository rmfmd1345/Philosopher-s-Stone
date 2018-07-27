#include "stdafx.h"
#include "Sprite.h"

void SpriteHelper::Init(HWND hWnd, int x, int y, int w, int h, int f, LPCWSTR szFileName, COLORREF sprite)
{
	hdcImg = CreateCompatibleDC(GetDC(hWnd));	//그릴 DC를 생성

	WCHAR str[128];
	wsprintf(str, szFileName);
	hBitmap = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hBitmap == NULL)
	{
		MessageBox(NULL, L"이미지가 없습니다.", L"에러!!!", MB_OK);	//이미지불러오기 실패
		exit(0);
	}

	pos.x = x;
	pos.y = y;

	this->w = w;
	this->h = h;

	CurrentFrame = 1;
	LastFrame = f;

	rtImg = { 0, 0, (w / f), h};

	SpriteColor = sprite;
}

void SpriteHelper::Draw(HDC hMemDC)
{
	SelectObject(hdcImg, hBitmap);	//미리 만들어둔 DC에 불러온 비트맵을 설정
	TransparentBlt(hMemDC, pos.x, pos.y, rtImg.right, h, hdcImg, rtImg.left, rtImg.top, rtImg.right, rtImg.bottom, SpriteColor);	//받아온 후면DC에 비트맵을 불러온 DC를 복사
}

void SpriteHelper::ReverseDraw(HDC hMemDC)
{
	SelectObject(hdcImg, hBitmap);
	StretchBlt(hdcImg, 0, 0, rtImg.right, h, hdcImg, rtImg.left, rtImg.top, rtImg.right, rtImg.bottom, SRCCOPY);
	StretchBlt(hdcImg, 0 + rtImg.right - 1, 0, -rtImg.right, h, hdcImg, 0, 0, rtImg.right, rtImg.bottom, SRCCOPY);
	TransparentBlt(hMemDC, pos.x, pos.y, rtImg.right, h, hdcImg, 0, 0, rtImg.right, rtImg.bottom, SpriteColor);
}

void SpriteHelper::Ternimate()
{
	if (hBitmap != nullptr)
		DeleteObject(hBitmap);

	DeleteDC(hdcImg);
}

void SpriteHelper::SetPosition(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

void SpriteHelper::SetSpriteColor(COLORREF color)
{
	SpriteColor = color;
}

void SpriteHelper::NextFrameSprite()
{
	rtImg = { (w / LastFrame) * CurrentFrame, 0, (w / LastFrame), h };
	CurrentFrame++;
	if (CurrentFrame >= LastFrame)
		CurrentFrame = 1;
}