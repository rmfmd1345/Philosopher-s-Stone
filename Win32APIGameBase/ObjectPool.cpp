#include "stdafx.h"
#include "ObjectPool.h"

ObjectPool* ObjectPool::pool = nullptr;

void ObjectPool::CreateObject(HWND hWnd)	//��ü�� �ʱ� ������ ���� ��
{
	titleBtn_Start.Init(hWnd, 1000, 468, 132, 34, L"./Image/UI/Main/ui_start.bmp", L"./Image/UI/Main/ui_start_down.bmp", L"./Image/UI/Main/ui_start_up.bmp"); //������ ��ġ�� ��ư �ʱ�ȭ

	titleBtn_Credit.Init(hWnd ,1000, 528, 164, 46, L"./Image/UI/Main/ui_credit.bmp", L"./Image/UI/Main/ui_credit_down.bmp", L"./Image/UI/Main/ui_credit_up.bmp"); //������ ��ġ�� ��ư �ʱ�ȭ

	titleBtn_Exit.Init(hWnd, 1000, 603, 114, 42, L"./Image/UI/Main/ui_exit.bmp", L"./Image/UI/Main/ui_exit_down.bmp", L"./Image/UI/Main/ui_exit_up.bmp"); //������ ��ġ�� ��ư �ʱ�ȭ

	titleBg.Init(hWnd, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, L"./Image/Background/Main_Bg.bmp");
}

void ObjectPool::DeleteObject()				//��Ʈ�ʰ�ü�� �ݵ�� �������ֱ�
{
	titleBg.Ternimate();
	titleBtn_Start.Ternimate();
	titleBtn_Credit.Ternimate();
	titleBtn_Exit.Ternimate();
}