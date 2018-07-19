#include "stdafx.h"
#include "BitmapObj.h"

void Bitmap::Init(HWND hWnd, int x, int y, int w, int h, LPCWSTR szFileName, COLORREF sprite)
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

	SpriteColor = sprite;
}

void Bitmap::Draw(HDC hMemDC)
{
	SelectObject(hdcImg, hBitmap);	//미리 만들어둔 DC에 불러온 비트맵을 설정
	TransparentBlt(hMemDC, pos.x, pos.y, w, h, hdcImg, 0, 0, w, h, SpriteColor);	//받아온 후면DC에 비트맵을 불러온 DC를 복사
}

void Bitmap::Ternimate()
{
	if (hBitmap != nullptr)
		DeleteObject(hBitmap);

	DeleteDC(hdcImg);
}

void Bitmap::SetPosition(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

void Bitmap::SetSpriteColor(COLORREF color)
{
	SpriteColor = color;
}