#include "stdafx.h"
#include "Scene.h"

void Ending::Draw(HDC hMemDC)
{
	if (ObjPool->Endingnum == HAPPYENDING)
	{
		ObjPool->happyendingBg.Draw(hMemDC);
	}
	else
	{
		ObjPool->badendingBg.Draw(hMemDC);
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
	ObjPool->SoundPool.Play(EFFECT_SELECT);
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
	ObjPool->SoundPool.Stop(BGM_HAPPY);
	ObjPool->SoundPool.Stop(BGM_BAD);

	ObjPool->Wave = -1;
	ObjPool->MonsterPool.ResetSteal();

	ObjPool->howtonum = 0;
	ObjPool->Player.Checkending = false;
	ObjPool->aniEnding = 0;
	ObjPool->Endingnum = 0;
	ObjPool->CheckMonster = false;

	//초기화 해야할 것 추가
}