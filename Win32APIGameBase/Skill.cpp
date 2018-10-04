#include "stdafx.h"
#include "Skill.h"

void Skill::InitSkill(HWND hWnd, int id, int f, int r)
{
	ID = id;

	for (int i = 0; i < 8; i++)
		Skill_Range[i] = { 0 , 0 };
	
	nowFrame = 0;
	maxFrame = f;
	maxRange = r;

	nowDirection = 0;
	Check_Active = false;

	switch (ID)
	{
	case ATK_SKILL:
		//Ani_Skill[UP].Init(hWnd, 0, 0, );
		//Ani_Skill[DOWN].Init(hWnd, 0, 0, );
		//Ani_Skill[LEFT].Init(hWnd, 0, 0, );
		//Ani_Skill[RIGHT].Init(hWnd, 0, 0, );
		break;
	case PUSH_SKILL:
		//Ani_Skill[UP].Init(hWnd, 0, 0, 80, 80, f, L"./Image/Skill/skilleffect_2_1.bmp");
		Ani_Skill[DOWN].Init(hWnd, 0, 0, 80, 80, f, L"./Image/Skill/skilleffect_2_2.bmp");
		Ani_Skill[LEFT].Init(hWnd, 0, 0, 80, 80, f, L"./Image/Skill/skilleffect_2_3.bmp");
		Ani_Skill[RIGHT].Init(hWnd, 0, 0, 80, 80, f, L"./Image/Skill/skilleffect_2_4.bmp");
		break;
	case BARRICADE_SKILL:
		//Ani_Skill[UP].Init(hWnd, 0, 0, );
		//Ani_Skill[DOWN].Init(hWnd, 0, 0, );
		//Ani_Skill[LEFT].Init(hWnd, 0, 0, );
		//Ani_Skill[RIGHT].Init(hWnd, 0, 0, );
		break;
	default:
		break;
	}
}

void Skill::ActiveSkill(int Direction)
{
	POINT P_point = ObjPool->Player.GetPosition();

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
		break;
	case AGGRO_SKILL:

		break;
	case PUSH_SKILL:
		switch (Direction)
		{
		case UP:
			Skill_Range[0].x = P_point.x;
			Skill_Range[0].y = P_point.y - 1;
			break;
		case DOWN:
			Skill_Range[0].x = P_point.x;
			Skill_Range[0].y = P_point.y + 1;
			break;
		case LEFT:
			Skill_Range[0].x = P_point.x - 1;
			Skill_Range[0].y = P_point.y;
			break;
		case RIGHT:
			Skill_Range[0].x = P_point.x + 1;
			Skill_Range[0].y = P_point.y;
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

void Skill::Terminate()
{
	for (int i = 0; i < 4; i++)
	{
		Ani_Skill[i].Ternimate();
	}
}