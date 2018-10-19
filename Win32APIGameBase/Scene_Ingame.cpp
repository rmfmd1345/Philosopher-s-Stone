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
	//MonsterPool.Draw���� �÷��̾�� ������ ��ǥ�� Ȯ���� ���ڿ������� ��ġ�� �ʵ��� ��.

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

void Ingame::Update() //�� ������Ʈ
{
	for (auto it = ObjPool->MonsterPool.ePool.begin(); it != ObjPool->MonsterPool.ePool.end();)
	{
		ObjPool->Maps.ActiveTile(it->GetEntity()); //���Ϳ� ���� ��� �ִ� Ÿ�� �ߵ�
		if (!ObjPool->MonsterPool.CheckHealth())
			it++;
		
		if (ObjPool->MonsterPool.ePool.empty()) break;
	}

	if (ObjPool->Player.GetState() == STAND && ObjPool->Player.isWaitingTrapSet == true) //�̵��߿� Ʈ�� ������ ��������� �� ���� ĭ�� ���缭�� ������ġ
	{
		ObjPool->Player.SetState(TRAPSETTING); //�÷��̾� �������·� �����
		ObjPool->Player.isWaitingTrapSet = false;
	}

	if (ObjPool->Player.GetState() == STAND && ObjPool->Player.isWaitingSkillSet == true) //�̵��߿� Ʈ�� ������ ��������� �� ���� ĭ�� ���缭�� ������ġ
	{
		ObjPool->Player.SetState(SKILLPREPARING); //�÷��̾� �������·� �����
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

	if (exlastBitState == 0 && exkeyState & 0x0001) //UP //������ 0x1 �� 0 �̸� ����(�� �����ٰ� ������ ��)
	{
		ObjPool->MonsterPool.AddMonster(DEALER, 4, 4);
		exlastBitState = 1; // ������ �߿� ������� �ʵ��� ǥ��
	}
	if ((exkeyState & 0x8000) == 0) // ������ �ôٸ� ���� ������ ���ؼ� ���� �ʱ�ȭ
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

	if (lastBitState[UP] == 0 && keyState[UP] & 0x0001) //B_UP //������ 0x1 �� 0 �̸� ����(�� �����ٰ� ������ ��)
	{
		ObjPool->Player.SetDirection(UP);
		lastBitState[UP] = 1; // ������ �߿� ������� �ʵ��� ǥ��
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
		//���� �ִ°� �����̸� ����
		printf("�÷��̾� ����: %d", ObjPool->Player.GetState());
		if (ObjPool->Maps.CheckTrap(ObjPool->Player.GetDirection(), ObjPool->Player.GetPosition()) && ObjPool->Player.GetState() != TRAPSETTING && ObjPool->Player.GetState() != SKILLPREPARING && ObjPool->Player.GetState() != WALK)
		{
			ObjPool->Player.RepairTrap();
		}
		else if (ObjPool->Player.GetState() == STAND)
		{
			ObjPool->Player.DigMap();
		}
		else if (ObjPool->Player.GetState() == TRAPSETTING) //Ʈ�� �������̸� ��ġ
		{
			ObjPool->Player.SetTrap();
			ObjPool->Player.SetState(STAND);
		}
		else if (ObjPool->Player.GetState() == SKILLPREPARING)
		{
			ObjPool->Player.UseSkill();
			ObjPool->Player.SetState(STAND);
		}
		ObjPool->Player.SetSelectedArea(false); //���û��� ����

		lastBitState[SPACE] = 1;
	}

	//�÷��̾� �۵�
	if (lastBitState[KEY_1] == 0 && keyState[KEY_1] & 0x0001) //1��Ű
	{
		if (ObjPool->Player.GetState() == STAND && ObjPool->Player.Rock_Num >= 10) //�÷��̾ �� �ִ� ���¸�
		{
			ObjPool->Player.SetState(TRAPSETTING); //�÷��̾� �������·� �����
			ObjPool->Player.selectedTrap = TRAP_Niddle;
		}
		else if (ObjPool->Player.GetState() == WALK && ObjPool->Player.Rock_Num >= 10) //�̵��߿� ������ �� �ɾ������ ���
		{
			ObjPool->Player.selectedTrap = TRAP_Niddle;
			ObjPool->Player.isWaitingTrapSet = true;
		}
		else if (ObjPool->Player.GetState() == TRAPSETTING && ObjPool->Player.selectedTrap == TRAP_Niddle) //�������¿��� 1��Ű�� �� �� �� ������ ��������
		{
			ObjPool->Player.selectedTrap = NONE;
			ObjPool->Player.SetState(STAND);
		}

		lastBitState[KEY_1] = 1;
	}

	if (lastBitState[KEY_2] == 0 && keyState[KEY_2] & 0x0001) //2��Ű
	{
		if (ObjPool->Player.GetState() == STAND && ObjPool->Player.Rock_Num >= 15)
		{
			ObjPool->Player.SetState(TRAPSETTING);
			ObjPool->Player.selectedTrap = TRAP_ScareCrow;
		}

		else if (ObjPool->Player.GetState() == WALK && ObjPool->Player.Rock_Num >= 15) //�̵��߿� ������ �� �ɾ������ ���
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

	if (lastBitState[KEY_3] == 0 && keyState[KEY_3] & 0x0001) //3��Ű
	{
		if (ObjPool->Player.GetState() == STAND && ObjPool->Player.Rock_Num >= 20)
		{
			ObjPool->Player.SetState(TRAPSETTING);
			ObjPool->Player.selectedTrap = TRAP_Grab;
		}

		else if (ObjPool->Player.GetState() == WALK && ObjPool->Player.Rock_Num >= 20) //�̵��߿� ������ �� �ɾ������ ���
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

	if (lastBitState[KEY_4] == 0 && keyState[KEY_4] & 0x0001 && ObjPool->Player.Rock_Num >= 25) //4��Ű
	{
		if (ObjPool->Player.GetState() == STAND)
		{
			ObjPool->Player.SetState(TRAPSETTING);
			ObjPool->Player.selectedTrap = TRAP_Confusion;
		}

		else if (ObjPool->Player.GetState() == WALK && ObjPool->Player.Rock_Num >= 25) //�̵��߿� ������ �� �ɾ������ ���
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

	if (lastBitState[KEY_5] == 0 && keyState[KEY_5] & 0x0001) //5��Ű
	{
		if (ObjPool->Player.GetState() == STAND && ObjPool->Player.Rock_Num >= 30)
		{
			ObjPool->Player.SetState(TRAPSETTING);
			ObjPool->Player.selectedTrap = TRAP_Hole;
		}

		else if (ObjPool->Player.GetState() == WALK && ObjPool->Player.Rock_Num >= 30) //�̵��߿� ������ �� �ɾ������ ���
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

			else if (ObjPool->Player.GetState() == WALK) //�̵��߿� ������ �� �ɾ������ ���
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

			else if (ObjPool->Player.GetState() == WALK) //�̵��߿� ������ �� �ɾ������ ���
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
		if ((keyState[14] & 0x8000) == 0) // ������ �ôٸ� ���� ������ ���ؼ� ���� �ʱ�ȭ
		{
			lastBitState[i] = 0;
		}
	}
}