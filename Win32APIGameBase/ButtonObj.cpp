#include "stdafx.h"
#include "ButtonObj.h"

void Button::Init(HWND hWnd, int x, int y, int w, int h, LPCWSTR FileName, LPCWSTR OnFileName, LPCWSTR OverFileName, COLORREF sprite)
{
	hdcImg = CreateCompatibleDC(GetDC(hWnd));	//그릴 DC를 생성

	WCHAR str[128];
	wsprintf(str, FileName);
	hBitmap = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hBitmap == NULL)
	{
		MessageBox(NULL, L"이미지가 없습니다.", L"에러!!!", MB_OK);	//이미지불러오기 실패
		exit(0);
	}

	wsprintf(str, OnFileName);
	hOnBitmap = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hOnBitmap == NULL)
	{
		MessageBox(NULL, L"이미지가 없습니다.", L"에러!!!", MB_OK);	//이미지불러오기 실패
		exit(0);
	}

	wsprintf(str, OverFileName);
	hOverBitmap = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hOverBitmap == NULL)
	{
		MessageBox(NULL, L"이미지가 없습니다.", L"에러!!!", MB_OK);	//이미지불러오기 실패
		exit(0);
	}

	pos.x = x;
	pos.y = y;

	this->w = w;
	this->h = h;

	SpriteColor = sprite;

	stateBtn = OFF;
}

void Button::Draw(HDC hMemDC)
{
	if (stateBtn == OFF)
		SelectObject(hdcImg, hBitmap);
	else if (stateBtn == OVER)
		SelectObject(hdcImg, hOverBitmap);
	else if (stateBtn == ON)
		SelectObject(hdcImg, hOnBitmap);

	TransparentBlt(hMemDC, pos.x, pos.y, w, h, hdcImg, 0, 0, w, h, SpriteColor);
}

bool Button::isOver(int x, int y)	//마우스오버 체크
{
	if ((pos.x <= x) && (x <= pos.x + w) && (pos.y <= y) && (y <= pos.y + h))
	{
		if (stateBtn != ON) stateBtn = OVER;
		return true;
	}
	stateBtn = OFF;
	return false;
}

bool Button::isClickDown(int x, int y)
{
	if (this->isOver(x, y))
	{
		stateBtn = ON;
		return true;
	}
	stateBtn = OFF;
	return false;
}

bool Button::isClickUp(int x, int y)
{
	stateBtn = OFF;
	if (this->isOver(x, y))
	{
		return true;
	}
	return false;
}

void Button::Ternimate()
{
	if (hBitmap != nullptr)
		DeleteObject(hBitmap);
	if (hOnBitmap != nullptr)
		DeleteObject(hOnBitmap);
	if (hOverBitmap != nullptr)
		DeleteObject(hOverBitmap);

	DeleteDC(hdcImg);
}

void Button::SetPosition(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

void Button::SetSpriteColor(COLORREF color)
{
	SpriteColor = color;
}

POINT Button::GetPosition()
{
	return pos;
}