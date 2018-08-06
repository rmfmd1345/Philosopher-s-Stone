#include "stdafx.h"
#include "Scene.h"

void Credit::Draw(HDC hMemDC)
{
	ObjPool->creditBg.Draw(hMemDC);
}

void Credit::OnTimer(HWND hWnd, int timer)
{

}

void Credit::OnMouseLButtonDown(HWND hWnd, int x, int y)
{

}

void Credit::OnMouseLButtonUp(HWND hWnd, int x, int y)
{

}

void Credit::OnMouseRButtonDown(HWND hWnd, int x, int y)
{

}

void Credit::OnMouseRButtonUp(HWND hWnd, int x, int y)
{

}

void Credit::OnMouseMove(HWND hWnd, int x, int y)
{

}

void Credit::OnKeyborad()
{
	if (GetAsyncKeyState(VK_SPACE))	//키보드 입력이 VK_SPACE라면 타이틀로 돌아가기
	{
		ObjPool->System.SetScene(SCENE_TITLE);	//씬을 바꾼다
	}
}