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

	ObjPool->MonsterPool.Draw(hMemDC, PlayerPos.x, PlayerPos.y);
	//ObjPool->Player.Draw(hMemDC, PlayerPos.x, PlayerPos.y);
	//MonsterPool.Draw에서 플레이어와 몬스터의 좌표를 확인해 부자연스럽게 겹치지 않도록 함. 

	ObjPool->Maps.DrawBrick(hMemDC, PlayerPos.x, PlayerPos.y);

	ObjPool->ingameBtn_Option.Draw(hMemDC);
	ObjPool->ingameUI_Stone.Draw(hMemDC);
	ObjPool->ingameUI_Trap.Draw(hMemDC);
	ObjPool->ingameUI_Skill.Draw(hMemDC);
	ObjPool->ingameUI_Stage.Draw(hMemDC);
	ObjPool->ingameUI_Time.Draw(hMemDC);
}

void Ingame::OnTimer(HWND hWnd, int timer)
{
	if (timer == UPDATE)
	{
		ObjPool->Maps.ActiveTile(ObjPool->Player.GetPosition());
	}
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
}

void Ingame::OnMouseRButtonDown(HWND hWnd, int x, int y)
{
	
}

void Ingame::OnMouseRButtonUp(HWND hWnd, int x, int y)
{
	
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

	keyState[5] = GetAsyncKeyState(0x31); //1
	keyState[6] = GetAsyncKeyState(0x32); //2
	keyState[7] = GetAsyncKeyState(0x33); //3
	keyState[8] = GetAsyncKeyState(0x34); //4
	
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

	if (lastBitState[SPACE] == 0 && keyState[SPACE] & 0x0001) //SPACE
	{
		if (ObjPool->Player.GetState() == STAND) //그냥 서있는 상태면 땅 파고
			ObjPool->Player.DigMap();

		else if (ObjPool->Player.GetState() == TRAPSETTING) //트랩 세팅중이면 설치
		{
			ObjPool->Player.SetTrap();
			ObjPool->Player.SetState(STAND);
		}

		lastBitState[SPACE] = 1;
	}

	//플레이어 작동
	if (lastBitState[KEY_1] == 0 && keyState[KEY_1] & 0x0001) //1번키
	{
		/* 플레이어 이동 중에 1번키를 누르면, 일단 걸어간 후 다음 칸부터 TRAPSETTING 모드가 되게 하고 싶은데 방법 없나 */
		if (ObjPool->Player.GetState() == STAND) //플레이어가 서 있는 상태면
		{
			ObjPool->Player.SetState(TRAPSETTING); //플레이어 고정상태로 만들기
			ObjPool->Player.selectedTrap = TRAP_Niddle;
		}

		else if (ObjPool->Player.GetState() == TRAPSETTING) //고정상태에서 1번키를 한 번 더 누르면 고정해제
			ObjPool->Player.SetState(STAND);

		lastBitState[KEY_1] = 1;
	}

	if (lastBitState[KEY_2] == 0 && keyState[KEY_2] & 0x0001) //2번키
	{
		if (ObjPool->Player.GetState() == STAND)
		{
			ObjPool->Player.SetState(TRAPSETTING);
			ObjPool->Player.selectedTrap = TRAP_Hole;
		}

		else if (ObjPool->Player.GetState() == TRAPSETTING)
			ObjPool->Player.SetState(STAND);

		lastBitState[KEY_2] = 1;
	}

	if (lastBitState[KEY_3] == 0 && keyState[KEY_3] & 0x0001) //3번키
	{
		if (ObjPool->Player.GetState() == STAND)
		{
			ObjPool->Player.SetState(TRAPSETTING);
			ObjPool->Player.selectedTrap = TRAP_ScareCrow;
		}

		else if (ObjPool->Player.GetState() == TRAPSETTING)
			ObjPool->Player.SetState(STAND);

		lastBitState[KEY_3] = 1;
	}

	if (lastBitState[KEY_4] == 0 && keyState[KEY_4] & 0x0001) //4번키
	{
		if (ObjPool->Player.GetState() == STAND)
		{
			ObjPool->Player.SetState(TRAPSETTING);
			ObjPool->Player.selectedTrap = TRAP_Grap;
		}

		else if (ObjPool->Player.GetState() == TRAPSETTING)
			ObjPool->Player.SetState(STAND);

		lastBitState[KEY_4] = 1;
	}

	for (int i = 0; i < 4; i++)
	{
		if ((keyState[i] & 0x8000) == 0) // 완전히 뗐다면 다음 실행을 위해서 상태 초기화
		{
			lastBitState[i] = 0;
		}
	}
}