#include "stdafx.h"
#include "ObjectPool.h"

ObjectPool* ObjectPool::pool = nullptr;

void ObjectPool::CreateObject(HWND hWnd)	//객체의 초기 설정을 적는 곳
{
	//title Scene
	titleBtn_Start.Init(hWnd, 1000, 468, 132, 34, L"./Image/UI/Main/ui_start.bmp", L"./Image/UI/Main/ui_start_down.bmp", L"./Image/UI/Main/ui_start_up.bmp"); //지정한 위치에 버튼 초기화

	titleBtn_Credit.Init(hWnd ,1000, 528, 164, 46, L"./Image/UI/Main/ui_credit.bmp", L"./Image/UI/Main/ui_credit_down.bmp", L"./Image/UI/Main/ui_credit_up.bmp"); //지정한 위치에 버튼 초기화

	titleBtn_Exit.Init(hWnd, 1000, 603, 114, 42, L"./Image/UI/Main/ui_exit.bmp", L"./Image/UI/Main/ui_exit_down.bmp", L"./Image/UI/Main/ui_exit_up.bmp"); //지정한 위치에 버튼 초기화

	titleBg.Init(hWnd, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, L"./Image/Background/Main_Bg.bmp");

	//credit Scene
	creditBg.Init(hWnd, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, L"./Image/Background/Credit_Bg.bmp");

	//ingame Scene
	ingameBtn_Option.Init(hWnd, 1200, 30, 56, 56, L"./Image/UI/Ingame/ui_option.bmp", L"./Image/UI/Ingame/ui_option_down.bmp", L"./Image/UI/Ingame/ui_option_up.bmp");
	
	ingameUI_Stone.Init(hWnd, 950, 25, 224, 70, L"./Image/UI/Ingame/ui_stone.bmp");
	
	ingameUI_Trap.Init(hWnd, 330, 585, 616, 136, L"./Image/UI/Ingame/ui_trap.bmp");

	ingameUI_SelectedTrap.Init(hWnd, 0, 0, 960, 240, 4, L"./Image/UI/Ingame/ui_selectedtrap.bmp");

	ingameUI_Skill.Init(hWnd, 20, 180, 104, 454, L"./Image/UI/Ingame/ui_skill.bmp");
	
	ingameUI_Stage.Init(hWnd, 0, 0, 400, 156, L"./Image/UI/Ingame/ui_stage.bmp");
	
	ingameUI_Time.Init(hWnd, 475, 0, 320, 134, L"./Image/UI/Ingame/ui_time.bmp");

	//Ending Scene
	EndingBg_Dead.Init(hWnd, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, L"./Image/Background/Ending_Bg.bmp");

	EndingBg_Clear.Init(hWnd, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, L"./Image/Background/Clear_Bg.bmp");

	//STATE ANI
	FindEffect.Init(hWnd, 0, 0, 84, 32, 6, L"./Image/Skill/findeffect.bmp");

	ConfuseEffect.Init(hWnd, 0, 0, 252, 24, 6, L"./Image/Skill/star_ani.bmp");

	Maps.InitMap(hWnd);

	Maps.ResetMap();

	MonsterPool.Init(hWnd);

	MonsterPool.Init(hWnd);
	Player.Init(hWnd, 2, 5);

	//Sound Init
	SoundPool.Init();
	ObjPool->SoundPool.Play(BGM_TITLE);
}

void ObjectPool::DeleteObject()				//비트맵객체는 반드시 종료해주기
{
	SoundPool.Terminate();

	titleBg.Ternimate();
	titleBtn_Start.Ternimate();
	titleBtn_Credit.Ternimate();
	titleBtn_Exit.Ternimate();

	creditBg.Ternimate();

	ingameBtn_Option.Ternimate();
	ingameUI_Stone.Ternimate();
	ingameUI_Trap.Ternimate();
	ingameUI_Skill.Ternimate();
	ingameUI_Stage.Ternimate();
	ingameUI_Time.Ternimate();

	Maps.DestroyMap();

	MonsterPool.Ternimate();
	FindEffect.Ternimate();
}