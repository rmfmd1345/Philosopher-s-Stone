#include "stdafx.h"
#include "ObjectPool.h"

ObjectPool* ObjectPool::pool = nullptr;

void ObjectPool::CreateObject(HWND hWnd)	//객체의 초기 설정을 적는 곳
{
	titleBtn.Init({ (SCREEN_WIDTH / 2) - 175, (SCREEN_HEIGHT / 2) + 50, (SCREEN_WIDTH / 2) + 175, (SCREEN_HEIGHT / 2) + 200 }, 
					RGB(0, 255, 0), 
					RGB(0, 255, 0),
					RGB(0, 200, 0));

	titleBg.Init(hWnd, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, L"./Image/titleBg.bmp");
}

void ObjectPool::DeleteObject()				//비트맵객체는 반드시 종료해주기
{
	titleBg.Ternimate();
}