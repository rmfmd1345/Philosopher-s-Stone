#include "stdafx.h"
#include "DrawManager.h"
#include "Scene.h"

void DrawManager::Initialize()
{

}

void DrawManager::Drawing(HWND hwnd)	//그리기 단계 (더블버퍼링 적용됨)
{
	hWnd = hwnd;

	hdc = GetDC(hWnd);					//전면 DC
	hMemDC = CreateCompatibleDC(hdc);	//후면 DC

	hBit = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
	SelectObject(hMemDC, hBit);

	switch (ObjPool->System.GetScene())	//그릴 씬 체크
	{
	case SCENE_TITLE:
		Title::Draw(hMemDC);	//후면DC 전송
		break;
	case SCENE_INGAME:
		Ingame::Draw(hMemDC);
		break;
	}

	BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, hMemDC, 0, 0, SRCCOPY);	//씬 그리기에서 그림이 그려진 후면DC를 화면에 보여질 전면DC로 복사

	DeleteObject(hBit);
	DeleteDC(hMemDC);
	DeleteDC(hdc);
	ReleaseDC(hWnd, hdc);	//초기화!
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