#include "stdafx.h"
#include "DrawManager.h"
#include "Scene.h"

void DrawManager::Initialize()
{

}

void DrawManager::Drawing(HWND hwnd)	//�׸��� �ܰ� (������۸� �����)
{
	hWnd = hwnd;

	hdc = GetDC(hWnd);					//���� DC
	hMemDC = CreateCompatibleDC(hdc);	//�ĸ� DC

	hBit = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
	SelectObject(hMemDC, hBit);

	switch (ObjPool->System.GetScene())	//�׸� �� üũ
	{
	case SCENE_TITLE:
		Title::Draw(hMemDC);	//�ĸ�DC ����
		break;
	case SCENE_INGAME:
		Ingame::Draw(hMemDC);
		break;
	}

	BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, hMemDC, 0, 0, SRCCOPY);	//�� �׸��⿡�� �׸��� �׷��� �ĸ�DC�� ȭ�鿡 ������ ����DC�� ����

	DeleteObject(hBit);
	DeleteDC(hMemDC);
	DeleteDC(hdc);
	ReleaseDC(hWnd, hdc);	//�ʱ�ȭ!
}

void DrawManager::Terminate()
{
	if (hBit != nullptr)
		DeleteObject(hBit);
	if (hMemDC != nullptr)
		DeleteDC(hMemDC);
	if (hdc != nullptr)
		DeleteDC(hdc);
}