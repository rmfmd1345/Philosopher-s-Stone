#include "stdafx.h"
#include "Skill.h"

void Skill::InitSkill(HWND hWnd, int id, int f)
{
	ID = id;

	for (int i = 0; i < 8; i++)
		Skill_Range[i] = { 0 , 0 };
	
	nowFrame = 0;
	maxFrame = f;

	nowDirection = 0;
	Check_Active = false;

	switch (ID)
	{
	case ATK_SKILL:
		Ani_Skill[UP].Init(hWnd, 0, 0, 2400, 240, f, L"./Image/Skill/skilleffect_1.bmp");
		break;
	case PUSH_SKILL:
		Ani_Skill[UP].Init(hWnd, 0, 0, 1280, 160, f, L"./Image/Skill/skilleffect_2_1.bmp");
		Ani_Skill[DOWN].Init(hWnd, 0, 0, 1280, 160, f, L"./Image/Skill/skilleffect_2_2.bmp");
		Ani_Skill[LEFT].Init(hWnd, 0, 0, 1280, 160, f, L"./Image/Skill/skilleffect_2_3.bmp");
		Ani_Skill[RIGHT].Init(hWnd, 0, 0, 1280, 160, f, L"./Image/Skill/skilleffect_2_4.bmp");
		break;
	case BARRICADE_SKILL:
		Ani_Skill[UP].Init(hWnd, 0, 0, 80, 80, f, L"./Image/Skill/skilleffect_3_1.bmp");
		Ani_Skill[LEFT].Init(hWnd, 0, 0, 80, 80, f , L"./Image/Skill/skilleffect_3_2.bmp");
		break;
	default:
		break;
	}
}

void Skill::ActiveSkill()
{
	POINT P_point = ObjPool->Player.GetPosition();
	POINT P_Temp = ObjPool->Player.GetPosition();
	int Direction = ObjPool->Player.GetDirection();

	if (P_Temp.x <= 8)
		P_Temp.x = 8;
	if (P_Temp.y <= 5)
		P_Temp.y = 5;
	if (P_Temp.x >= MAX_TILE_X - 9)
		P_Temp.x = 27;
	if (P_Temp.y >= MAX_TILE_Y - 4)
		P_Temp.y = 18;

	int Map_Start_x = P_Temp.x - 9;
	int Map_Start_y = P_Temp.y - 6;

	switch (ID)
	{
	case ATK_SKILL:
		Skill_Range[0].x = P_point.x - 1;
		Skill_Range[0].y = P_point.y - 1;

		Skill_Range[1].x = P_point.x;
		Skill_Range[1].y = P_point.y - 1;

		Skill_Range[2].x = P_point.x + 1;
		Skill_Range[2].y = P_point.y - 1;

		Skill_Range[3].x = P_point.x - 1;
		Skill_Range[3].y = P_point.y;

		Skill_Range[4].x = P_point.x + 1;
		Skill_Range[4].y = P_point.y;

		Skill_Range[5].x = P_point.x - 1;
		Skill_Range[5].y = P_point.y + 1;

		Skill_Range[6].x = P_point.x;
		Skill_Range[6].y = P_point.y + 1;

		Skill_Range[7].x = P_point.x + 1;
		Skill_Range[7].y = P_point.y + 1;

		Ani_Skill[UP].SetPosition(((P_point.x - Map_Start_x) - 2) * 80 - 40, ((P_point.y - Map_Start_y) - 2) * 80 - 40);

		for (auto it = ObjPool->MonsterPool.ePool.begin(); it != ObjPool->MonsterPool.ePool.end(); it++)
		{
			for (int i = 0; i < 8; i++)
			{
				if (Skill_Range[i].x == it->GetPosition().x && Skill_Range[i].y == it->GetPosition().y)
					it->AddHealth(-10);
			}
		}

		break;
	case AGGRO_SKILL:

		break;
	case PUSH_SKILL:
		switch (Direction)
		{
		case UP:
			Skill_Range[0].x = P_point.x;
			Skill_Range[0].y = P_point.y - 1;

			Ani_Skill[UP].SetPosition(((P_point.x - Map_Start_x) - 2) * 80, ((P_point.y - Map_Start_y) - 3) * 80 - 40);
			break;
		case DOWN:
			Skill_Range[0].x = P_point.x;
			Skill_Range[0].y = P_point.y + 1;

			Ani_Skill[DOWN].SetPosition(((P_point.x - Map_Start_x) - 2) * 80, ((P_point.y - Map_Start_y) - 1) * 80 - 40);
			break;
		case LEFT:
			Skill_Range[0].x = P_point.x - 1;
			Skill_Range[0].y = P_point.y;

			Ani_Skill[LEFT].SetPosition(((P_point.x - Map_Start_x) - 3) * 80 - 40, ((P_point.y - Map_Start_y) - 2) * 80 - 40);
			break;
		case RIGHT:
			Skill_Range[0].x = P_point.x + 1;
			Skill_Range[0].y = P_point.y;

			Ani_Skill[RIGHT].SetPosition(((P_point.x - Map_Start_x)) * 80 - 40, ((P_point.y - Map_Start_y) - 2) * 80 - 40);
			break;
		default:
			break;
		}
		break;
	case BARRICADE_SKILL:
		
		break;
	default:
		break;
	}
}

void Skill::Animation()
{
	int Direction = ObjPool->Player.GetDirection();

	if (Check_Active)
		Ani_Skill[Direction].NextFrameSprite();
}

void Skill::Draw(HDC hMemDC)
{
	int Direction = ObjPool->Player.GetDirection();
	
	switch (ID)
	{
	case ATK_SKILL:
		Ani_Skill[UP].Draw(hMemDC);

		if (Ani_Skill[Direction].GetCurrentFrame() >= Ani_Skill[Direction].GetLastFrame() - 1)
		{
			Check_Active = false;
			Ani_Skill[Direction].SetCurrentFrame(1);
		}
		break;
	case PUSH_SKILL:
		Ani_Skill[Direction].Draw(hMemDC);

		if (Ani_Skill[Direction].GetCurrentFrame() >= Ani_Skill[Direction].GetLastFrame() - 1)
		{
			Check_Active = false;
			Ani_Skill[Direction].SetCurrentFrame(1);
		}
		break;
	case BARRICADE_SKILL:
		Ani_Skill[Direction].Draw(hMemDC);

		if (Ani_Skill[Direction].GetCurrentFrame() >= Ani_Skill[Direction].GetLastFrame() - 1)
		{
			Check_Active = false;
			Ani_Skill[Direction].SetCurrentFrame(1);
		}
		break;
	default:
		break;
	}
}

void Skill::Terminate()
{
	for (int i = 0; i < 4; i++)
	{
		Ani_Skill[i].Ternimate();
	}
}