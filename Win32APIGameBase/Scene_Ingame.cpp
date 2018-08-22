#include "stdafx.h"
#include "Scene.h"

POINT PlayerPos = ObjPool->Player.GetPosition();

void Ingame::Draw(HDC hMemDC)
{
	PlayerPos = ObjPool->Player.GetPosition();

	ObjPool->Gdi.SetPenColor(RGB(10, 23, 55));
	ObjPool->Gdi.SetBrushColor(RGB(10, 23, 55));
	ObjPool->Gdi.Rect(hMemDC, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });

	ObjPool->Maps.DrawMap(hMemDC, PlayerPos.x, PlayerPos.y);
	ObjPool->Maps.DrawBrick(hMemDC, PlayerPos.x, PlayerPos.y);

	ObjPool->MonsterPool.Draw(hMemDC, PlayerPos.x, PlayerPos.y);
	//ObjPool->Player.Draw(hMemDC, PlayerPos.x, PlayerPos.y);
	//MonsterPool.Draw에서 플레이어와 몬스터의 좌표를 확인해 부자연스럽게 겹치지 않도록 함. 

	ObjPool->ingameBtn_Option.Draw(hMemDC);
	ObjPool->ingameUI_Stone.Draw(hMemDC);
	ObjPool->ingameUI_Trap.Draw(hMemDC);
	ObjPool->ingameUI_Skill.Draw(hMemDC);
	ObjPool->ingameUI_Stage.Draw(hMemDC);
	ObjPool->ingameUI_Time.Draw(hMemDC);
}

void Ingame::OnTimer(HWND hWnd, int timer)
{
	if (timer == ANIMATION)
	{
		ObjPool->MonsterPool.Animation();
		ObjPool->MonsterPool.UpdateState();

		ObjPool->Player.Animation();
		ObjPool->Player.UpdateState();
	}
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

	if (PlayerPos.x <= 8)
		PlayerPos.x = 8;
	if (PlayerPos.y <= 5)
		PlayerPos.y = 5;
	if (PlayerPos.x >= 24)
		PlayerPos.x = 24;
	if (PlayerPos.y >= 11)
		PlayerPos.y = 11;

	int Map_Start_x = PlayerPos.x - 8;
	int Map_Start_y = PlayerPos.y - 5;

	//For test
	ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Floor, (x / 80) + Map_Start_x, (y / 80) + Map_Start_y);
}

void Ingame::OnMouseRButtonDown(HWND hWnd, int x, int y)
{
	
}

void Ingame::OnMouseRButtonUp(HWND hWnd, int x, int y)
{
	if (PlayerPos.x <= 8)
		PlayerPos.x = 8;
	if (PlayerPos.y <= 5)
		PlayerPos.y = 5;
	if (PlayerPos.x >= 24)
		PlayerPos.x = 24;
	if (PlayerPos.y >= 11)
		PlayerPos.y = 11;

	int Map_Start_x = PlayerPos.x - 8;
	int Map_Start_y = PlayerPos.y - 5;

	//For test
	ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Trap_Niddle, (x / 80) + Map_Start_x, (y / 80) + Map_Start_y);
}

void Ingame::OnMouseMove(HWND hWnd, int x, int y)
{
	ObjPool->ingameBtn_Option.isOver(x, y);
}

void Ingame::OnKeyborad()
{
	DWORD lastBitState[9] = {0, };
	DWORD keyState[9];

	keyState[0] = GetAsyncKeyState(VK_UP);
	keyState[1] = GetAsyncKeyState(VK_DOWN);
	keyState[2] = GetAsyncKeyState(VK_LEFT);
	keyState[3] = GetAsyncKeyState(VK_RIGHT);
	keyState[4] = GetAsyncKeyState(VK_SPACE);

	//keyState[5] = GetAsyncKeyState(0x57); //W
	//keyState[6] = GetAsyncKeyState(0x41); //A
	//keyState[7] = GetAsyncKeyState(0x53); //S
	//keyState[8] = GetAsyncKeyState(0x44); //D
	
	if (lastBitState[UP] == 0 && keyState[UP] & 0x0001) //UP //이전에 0x1 이 0 이면 실행(안 누르다가 눌렀을 때)
	{
		ObjPool->Player.SetDirection(UP);
		lastBitState[UP] = 1; // 누르는 중엔 실행되지 않도록 표시
	}

	if (lastBitState[DOWN] == 0 && keyState[DOWN] & 0x0001) //DOWN
	{
		ObjPool->Player.SetDirection(DOWN);
		lastBitState[DOWN] = 1;
	}

	if (lastBitState[LEFT] == 0 && keyState[LEFT] & 0x0001) //LEFT
	{
		ObjPool->Player.SetDirection(LEFT);
		lastBitState[LEFT] = 1;
	}

	if (lastBitState[RIGHT] == 0 && keyState[RIGHT] & 0x0001) //RIGHT
	{
		ObjPool->Player.SetDirection(RIGHT);
		lastBitState[RIGHT] = 1;
	}

	if (lastBitState[4] == 0 && keyState[4] & 0x0001) //SPACE
	{
		lastBitState[4] = 1;
	}

	//플레이어 작동
	//if (lastBitState[5] == 0 && keyState[5] & 0x0001) //W
	//{
	//	ObjPool->Player.SetDirection(UP);
	//	lastBitState[5] = 1;
	//}

	//if (lastBitState[6] == 0 && keyState[6] & 0x0001) //A
	//{
	//	ObjPool->Player.SetDirection(LEFT);
	//	lastBitState[6] = 1;
	//}

	//if (lastBitState[7] == 0 && keyState[7] & 0x0001) //S
	//{
	//	ObjPool->Player.SetDirection(DOWN);
	//	lastBitState[7] = 1;
	//}

	//if (lastBitState[8] == 0 && keyState[8] & 0x0001) //D
	//{
	//	ObjPool->Player.SetDirection(RIGHT);
	//	lastBitState[8] = 1;
	//}

	for (int i = 0; i < 4; i++)
	{
		if ((keyState[i] & 0x8000) == 0) // 완전히 뗐다면 다음 실행을 위해서 상태 초기화
		{
			lastBitState[i] = 0;
		}
	}
}