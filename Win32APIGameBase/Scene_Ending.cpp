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
	ObjPool->Player.AddHealth(1);
	ObjPool->Player.SetPosition(2, 5);
	ObjPool->Player.SetDirection(RIGHT);

	ObjPool->MonsterPool.ePool.clear();
	ObjPool->MonsterPool.ePool_Next.clear();
	ObjPool->MonsterTimer = 0;

	ObjPool->Maps.ResetMap();

	ObjPool->Sounds.Push(BGM_TITLE, 1);
	ObjPool->Sounds.Pop(0);

	//초기화 해야할 것 추가
}