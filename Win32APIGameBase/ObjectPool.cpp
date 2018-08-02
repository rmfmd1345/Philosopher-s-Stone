#include "stdafx.h"
#include "ObjectPool.h"

ObjectPool* ObjectPool::pool = nullptr;

void ObjectPool::CreateObject(HWND hWnd)	//��ü�� �ʱ� ������ ���� ��
{
	titleBtn_Start.Init(1000, 468, 124, 34, RGB(255, 0, 255)); //������ ��ġ�� ��ư �ʱ�ȭ

	titleBtn_Start.Btn_Bitmap[Button::Up].Init(hWnd, 1000, 468, 124, 34, L"./Image/UI/Main/ui_start.bmp");
	titleBtn_Start.Btn_Bitmap[Button::Over].Init(hWnd, 1000, 468, 134, 34, L"./Image/UI/Main/ui_start_up.bmp");
	titleBtn_Start.Btn_Bitmap[Button::Down].Init(hWnd, 1000, 468, 122, 34, L"./Image/UI/Main/ui_start_down.bmp");

	titleBtn_Start.Init(1000, 468, 124, 34);

	titleBtn_Start.Button_State_Num = Button::Up;

	//

	titleBtn_Credit.Init(1000, 528, 152, 46, RGB(255, 0, 255)); //������ ��ġ�� ��ư �ʱ�ȭ

	titleBtn_Credit.Btn_Bitmap[Button::Up].Init(hWnd, 1000, 528, 152, 46, L"./Image/UI/Main/ui_credit.bmp");
	titleBtn_Credit.Btn_Bitmap[Button::Over].Init(hWnd, 1000, 528, 164, 46, L"./Image/UI/Main/ui_credit_up.bmp");
	titleBtn_Credit.Btn_Bitmap[Button::Down].Init(hWnd, 1000, 528, 152, 46, L"./Image/UI/Main/ui_credit_down.bmp");

	titleBtn_Credit.Init(1000, 528, 152, 46);

	titleBtn_Credit.Button_State_Num = Button::Up;

	//

	titleBtn_Exit.Init(1000, 603, 104, 42, RGB(255, 0, 255)); //������ ��ġ�� ��ư �ʱ�ȭ

	titleBtn_Exit.Btn_Bitmap[Button::Up].Init(hWnd, 1000, 603, 104, 42, L"./Image/UI/Main/ui_exit.bmp");
	titleBtn_Exit.Btn_Bitmap[Button::Over].Init(hWnd, 1000, 603, 114, 42, L"./Image/UI/Main/ui_exit_up.bmp");
	titleBtn_Exit.Btn_Bitmap[Button::Down].Init(hWnd, 1000, 603, 104, 42, L"./Image/UI/Main/ui_exit_down.bmp");

	titleBtn_Exit.Init(1000, 603, 104, 42);

	titleBtn_Exit.Button_State_Num = Button::Up;

	//

	titleBg.Init(hWnd, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, L"./Image/Background/Main_Bg.bmp");
}

void ObjectPool::DeleteObject()				//��Ʈ�ʰ�ü�� �ݵ�� �������ֱ�
{
	titleBg.Ternimate();
	titleBtn_Start.Btn_Bitmap->Ternimate();
	titleBtn_Credit.Btn_Bitmap->Ternimate();
	titleBtn_Exit.Btn_Bitmap->Ternimate();
}