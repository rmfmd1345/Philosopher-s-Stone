#include "stdafx.h"
#include "ObjectPool.h"

ObjectPool* ObjectPool::pool = nullptr;

void ObjectPool::CreateObject(HWND hWnd)	//객체의 초기 설정을 적는 곳
{
	titleBtn_Start.Init(hWnd, 1000, 468, 132, 34, L"./Image/UI/Main/ui_start.bmp", L"./Image/UI/Main/ui_start_down.bmp", L"./Image/UI/Main/ui_start_up.bmp"); //지정한 위치에 버튼 초기화

	titleBtn_Credit.Init(hWnd ,1000, 528, 164, 46, L"./Image/UI/Main/ui_credit.bmp", L"./Image/UI/Main/ui_credit_down.bmp", L"./Image/UI/Main/ui_credit_up.bmp"); //지정한 위치에 버튼 초기화

	titleBtn_Exit.Init(hWnd, 1000, 603, 114, 42, L"./Image/UI/Main/ui_exit.bmp", L"./Image/UI/Main/ui_exit_down.bmp", L"./Image/UI/Main/ui_exit_up.bmp"); //지정한 위치에 버튼 초기화

	titleBg.Init(hWnd, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, L"./Image/Background/Main_Bg.bmp");
}

void ObjectPool::DeleteObject()				//비트맵객체는 반드시 종료해주기
{
	titleBg.Ternimate();
	titleBtn_Start.Ternimate();
	titleBtn_Credit.Ternimate();
	titleBtn_Exit.Ternimate();
}