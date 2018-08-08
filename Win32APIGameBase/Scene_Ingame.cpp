#include "stdafx.h"
#include "Scene.h"

//For test
static int testC_x = 5;
static int testC_y = 5;

void Ingame::Draw(HDC hMemDC)
{
	ObjPool->Gdi.SetBrushColor(RGB(0, 0, 0));
	ObjPool->Gdi.Rect(hMemDC, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });
	ObjPool->Maps.DrawMap(hMemDC, testC_x, testC_y);
	ObjPool->Maps.DrawBrick(hMemDC, testC_x, testC_y);
	ObjPool->ingameBtn_Option.Draw(hMemDC);
	ObjPool->ingameUI_Stone.Draw(hMemDC);
	ObjPool->ingameUI_Trap.Draw(hMemDC);
	ObjPool->ingameUI_Skill.Draw(hMemDC);
	ObjPool->ingameUI_Stage.Draw(hMemDC);
	ObjPool->ingameUI_Time.Draw(hMemDC);
}

void Ingame::OnTimer(HWND hWnd, int timer)
{

}

void Ingame::OnMouseLButtonDown(HWND hWnd, int x, int y)
{
	ObjPool->ingameBtn_Option.isClickDown(x, y);
}

void Ingame::OnMouseLButtonUp(HWND hWnd, int x, int y)
{
	if (ObjPool->ingameBtn_Option.isClickUp(x, y))
	{
		ObjPool->System.SetScene(SCENE_OPTION);
	}

	if (testC_x <= 9)
		testC_x = 9;
	if (testC_y <= 5)
		testC_y = 5;
	if (testC_x >= 23)
		testC_x = 23;
	if (testC_y >= 11)
		testC_y = 11;

	int Map_Start_x = testC_x - 9;
	int Map_Start_y = testC_y - 5;

	//For test
	ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Floor, (x / 80) + Map_Start_x, (y / 80) + Map_Start_y);
}

void Ingame::OnMouseRButtonDown(HWND hWnd, int x, int y)
{
	
}

void Ingame::OnMouseRButtonUp(HWND hWnd, int x, int y)
{
	if (testC_x <= 9)
		testC_x = 9;
	if (testC_y <= 5)
		testC_y = 5;
	if (testC_x >= 23)
		testC_x = 23;
	if (testC_y >= 11)
		testC_y = 11;

	int Map_Start_x = testC_x - 9;
	int Map_Start_y = testC_y - 5;

	//For test
	ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Trap_Niddle, (x / 80) + Map_Start_x, (y / 80) + Map_Start_y);
}

void Ingame::OnMouseMove(HWND hWnd, int x, int y)
{
	ObjPool->ingameBtn_Option.isOver(x, y);
}

enum eKeyInput
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

void Ingame::OnKeyborad()
{
	DWORD lastBitState[4] = { 0,0,0,0 };
	DWORD keyState[4];

	keyState[0] = GetAsyncKeyState(VK_UP);
	keyState[1] = GetAsyncKeyState(VK_DOWN);
	keyState[2] = GetAsyncKeyState(VK_LEFT);
	keyState[3] = GetAsyncKeyState(VK_RIGHT);

	if (lastBitState[UP] == 0 && keyState[UP] & 0x0001) // 이전에 0x1 이 0 이면 실행(안 누르다가 눌렀을 때)
	{
		if (testC_y > 0)
			testC_y--;
		lastBitState[UP] = 1; // 누르는 중엔 실행되지 않도록 표시
	}

	if (lastBitState[DOWN] == 0 && keyState[DOWN] & 0x0001)
	{
		if (testC_y < 16)
			testC_y++;
		lastBitState[DOWN] = 1;
	}

	if (lastBitState[LEFT] == 0 && keyState[LEFT] & 0x0001)
	{
		if (testC_x > 0)
			testC_x--;
		lastBitState[LEFT] = 1;
	}

	if (lastBitState[RIGHT] == 0 && keyState[RIGHT] & 0x0001)
	{
		if (testC_x < 32)
			testC_x++;
		lastBitState[RIGHT] = 1;
	}

	for (int i = 0; i < 4; i++)
	{
		if ((keyState[i] & 0x8000) == 0) // 완전히 뗐다면 다음 실행을 위해서 상태 초기화
		{
			lastBitState[i] = 0;
		}
	}
}