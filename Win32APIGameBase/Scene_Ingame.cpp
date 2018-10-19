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
	ObjPool->Maps.DrawTileUI(hMemDC, PlayerPos.x, PlayerPos.y);

	ObjPool->MonsterPool.Draw(hMemDC, PlayerPos.x, PlayerPos.y);
	//ObjPool->Player.Draw(hMemDC, PlayerPos.x, PlayerPos.y);
	//MonsterPool.Draw에서 플레이어와 몬스터의 좌표를 확인해 부자연스럽게 겹치지 않도록 함.

	ObjPool->ingameBtn_Option.Draw(hMemDC);
	ObjPool->ingameUI_Stone.Draw(hMemDC);
	ObjPool->ingameUI_Trap.Draw(hMemDC);
	ObjPool->ingameUI_Skill.Draw(hMemDC);
	ObjPool->Player.DrawSelectedTrapUI(hMemDC);
	ObjPool->ingameUI_Stage.Draw(hMemDC);
	ObjPool->ingameUI_Time.Draw(hMemDC);
	ObjPool->Player.ATK_Skill.DrawSkillCooltime(hMemDC);
	ObjPool->Player.AGGRO_Skill.DrawSkillCooltime(hMemDC);
	ObjPool->Player.PUSH_Skill.DrawSkillCooltime(hMemDC);
	ObjPool->Player.BARRICADE_Skill.DrawSkillCooltime(hMemDC);

	ObjPool->Gdi.SetTextsColor(RGB(0, 124, 255));
	ObjPool->Gdi.Text(hMemDC, 560, 45, ObjPool->TIMER, 60);

	ObjPool->Gdi.SetTextsColor(RGB(255, 255, 255));
	ObjPool->Gdi.Text(hMemDC, 1020, 30, ObjPool->Player.Rock_Num_UI, 48);
}

void Ingame::OnTimer(HWND hWnd, int timer)
{
	if (timer == ANIMATION)
	{
		ObjPool->MonsterPool.Animation();
		ObjPool->MonsterPool.UpdateState();

		if (ObjPool->Player.ATK_Skill.Check_Active)
			ObjPool->Player.ATK_Skill.Animation();
		if (ObjPool->Player.PUSH_Skill.Check_Active)
			ObjPool->Player.PUSH_Skill.Animation();
		if (ObjPool->Player.BARRICADE_Skill.Check_Active)
			ObjPool->Player.BARRICADE_Skill.Animation();
	}

	if (timer == PLAYERWALK)
	{
		ObjPool->Player.Animation();
		ObjPool->Player.UpdateState();
	}

	if (timer == MONSTERTM)
	{
		if (ObjPool->MonsterPool.ePool.empty() && ObjPool->MonsterTimer <= 0)
		{
			int Temp = 0;

			Temp = rand() % 3;

			switch (Temp)
			{
			case DEALER:
				ObjPool->MonsterPool.AddMonster(DEALER);
				break;
			case WIZARD:
				ObjPool->MonsterPool.AddMonster(WIZARD);
				break;
			case TANKER:
				ObjPool->MonsterPool.AddMonster(TANKER);
				break;
			}

			ObjPool->MonsterTimer = 30;
			return;
		}

		if (ObjPool->MonsterTimer > 0)
		{
			ObjPool->MonsterTimer--;
		}

		if (ObjPool->Player.ATK_Skill.Cooltime > 0)
			ObjPool->Player.ATK_Skill.Cooltime--;
		if (ObjPool->Player.AGGRO_Skill.Cooltime > 0)
			ObjPool->Player.AGGRO_Skill.Cooltime--;
		if (ObjPool->Player.PUSH_Skill.Cooltime > 0)
			ObjPool->Player.PUSH_Skill.Cooltime--;
		if (ObjPool->Player.BARRICADE_Skill.Cooltime > 0)
			ObjPool->Player.BARRICADE_Skill.Cooltime--;
	}
	wsprintf(ObjPool->TIMER, L"%02d:%02d", ObjPool->MonsterTimer / 60, ObjPool->MonsterTimer % 60);
	wsprintf(ObjPool->Player.Rock_Num_UI, L"%05d", ObjPool->Player.Rock_Num);
}

void Ingame::Update() //씬 업데이트
{
	for (auto it = ObjPool->MonsterPool.ePool.begin(); it != ObjPool->MonsterPool.ePool.end();)
	{
		ObjPool->Maps.ActiveTile(it->GetEntity()); //몬스터에 대해 밟고 있는 타일 발동
		if (!ObjPool->MonsterPool.CheckHealth())
			it++;
		
		if (ObjPool->MonsterPool.ePool.empty()) break;
	}

	if (ObjPool->Player.GetState() == STAND && ObjPool->Player.isWaitingTrapSet == true) //이동중에 트랩 세팅을 명령했으면 그 다음 칸에 멈춰서서 함정설치
	{
		ObjPool->Player.SetState(TRAPSETTING); //플레이어 고정상태로 만들기
		ObjPool->Player.isWaitingTrapSet = false;
	}

	if (ObjPool->Player.GetState() == STAND && ObjPool->Player.isWaitingSkillSet == true) //이동중에 트랩 세팅을 명령했으면 그 다음 칸에 멈춰서서 함정설치
	{
		ObjPool->Player.SetState(SKILLPREPARING); //플레이어 고정상태로 만들기
		ObjPool->Player.isWaitingSkillSet = false;
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
	system("cls");
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
	DWORD exlastBitState = 0;
	DWORD exkeyState;
	exkeyState = GetAsyncKeyState(VK_F1);

	if (exlastBitState == 0 && exkeyState & 0x0001) //UP //이전에 0x1 이 0 이면 실행(안 누르다가 눌렀을 때)
	{
		ObjPool->MonsterPool.AddMonster(DEALER, 4, 4);
		exlastBitState = 1; // 누르는 중엔 실행되지 않도록 표시
	}
	if ((exkeyState & 0x8000) == 0) // 완전히 뗐다면 다음 실행을 위해서 상태 초기화
	{
		exlastBitState = 0;
	}

	DWORD lastBitState[14] = { 0, };
	DWORD keyState[14];

	keyState[0] = GetAsyncKeyState(VK_UP);
	keyState[1] = GetAsyncKeyState(VK_DOWN);
	keyState[2] = GetAsyncKeyState(VK_LEFT);
	keyState[3] = GetAsyncKeyState(VK_RIGHT);
	keyState[4] = GetAsyncKeyState(VK_SPACE);

	keyState[5] = GetAsyncKeyState(0x31); //1
	keyState[6] = GetAsyncKeyState(0x32); //2
	keyState[7] = GetAsyncKeyState(0x33); //3
	keyState[8] = GetAsyncKeyState(0x34); //4
	keyState[9] = GetAsyncKeyState(0x35); //5

	keyState[10] = GetAsyncKeyState(0x41); //A
	keyState[11] = GetAsyncKeyState(0x53); //S
	keyState[12] = GetAsyncKeyState(0x44); //D
	keyState[13] = GetAsyncKeyState(0x46); //F

	if (lastBitState[UP] == 0 && keyState[UP] & 0x0001) //B_UP //이전에 0x1 이 0 이면 실행(안 누르다가 눌렀을 때)
	{
		ObjPool->Player.SetDirection(UP);
		lastBitState[UP] = 1; // 누르는 중엔 실행되지 않도록 표시
	}

	if (lastBitState[DOWN] == 0 && keyState[DOWN] & 0x0001) //B_DOWN
	{
		ObjPool->Player.SetDirection(DOWN);
		lastBitState[DOWN] = 1;
	}

	if (lastBitState[LEFT] == 0 && keyState[LEFT] & 0x0001) //B_LEFT
	{
		ObjPool->Player.SetDirection(LEFT);
		lastBitState[LEFT] = 1;
	}

	if (lastBitState[RIGHT] == 0 && keyState[RIGHT] & 0x0001) //B_RIGHT
	{
		ObjPool->Player.SetDirection(RIGHT);
		lastBitState[RIGHT] = 1;
	}

	if (lastBitState[SPACE] == 0 && keyState[SPACE] & 0x0001) //SPACE
	{
		//보고 있는게 함정이면 수리
		printf("플레이어 상태: %d", ObjPool->Player.GetState());
		if (ObjPool->Maps.CheckTrap(ObjPool->Player.GetDirection(), ObjPool->Player.GetPosition()) && ObjPool->Player.GetState() != TRAPSETTING && ObjPool->Player.GetState() != SKILLPREPARING && ObjPool->Player.GetState() != WALK)
		{
			ObjPool->Player.RepairTrap();
		}
		else if (ObjPool->Player.GetState() == STAND)
		{
			ObjPool->Player.DigMap();
		}
		else if (ObjPool->Player.GetState() == TRAPSETTING) //트랩 세팅중이면 설치
		{
			ObjPool->Player.SetTrap();
			ObjPool->Player.SetState(STAND);
		}
		else if (ObjPool->Player.GetState() == SKILLPREPARING)
		{
			ObjPool->Player.UseSkill();
			ObjPool->Player.SetState(STAND);
		}
		ObjPool->Player.SetSelectedArea(false); //선택상태 해제

		lastBitState[SPACE] = 1;
	}

	//플레이어 작동
	if (lastBitState[KEY_1] == 0 && keyState[KEY_1] & 0x0001) //1번키
	{
		if (ObjPool->Player.GetState() == STAND && ObjPool->Player.Rock_Num >= 10) //플레이어가 서 있는 상태면
		{
			ObjPool->Player.SetState(TRAPSETTING); //플레이어 고정상태로 만들기
			ObjPool->Player.selectedTrap = TRAP_Niddle;
		}
		else if (ObjPool->Player.GetState() == WALK && ObjPool->Player.Rock_Num >= 10) //이동중에 누르면 다 걸어갈때까지 대기
		{
			ObjPool->Player.selectedTrap = TRAP_Niddle;
			ObjPool->Player.isWaitingTrapSet = true;
		}
		else if (ObjPool->Player.GetState() == TRAPSETTING && ObjPool->Player.selectedTrap == TRAP_Niddle) //고정상태에서 1번키를 한 번 더 누르면 고정해제
		{
			ObjPool->Player.selectedTrap = NONE;
			ObjPool->Player.SetState(STAND);
		}

		lastBitState[KEY_1] = 1;
	}

	if (lastBitState[KEY_2] == 0 && keyState[KEY_2] & 0x0001) //2번키
	{
		if (ObjPool->Player.GetState() == STAND && ObjPool->Player.Rock_Num >= 15)
		{
			ObjPool->Player.SetState(TRAPSETTING);
			ObjPool->Player.selectedTrap = TRAP_ScareCrow;
		}

		else if (ObjPool->Player.GetState() == WALK && ObjPool->Player.Rock_Num >= 15) //이동중에 누르면 다 걸어갈때까지 대기
		{
			ObjPool->Player.selectedTrap = TRAP_ScareCrow;
			ObjPool->Player.isWaitingTrapSet = true;
		}

		else if (ObjPool->Player.GetState() == TRAPSETTING && ObjPool->Player.selectedTrap == TRAP_ScareCrow)
		{
			ObjPool->Player.selectedTrap = NONE;
			ObjPool->Player.SetState(STAND);
		}

		lastBitState[KEY_2] = 1;
	}

	if (lastBitState[KEY_3] == 0 && keyState[KEY_3] & 0x0001) //3번키
	{
		if (ObjPool->Player.GetState() == STAND && ObjPool->Player.Rock_Num >= 20)
		{
			ObjPool->Player.SetState(TRAPSETTING);
			ObjPool->Player.selectedTrap = TRAP_Grab;
		}

		else if (ObjPool->Player.GetState() == WALK && ObjPool->Player.Rock_Num >= 20) //이동중에 누르면 다 걸어갈때까지 대기
		{
			ObjPool->Player.selectedTrap = TRAP_Grab;
			ObjPool->Player.isWaitingTrapSet = true;
		}

		else if (ObjPool->Player.GetState() == TRAPSETTING && ObjPool->Player.selectedTrap == TRAP_Grab)
		{
			ObjPool->Player.selectedTrap = NONE;
			ObjPool->Player.SetState(STAND);
		}


		lastBitState[KEY_3] = 1;
	}

	if (lastBitState[KEY_4] == 0 && keyState[KEY_4] & 0x0001 && ObjPool->Player.Rock_Num >= 25) //4번키
	{
		if (ObjPool->Player.GetState() == STAND)
		{
			ObjPool->Player.SetState(TRAPSETTING);
			ObjPool->Player.selectedTrap = TRAP_Confusion;
		}

		else if (ObjPool->Player.GetState() == WALK && ObjPool->Player.Rock_Num >= 25) //이동중에 누르면 다 걸어갈때까지 대기
		{
			ObjPool->Player.selectedTrap = TRAP_Confusion;
			ObjPool->Player.isWaitingTrapSet = true;
		}

		else if (ObjPool->Player.GetState() == TRAPSETTING && ObjPool->Player.selectedTrap == TRAP_Confusion)
		{
			ObjPool->Player.selectedTrap = NONE;
			ObjPool->Player.SetState(STAND);
		}

		lastBitState[KEY_4] = 1;
	}

	if (lastBitState[KEY_5] == 0 && keyState[KEY_5] & 0x0001) //5번키
	{
		if (ObjPool->Player.GetState() == STAND && ObjPool->Player.Rock_Num >= 30)
		{
			ObjPool->Player.SetState(TRAPSETTING);
			ObjPool->Player.selectedTrap = TRAP_Hole;
		}

		else if (ObjPool->Player.GetState() == WALK && ObjPool->Player.Rock_Num >= 30) //이동중에 누르면 다 걸어갈때까지 대기
		{
			ObjPool->Player.selectedTrap = TRAP_Hole;
			ObjPool->Player.isWaitingTrapSet = true;
		}

		else if (ObjPool->Player.GetState() == TRAPSETTING && ObjPool->Player.selectedTrap == TRAP_Hole)
		{
			ObjPool->Player.selectedTrap = NONE;
			ObjPool->Player.SetState(STAND);
		}

		lastBitState[KEY_5] = 1;
	}

	if (lastBitState[KEY_A] == 0 && keyState[KEY_A] & 0x0001) //B_RIGHT
	{
		if (ObjPool->Player.ATK_Skill.Cooltime <= 0)
		{
			if (ObjPool->Player.GetState() == STAND)
			{
				ObjPool->Player.selectedSkill = ATK_SKILL;
				ObjPool->Player.UseSkill();
			}
		}

		lastBitState[KEY_A] = 1;
	}

	if (lastBitState[KEY_S] == 0 && keyState[KEY_S] & 0x0001) //B_RIGHT
	{
		if (ObjPool->Player.AGGRO_Skill.Cooltime <= 0)
		{
			if (ObjPool->Player.GetState() == STAND)
			{
				ObjPool->Player.selectedSkill = AGGRO_SKILL;
				ObjPool->Player.UseSkill();
			}
		}

		lastBitState[KEY_S] = 1;
	}

	if (lastBitState[KEY_D] == 0 && keyState[KEY_D] & 0x0001) //B_RIGHT
	{
		if (ObjPool->Player.PUSH_Skill.Cooltime <= 0)
		{
			if (ObjPool->Player.GetState() == STAND)
			{
				ObjPool->Player.SetState(SKILLPREPARING);
				ObjPool->Player.selectedSkill = PUSH_SKILL;
			}

			else if (ObjPool->Player.GetState() == WALK) //이동중에 누르면 다 걸어갈때까지 대기
			{
				ObjPool->Player.selectedSkill = PUSH_SKILL;
				ObjPool->Player.isWaitingSkillSet = true;
			}

			else if (ObjPool->Player.GetState() == SKILLPREPARING && ObjPool->Player.selectedSkill == PUSH_SKILL)
			{
				ObjPool->Player.selectedSkill = NONE;
				ObjPool->Player.SetState(STAND);
			}
		}

		lastBitState[KEY_D] = 1;
	}

	if (lastBitState[KEY_F] == 0 && keyState[KEY_F] & 0x0001) //B_RIGHT
	{
		if (ObjPool->Player.BARRICADE_Skill.Cooltime <= 0)
		{
			if (ObjPool->Player.GetState() == STAND)
			{
				ObjPool->Player.SetState(SKILLPREPARING);
				ObjPool->Player.selectedSkill = BARRICADE_SKILL;
			}

			else if (ObjPool->Player.GetState() == WALK) //이동중에 누르면 다 걸어갈때까지 대기
			{
				ObjPool->Player.selectedSkill = BARRICADE_SKILL;
				ObjPool->Player.isWaitingSkillSet = true;
			}

			else if (ObjPool->Player.GetState() == SKILLPREPARING && ObjPool->Player.selectedSkill == BARRICADE_SKILL)
			{
				ObjPool->Player.selectedSkill = NONE;
				ObjPool->Player.SetState(STAND);
			}
		}

		lastBitState[KEY_F] = 1;
	}

	for (int i = 0; i < 14; i++)
	{
		if ((keyState[14] & 0x8000) == 0) // 완전히 뗐다면 다음 실행을 위해서 상태 초기화
		{
			lastBitState[i] = 0;
		}
	}
}