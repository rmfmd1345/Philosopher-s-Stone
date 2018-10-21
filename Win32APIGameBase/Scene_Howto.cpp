#include "stdafx.h"
#include "Scene.h"

void Howto::Draw(HDC hMemDC)
{
	ObjPool->howto[ObjPool->howtonum].Draw(hMemDC);
}

void Howto::OnTimer(HWND hWnd, int timer)
{

}

void Howto::Update()
{

}

void Howto::OnMouseLButtonDown(HWND hWnd, int x, int y)
{

}

void Howto::OnMouseLButtonUp(HWND hWnd, int x, int y)
{
	ObjPool->SoundPool.Play(EFFECT_SELECT);
	if (ObjPool->howtonum < 2)
		ObjPool->howtonum++;
	else
	{
		ObjPool->System.SetScene(SCENE_INGAME);	//¾ÀÀ» ¹Ù²Û´Ù
		ObjPool->SoundPool.Play(BGM_SAFE);
		ObjPool->SoundPool.Stop(BGM_TITLE);
	}
}