#include "stdafx.h"
#include "Scene.h"

void Ending::Draw(HDC hMemDC)
{
	ObjPool->EndingBg_Dead.Draw(hMemDC);

	/*
	if (ObjPool->Player.isDead())
	{
		ObjPool->EndingBg_Dead.Draw(hMemDC);
	}
	else
	{
		ObjPool->EndingBg_Clear.Draw(hMemDC);
	}
	*/
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
	ObjPool->Player.SetPosition(2, 5);
	ObjPool->Player.SetDirection(RIGHT);
	ObjPool->Player.ATK_Skill.Cooltime = 0;
	ObjPool->Player.AGGRO_Skill.Cooltime = 0;
	ObjPool->Player.PUSH_Skill.Cooltime = 0;
	ObjPool->Player.BARRICADE_Skill.Cooltime = 0;
	ObjPool->Player.Rock_Num = 0;

	ObjPool->MonsterPool.ePool.clear();
	ObjPool->MonsterPool.ePool_Next.clear();
	ObjPool->MonsterTimer = 0;

	ObjPool->Maps.ResetMap();

	ObjPool->SoundPool.Play(BGM_TITLE);
	ObjPool->SoundPool.Stop(BGM_CAVE);

	ObjPool->Wave = -1;
	ObjPool->MonsterPool.ResetSteal();

	//초기화 해야할 것 추가
}