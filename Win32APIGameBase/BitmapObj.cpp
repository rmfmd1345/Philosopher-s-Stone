#include "stdafx.h"
#include "BitmapObj.h"

void Bitmap::Init(HWND hWnd, int x, int y, int w, int h, LPCWSTR szFileName, COLORREF sprite)
{
	hdcImg = CreateCompatibleDC(GetDC(hWnd));	//�׸� DC�� ����

	WCHAR str[128];
	wsprintf(str, szFileName);
	hBitmap = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hBitmap == NULL)
	{
		MessageBox(NULL, L"�̹����� �����ϴ�.", L"����!!!", MB_OK);	//�̹����ҷ����� ����
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
	SelectObject(hdcImg, hBitmap);	//�̸� ������ DC�� �ҷ��� ��Ʈ���� ����
	TransparentBlt(hMemDC, pos.x, pos.y, w, h, hdcImg, 0, 0, w, h, SpriteColor);	//�޾ƿ� �ĸ�DC�� ��Ʈ���� �ҷ��� DC�� ����
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