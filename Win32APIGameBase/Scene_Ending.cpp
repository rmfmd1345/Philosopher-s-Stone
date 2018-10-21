#include "stdafx.h"
#include "Scene.h"

void Ending::Draw(HDC hMemDC)
{
	if (ObjPool->Player.isDead())
	{
		ObjPool->EndingBg_Dead.Draw(hMemDC);
	}
	else
	{

	}
}

void Ending::OnTimer(HWND hWnd, int timer)
{

}

void Ending::Update()
{

}

void Ending::OnMouseLButtonDown(HWND hWnd, int x, int y)
{
	
}

void Ending::OnMouseLButtonUp(HWND hWnd, int x, int y)
{
	ObjPool->System.SetScene(SCENE_TITLE);
}