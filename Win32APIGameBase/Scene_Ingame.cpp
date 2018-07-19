#include "stdafx.h"
#include "Scene.h"

void Ingame::Draw(HDC hMemDC)
{
	ObjPool->Gdi.SetBrushColor(RGB(150, 150, 200));
	ObjPool->Gdi.Rect(hMemDC, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });

	ObjPool->Gdi.SetTextsColor(RGB(250, 250, 250));
	ObjPool->Gdi.Text(hMemDC, 100, 100, L"인게임 인 듯");
}

void Ingame::OnTimer(HWND hWnd, int timer)
{

}

void Ingame::OnMouseLButton(HWND hWnd, int x, int y)
{

}

void Ingame::OnMouseRButton(HWND hWnd, int x, int y)
{

}

void Ingame::OnMouseMove(HWND hWnd, int x, int y)
{

}

void Ingame::OnKeyborad()
{

}