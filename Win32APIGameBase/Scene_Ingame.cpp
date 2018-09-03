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
	//MonsterPool.Draw���� �÷��̾�� ������ ��ǥ�� Ȯ���� ���ڿ������� ��ġ�� �ʵ��� ��. 

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
	
	if (lastBitState[UP] == 0 && keyState[UP] & 0x0001) //UP //������ 0x1 �� 0 �̸� ����(�� �����ٰ� ������ ��)
	{
		ObjPool->Player.SetDirection(UP);
		lastBitState[UP] = 1; // ������ �߿� ������� �ʵ��� ǥ��
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
		ObjPool->Player.DigMap();
		if (ObjPool->Player.selectedTrap != NONE) ObjPool->Player.SetTrap();
		lastBitState[SPACE] = 1;
	}

	//�÷��̾� �۵�
	if (lastBitState[KEY_1] == 0 && keyState[KEY_1] & 0x0001) //1��Ű
	{
		ObjPool->Player.selectedTrap = TRAP_Niddle;
		lastBitState[KEY_1] = 1;
	}

	if (lastBitState[KEY_2] == 0 && keyState[KEY_2] & 0x0001) //2��Ű
	{
		ObjPool->Player.selectedTrap = TRAP_Hole;
		lastBitState[KEY_2] = 1;
	}

	if (lastBitState[KEY_3] == 0 && keyState[KEY_3] & 0x0001) //3��Ű
	{
		ObjPool->Player.selectedTrap = TRAP_ScareCrow;
		lastBitState[KEY_3] = 1;
	}

	if (lastBitState[KEY_4] == 0 && keyState[KEY_4] & 0x0001) //4��Ű
	{
		ObjPool->Player.selectedTrap = TRAP_Grap;
		lastBitState[KEY_4] = 1;
	}

	for (int i = 0; i < 4; i++)
	{
		if ((keyState[i] & 0x8000) == 0) // ������ �ôٸ� ���� ������ ���ؼ� ���� �ʱ�ȭ
		{
			lastBitState[i] = 0;
		}
	}
}