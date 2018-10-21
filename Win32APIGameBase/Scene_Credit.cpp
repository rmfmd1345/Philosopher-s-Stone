#include "stdafx.h"
#include "Scene.h"

void Credit::Draw(HDC hMemDC)
{
	ObjPool->creditBg.Draw(hMemDC);
}

void Credit::OnTimer(HWND hWnd, int timer)
{

}

void Credit::Update()
{

}

void Credit::OnMouseLButtonDown(HWND hWnd, int x, int y)
{

}

void Credit::OnMouseLButtonUp(HWND hWnd, int x, int y)
{
	ObjPool->SoundPool.Play(EFFECT_SELECT);
	ObjPool->System.SetScene(SCENE_TITLE);	//æ¿¿ª πŸ≤€¥Ÿ
}
