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

	//howto Scene
	howto[0].Init(hWnd, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, L"./Image/Background/how_to_1.bmp");
	howto[1].Init(hWnd, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, L"./Image/Background/how_to_2.bmp");
	howto[2].Init(hWnd, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, L"./Image/Background/how_to_3.bmp");

	//ingame Scene
	ingameBtn_Option.Init(hWnd, 1200, 30, 56, 56, L"./Image/UI/Ingame/ui_option.bmp", L"./Image/UI/Ingame/ui_option_down.bmp", L"./Image/UI/Ingame/ui_option_up_empty.bmp");
	
	ingameSprite_Option.Init(hWnd, 1200, 28, 224, 60, 4, L"./Image/UI/Ingame/ui_option_up_ani.bmp");
	
	ingameUI_Stone.Init(hWnd, 950, 25, 224, 70, L"./Image/UI/Ingame/ui_stone.bmp");
	
	ingameUI_Trap.Init(hWnd, 330, 585, 616, 136, L"./Image/UI/Ingame/ui_trap.bmp");

	ingameUI_SelectedTrap.Init(hWnd, 0, 0, 960, 240, 4, L"./Image/UI/Ingame/ui_selectedtrap.bmp");

	ingameUI_Skill.Init(hWnd, 20, 180, 104, 454, L"./Image/UI/Ingame/ui_skill.bmp");
	
	ingameUI_Stage.Init(hWnd, 0, 0, 400, 156, L"./Image/UI/Ingame/ui_stage.bmp");

	ingameUI_Stage_Steal.Init(hWnd, 0, 0, 400, 156, L"./Image/UI/Ingame/ui_stage_off.bmp");
	
	ingameUI_Time.Init(hWnd, 475, 0, 320, 134, L"./Image/UI/Ingame/ui_time.bmp");

	//Ending Scene
	badendingBg.Init(hWnd, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, L"./Image/Background/Ending_Bg.bmp");

	happyendingBg.Init(hWnd, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, L"./Image/Background/Clear_Bg.bmp");

	//STATE ANI
	FindEffect.Init(hWnd, 0, 0, 84, 32, 6, L"./Image/Skill/findeffect.bmp");

	ConfuseEffect.Init(hWnd, 0, 0, 252, 24, 6, L"./Image/Skill/star_ani.bmp");

	Maps.InitMap(hWnd);

	Maps.ResetMap();

	MonsterPool.Init(hWnd);
	StoneEffect.Init(hWnd, 0, 0, 20, 26, L"./Image/UI/Ingame/stone.bmp");

	MonsterPool.Init(hWnd);
	Player.Init(hWnd, 2, 5);

	//Sound Init
	SoundPool.Init();
	ObjPool->SoundPool.Play(BGM_TITLE);
}

void ObjectPool::DeleteObject()				//비트맵객체는 반드시 종료해주기
{
	SoundPool.Terminate();

	FindEffect.Ternimate();
	ConfuseEffect.Ternimate();
	StoneEffect.Ternimate();

	//title Scene
	titleBtn_Start.Ternimate();	//버튼
	titleBtn_Credit.Ternimate();
	titleBtn_Exit.Ternimate();

	titleBg.Ternimate();
	badendingBg.Ternimate();
	happyendingBg.Ternimate();

	//credit Scene
	creditBg.Ternimate();

	//howto Scene
	howto[0].Ternimate();
	howto[1].Ternimate();
	howto[2].Ternimate();

	Maps.DestroyMap();
	ingameBtn_Option.Ternimate();
	ingameSprite_Option.Ternimate();
	ingameUI_Stone.Ternimate();
	ingameUI_Trap.Ternimate();
	ingameUI_Skill.Ternimate();
	ingameUI_Stage.Ternimate();
	ingameUI_Stage_Steal.Ternimate();
	ingameUI_Time.Ternimate();

	ingameUI_SelectedTrap.Ternimate();
}