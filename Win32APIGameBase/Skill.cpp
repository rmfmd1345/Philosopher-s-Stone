#include "stdafx.h"
#include "Skill.h"

void Skill::InitSkill(HWND hWnd, int id)
{
	ID = id;

	switch (ID)
	{
	case ATK_SKILL:
		//Ani_Skill[UP].Init(hWnd, 0, 0, );
		//Ani_Skill[DOWN].Init(hWnd, 0, 0, );
		//Ani_Skill[LEFT].Init(hWnd, 0, 0, );
		//Ani_Skill[RIGHT].Init(hWnd, 0, 0, );
		break;
	case PUSH_SKILL:
		Ani_Skill[UP].Init(hWnd, 0, 0, 80, 80, 7, L"./Image/Skill/skilleffect_2_1.bmp");
		Ani_Skill[DOWN].Init(hWnd, 0, 0, 80, 80, 7, L"./Image/Skill/skilleffect_2_2.bmp");
		Ani_Skill[LEFT].Init(hWnd, 0, 0, 80, 80, 7, L"./Image/Skill/skilleffect_2_3.bmp");
		Ani_Skill[RIGHT].Init(hWnd, 0, 0, 80, 80, 7, L"./Image/Skill/skilleffect_2_4.bmp");
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
	POINT Ppoint = ObjPool->Player.GetPosition();

	switch (ID)
	{
	case ATK_SKILL:
		
		break;
	case AGGRO_SKILL:

		break;
	case PUSH_SKILL:
		switch (Direction)
		{
		case UP:

			break;
		case DOWN:

			break;
		case LEFT:

			break;
		case RIGHT:

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