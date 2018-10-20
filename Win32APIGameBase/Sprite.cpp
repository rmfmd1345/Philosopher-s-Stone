#include "stdafx.h"
#include "Sprite.h"

void SpriteHelper::Init(HWND hWnd, int x, int y, int w, int h, int f, LPCWSTR szFileName, COLORREF sprite)
{
	hdcImg = CreateCompatibleDC(GetDC(hWnd));	//�׸� DC�� ����
	AlphaDC = CreateCompatibleDC(GetDC(hWnd));
	TransparentDC = CreateCompatibleDC(GetDC(hWnd));

	hBitmap = (HBITMAP) CreateCompatibleBitmap(GetDC(hWnd), SCREEN_WIDTH, SCREEN_HEIGHT);
	//h0Bitmap = (HBITMAP) SelectObject(hdcImg, hBitmap);

	//hBitmap2 = (HBITMAP)CreateCompatibleBitmap(GetDC(hWnd), SCREEN_WIDTH, SCREEN_HEIGHT);
	//h0Bitmap2 = (HBITMAP)SelectObject(AlphaDC, hBitmap2);

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

	CurrentFrame = 1;
	LastFrame = f;

	rtImg = { 0, 0, (w / f), h};

	SpriteColor = sprite;
}

void SpriteHelper::Draw(HDC hMemDC)
{
	SelectObject(hdcImg, hBitmap);	//�̸� ������ DC�� �ҷ��� ��Ʈ���� ����
	TransparentBlt(hMemDC, pos.x, pos.y, rtImg.right, h, hdcImg, rtImg.left, rtImg.top, rtImg.right, rtImg.bottom, SpriteColor);	//�޾ƿ� �ĸ�DC�� ��Ʈ���� �ҷ��� DC�� ����
}

void SpriteHelper::AlphaDraw(HDC hMemDC) //����ȭ ó�� �õ���
{
	//BitBlt(AlphaDC, 0, 0, rtImg.right, h, hMemDC, 0, 0, SRCCOPY);

	SelectObject(hdcImg, hBitmap);
	TransparentBlt(AlphaDC, 0, 0, rtImg.right, h, hdcImg, rtImg.left, rtImg.top, rtImg.right, rtImg.bottom, SpriteColor);
	BitBlt(hMemDC, pos.x, pos.y, rtImg.right, h, AlphaDC, rtImg.left, rtImg.top, SRCCOPY);
	
	//bf.BlendOp = AC_SRC_OVER;
	//bf.BlendFlags = 0; //�� ���� �׻� 0�̿��� ��
	//bf.AlphaFormat = 0;
	//bf.SourceConstantAlpha = 100; //���� ��
	//
	//
	//AlphaBlend(hMemDC, pos.x, pos.y, rtImg.right, h, AlphaDC, rtImg.left, rtImg.top, rtImg.right, rtImg.bottom, bf);
	// ����ۿ� �ϼ��� ���ĺ��� ����DC�� ������
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

void SpriteHelper::SetCurrentFrame(int f)
{
	CurrentFrame = f;
	rtImg = { (w / LastFrame) * CurrentFrame, 0, (w / LastFrame), h };
}

int SpriteHelper::GetCurrentFrame()
{
	return CurrentFrame;
}

int SpriteHelper::GetLastFrame()
{
	return LastFrame;
}

void SpriteHelper::NextFrameSprite(bool replay)
{
	rtImg = { (w / LastFrame) * CurrentFrame, 0, (w / LastFrame), h };
	CurrentFrame++;
	if (CurrentFrame >= LastFrame && !replay)
		CurrentFrame = LastFrame - 1;
	if (CurrentFrame >= LastFrame && replay)
		CurrentFrame = 1;
}

void SpriteHelper::NextFrameSprite_Trap()
{
	rtImg = { (w / LastFrame) * CurrentFrame, 0, (w / LastFrame), h };
	CurrentFrame++;
	if (CurrentFrame >= LastFrame)
		CurrentFrame = 0;
}


void SpriteHelper::SetFrameSprite(int f)
{
	CurrentFrame = 0;
	rtImg = { (w / LastFrame) * CurrentFrame, 0, (w / LastFrame), h };
}