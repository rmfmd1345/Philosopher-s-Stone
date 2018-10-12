#include "stdafx.h"
#include "Sprite.h"
#include "HeroObj.h"

void Hero::Init(HWND hWnd, int x, int y, COLORREF sprite)
{
	this->type = type;
	this->pos = { x, y };

	nowState = STAND;
	stateFrame_Hero = 0;

	nowAnimation = STAND;
	nowDirection = DOWN;

	nowFrame = 0;
	maxFrame = 4;

	health = 100;
	Rock_Num = 99999;

	Ani_stand[UP].Init(hWnd, 0, 0, 80, 132, 1, L"./Image/Walk_Ani/hero_walk_back.bmp");
	Ani_stand[DOWN].Init(hWnd, 0, 0, 80, 132, 1, L"./Image/Walk_Ani/hero_walk_front.bmp");
	Ani_stand[LEFT].Init(hWnd, 0, 0, 80, 132, 1, L"./Image/Walk_Ani/hero_walk_left.bmp");
	Ani_stand[RIGHT].Init(hWnd, 0, 0, 80, 132, 1, L"./Image/Walk_Ani/hero_walk_right.bmp");

	Ani_walk[UP].Init(hWnd, 0, 0, 480, 132, 6, L"./Image/Walk_Ani/hero_walk_back.bmp");
	Ani_walk[DOWN].Init(hWnd, 0, 0, 480, 132, 6, L"./Image/Walk_Ani/hero_walk_front.bmp");
	Ani_walk[LEFT].Init(hWnd, 0, 0, 480, 132, 6, L"./Image/Walk_Ani/hero_walk_left.bmp");
	Ani_walk[RIGHT].Init(hWnd, 0, 0, 480, 132, 6, L"./Image/Walk_Ani/hero_walk_right.bmp");

	Ani_attack[UP].Init(hWnd, 0, 0, 240, 122, 4, L"./Image/Attack_Ani/hero_attack_back.bmp");
	Ani_attack[DOWN].Init(hWnd, 0, 0, 216, 122, 4, L"./Image/Attack_Ani/hero_attack_front.bmp");
	Ani_attack[LEFT].Init(hWnd, 0, 0, 304, 122, 4, L"./Image/Attack_Ani/Hero_Attack_Left.bmp");
	Ani_attack[RIGHT].Init(hWnd, 0, 0, 336, 122, 4, L"./Image/Attack_Ani/hero_attack_right.bmp");

	ATK_Skill.InitSkill(hWnd, ATK_SKILL, 10);
	PUSH_Skill.InitSkill(hWnd, PUSH_SKILL, 8);
	BARRICADE_Skill.InitSkill(hWnd, BARRICADE_SKILL, 12);
}

void Hero::Ternimate()
{
	for (int i = 0; i < 4; i++)
	{
		Ani_stand[i].Ternimate();
		Ani_walk[i].Ternimate();
		Ani_attack[i].Ternimate();
	}
}

void Hero::Draw(HDC hMemDC, int x, int y)
{
	if (x <= 8)
		x = 8;
	if (y <= 5)
		y = 5;
	if (x >= MAX_TILE_X - 9)
		x = 27;
	if (y >= MAX_TILE_Y - 4)
		y = 18;

	int Map_x = x - 9;
	int Map_y = y - 6;

	int Term_x = 0;
	int Term_y = 0;

	/*switch (nowDirection)
	{
	case B_UP:
		Term_x = 5;
		break;
	case B_DOWN:
		Term_x = 15;
		break;
	case B_LEFT:
		Term_x = 12;
		break;
	case B_RIGHT:
		Term_x = 15;
		break;
	}*/
	Term_y = -65;

	if (nowDirection == UP)
		if (!(5 < pos.y && pos.y <= 18))
			Term_y -= (stateFrame_Hero * 8);

	if (nowDirection == DOWN)
		if (!(5 <= pos.y && pos.y < 18))
			Term_y += (stateFrame_Hero * 8);

	if (nowDirection == LEFT)
		if (!(8 < pos.x && pos.x <= 27))
			Term_x -= (stateFrame_Hero * 8);

	if (nowDirection == RIGHT)
		if (!(8 <= pos.x && pos.x < 27))
			Term_x += (stateFrame_Hero * 8);

	switch (nowAnimation)
	{
	case STAND:
		Ani_stand[nowDirection].SetPosition(((pos.x - Map_x) - 1) * 80 + Term_x - 40, ((pos.y - Map_y) - 1) * 80 + Term_y - 40);
		Ani_stand[nowDirection].Draw(hMemDC);
		break;
	case WALK:
		Ani_walk[nowDirection].SetPosition(((pos.x - Map_x) - 1) * 80 + Term_x - 40, ((pos.y - Map_y) - 1) * 80 + Term_y - 40);
		Ani_walk[nowDirection].Draw(hMemDC);
		break;
	case ATTACK:
		Ani_attack[nowDirection].SetPosition(((pos.x - Map_x) - 1) * 80 + Term_x - 40, ((pos.y - Map_y) - 1) * 80 + Term_y - 40);
		Ani_attack[nowDirection].Draw(hMemDC);
		break;
	}
}

void Hero::Animation()
{
	switch (nowAnimation)
	{
	case STAND:
		Ani_stand[nowDirection].NextFrameSprite();
		break;
	case WALK:
		Ani_walk[nowDirection].NextFrameSprite();
		break;
	case ATTACK:
		Ani_attack[nowDirection].NextFrameSprite();
		break;
	}
}

void Hero::UpdateState()
{
	if (nowState == TRAPSETTING)
		SetSelectedArea(true);
	else
		SetSelectedArea(false);

	if (nowState == WALK)
	{
		if (stateFrame_Hero < 10)
		{
			stateFrame_Hero++;
		}
		else
		{
			nowAnimation = STAND;
			switch (nowDirection)
			{
			case UP:
				pos.y--;
				break;
			case DOWN:
				pos.y++;
				break;
			case LEFT:
				pos.x--;
				break;
			case RIGHT:
				pos.x++;
				break;
			}
			nowState = STAND;
			stateFrame_Hero = 0;
		}
		return;
	}
	return;
}

void Hero::SetPosition(int x, int y)
{
	this->pos.x = x;
	this->pos.y = y;
}

void Hero::SetAnimation(int ani)
{
	nowAnimation = ani;
}

void Hero::SetDirection(int dire)
{
	if (nowState != WALK)
		nowDirection = dire;

	if (nowState == TRAPSETTING) //플레이어가 고정된 상태로 트랩 설치중이면
	{
		nowDirection = dire; //그 자리에서 방향만 바꾸기
		return;
	}

	switch (nowDirection)
	{
	case UP:
		if (ObjPool->Maps.GetTileMoveID(pos.x, pos.y - 1) && ObjPool->Maps.Map[pos.y - 1][pos.x].Tile_On)
		{
			nowState = WALK;
			nowAnimation = WALK;
			return;
		}
		break;
	case DOWN:
		if (ObjPool->Maps.GetTileMoveID(pos.x, pos.y + 1) && ObjPool->Maps.Map[pos.y + 1][pos.x].Tile_On)
		{
			nowState = WALK;
			nowAnimation = WALK;
			return;
		}
		break;
	case LEFT:
		if (ObjPool->Maps.GetTileMoveID(pos.x - 1, pos.y) && ObjPool->Maps.Map[pos.y][pos.x - 1].Tile_On)
		{
			nowState = WALK;
			nowAnimation = WALK;
			return;
		}
		break;
	case RIGHT:
		if (ObjPool->Maps.GetTileMoveID(pos.x + 1, pos.y) && ObjPool->Maps.Map[pos.y][pos.x + 1].Tile_On)
		{
			nowState = WALK;
			nowAnimation = WALK;
			return;
		}
		break;
	}
}

void Hero::SetState(int state)
{
	nowState = state;
}

int Hero::GetState()
{
	return nowState;
}

int Hero::GetDirection()
{
	return nowDirection;
}

POINT Hero::GetPosition()
{
	return pos;
}

int Hero::GetWalkState()
{
	if (nowState == WALK)
		return stateFrame_Hero;
	else
		return 0;
}

POINT Hero::GetWalkTerm()
{
	POINT Term = { 0, 0 };

	if(nowDirection == UP)
		if (5 < pos.y && pos.y <= 18)
			Term.y += (stateFrame_Hero * 8);

	if (nowDirection == DOWN)
		if (5 <= pos.y && pos.y < 18)
			Term.y -= (stateFrame_Hero * 8);

	if (nowDirection == LEFT)
		if (8 < pos.x && pos.x <= 27)
			Term.x += (stateFrame_Hero * 8);

	if (nowDirection == RIGHT)
		if (8 <= pos.x && pos.x < 27)
			Term.x -= (stateFrame_Hero * 8);

	return Term;
}

void Hero::AddHealth(int a)
{
	health += a;
}

void Hero::DigMap()
{
	switch (nowDirection)
	{
	case LEFT:
		if (ObjPool->Maps.Map[pos.y][(pos.x - 1)].Tile_ID != MENTLE && (ObjPool->Maps.Map[pos.y][(pos.x - 1)].Tile_ID == NONE || ObjPool->Maps.Map[pos.y][(pos.x - 1)].Tile_ID == WALL)) //멘틀이 아니고 파려는 곳이 NONE이면
		{
			ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Floor, (pos.x - 1), pos.y); //floor 로 바닥 설정
			Rock_Num += 5;
		}
		break;
	case RIGHT:
		if (ObjPool->Maps.Map[pos.y][(pos.x + 1)].Tile_ID != MENTLE && (ObjPool->Maps.Map[pos.y][(pos.x + 1)].Tile_ID == NONE || ObjPool->Maps.Map[pos.y][(pos.x + 1)].Tile_ID == WALL))
		{
			ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Floor, (pos.x + 1), pos.y);
			Rock_Num += 5;
		}
		break;
	case UP:
		if (ObjPool->Maps.Map[(pos.y - 1)][pos.x].Tile_ID != MENTLE && (ObjPool->Maps.Map[pos.y - 1][(pos.x)].Tile_ID == NONE || ObjPool->Maps.Map[pos.y - 1][(pos.x)].Tile_ID == WALL))
		{
			ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Floor, pos.x, (pos.y - 1));
			Rock_Num += 5;
		}
		break;
	case DOWN:
		if (ObjPool->Maps.Map[(pos.y + 1)][pos.x].Tile_ID != MENTLE && (ObjPool->Maps.Map[pos.y + 1][(pos.x)].Tile_ID == NONE || ObjPool->Maps.Map[pos.y + 1][(pos.x)].Tile_ID == WALL))
		{
			ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Floor, pos.x, (pos.y + 1));
			Rock_Num += 5;
		}
		break;
	default:
		break;
	}
	wsprintf(Rock_Num_UI, L"%05d", Rock_Num);
}

void Hero::SetSelectedArea(bool isCreate)
{
	if (isCreate)
	{
		if (ObjPool->Maps.isCanTrapSet(pos.x, pos.y + 1))
			ObjPool->Maps.Map[pos.y + 1][pos.x].Tile_SelectArea = true;
		if (ObjPool->Maps.isCanTrapSet(pos.x, pos.y - 1))
			ObjPool->Maps.Map[pos.y - 1][pos.x].Tile_SelectArea = true;
		if (ObjPool->Maps.isCanTrapSet(pos.x + 1, pos.y))
			ObjPool->Maps.Map[pos.y][pos.x + 1].Tile_SelectArea = true;
		if (ObjPool->Maps.isCanTrapSet(pos.x - 1, pos.y))
			ObjPool->Maps.Map[pos.y][pos.x - 1].Tile_SelectArea = true;
		//플레이어 주변영역을 선택된 영역으로 마크한다
	}
	else if (!isCreate)
	{
		ObjPool->Maps.Map[pos.y + 1][pos.x].Tile_SelectArea = false;
		ObjPool->Maps.Map[pos.y - 1][pos.x].Tile_SelectArea = false;
		ObjPool->Maps.Map[pos.y][pos.x + 1].Tile_SelectArea = false;
		ObjPool->Maps.Map[pos.y][pos.x - 1].Tile_SelectArea = false;
		//플레이어 주변영역을 지운다.
	}
}

void Hero::SetTrap()
{
	if (ObjPool->Maps.Map[pos.y][pos.x].Tile_ID != FLOOR)
		return;

	int Temp_X = pos.x;
	int Temp_Y = pos.y;

	switch (nowDirection)
	{
	case LEFT: Temp_X = pos.x - 1;
		break;
	case RIGHT: Temp_X = pos.x +  1;
		break;
	case UP: Temp_Y = pos.y - 1;
		break;
	case DOWN: Temp_Y = pos.y + 1;
		break;
	}


	switch (selectedTrap)
	{
	case NONE:
		break;
	case TRAP_Niddle:
		if (ObjPool->Player.Rock_Num >= 10)
		{
			ObjPool->Player.Rock_Num -= 10;
			ObjPool->Maps.SetTrapOnMap(ObjPool->Maps.Trap_Niddle, Temp_X, Temp_Y);
		}
		break;
	case TRAP_Hole:
		if (ObjPool->Player.Rock_Num >= 30)
		{
			ObjPool->Player.Rock_Num -= 30;
			ObjPool->Maps.SetTrapOnMap(ObjPool->Maps.Trap_Hole, Temp_X, Temp_Y);
		}
		break;
	case TRAP_ScareCrow:
		if (ObjPool->Player.Rock_Num >= 15)
		{
			ObjPool->Player.Rock_Num -= 15;
			ObjPool->Maps.SetTrapOnMap(ObjPool->Maps.Trap_ScareCrow, Temp_X, Temp_Y);
		}
		break;
	case TRAP_Grab:
		if (ObjPool->Player.Rock_Num >= 20)
		{
			ObjPool->Player.Rock_Num -= 20; 

			if (ObjPool->Maps.isCanTrapSet(Temp_X, Temp_Y))
			{
				ObjPool->Maps.SetTrapOnMap(ObjPool->Maps.Trap_Grab, Temp_X, Temp_Y);
				ObjPool->Maps.SetTrapOnMap(ObjPool->Maps.Trap_GrabArea, Temp_X + 1, Temp_Y); //갈고리함정 영역 설정
				ObjPool->Maps.SetTrapOnMap(ObjPool->Maps.Trap_GrabArea, Temp_X - 1, Temp_Y);
				ObjPool->Maps.SetTrapOnMap(ObjPool->Maps.Trap_GrabArea, Temp_X, Temp_Y + 1);
				ObjPool->Maps.SetTrapOnMap(ObjPool->Maps.Trap_GrabArea, Temp_X, Temp_Y - 1);
			}

			POINT grabPos;
			grabPos.x = Temp_X;
			grabPos.y = Temp_Y;
			ObjPool->Maps.Map[Temp_Y + 1][Temp_X].Grab_POS = grabPos; //끌려갈 영역의 좌표 저장
			ObjPool->Maps.Map[Temp_Y - 1][Temp_X].Grab_POS = grabPos;
			ObjPool->Maps.Map[Temp_Y][Temp_X + 1].Grab_POS = grabPos;
			ObjPool->Maps.Map[Temp_Y][Temp_X - 1].Grab_POS = grabPos;

		}
		break;
	case TRAP_Cunfusion:
		if (ObjPool->Player.Rock_Num >= 25)
		{
			ObjPool->Player.Rock_Num -= 25;
			ObjPool->Maps.SetTrapOnMap(ObjPool->Maps.Trap_Cunfusion, Temp_X, Temp_Y);
		}
		break;
	default:
		break;
	}
	Temp_X = 0;
	Temp_Y = 0;
	selectedTrap = NONE; //선택된 함정이 없도록 초기화
}

void Hero::RepairTrap()
{
	ObjPool->Player.SetState(TRAPREPAIRING);
	switch (nowDirection)
	{
	case LEFT:
		if (ObjPool->Maps.Map[pos.y][pos.x - 1].Tile_On == false)
			ObjPool->Maps.Map[pos.y][pos.x - 1].repairGage++;
		if (ObjPool->Maps.Map[pos.y][pos.x - 1].repairGage >= ObjPool->Maps.Map[pos.y][pos.x - 1].TrapHp)
		{
			ObjPool->Maps.Map[pos.y][pos.x - 1].Tile_On = true;
			ObjPool->Maps.Map[pos.y][pos.x - 1].repairGage = 0;
		}
		break;
	case RIGHT:
		if (ObjPool->Maps.Map[pos.y][pos.x + 1].Tile_On == false)
			ObjPool->Maps.Map[pos.y][pos.x + 1].repairGage++;
		if (ObjPool->Maps.Map[pos.y][pos.x + 1].repairGage >= ObjPool->Maps.Map[pos.y][pos.x + 1].TrapHp)
		{
			ObjPool->Maps.Map[pos.y][pos.x + 1].Tile_On = true;
			ObjPool->Maps.Map[pos.y][pos.x + 1].repairGage = 0;
		}
		break;
	case UP:
		if (ObjPool->Maps.Map[pos.y - 1][pos.x].Tile_On == false)
			ObjPool->Maps.Map[pos.y - 1][pos.x].repairGage++;
		if (ObjPool->Maps.Map[pos.y - 1][pos.x].repairGage >= ObjPool->Maps.Map[pos.y - 1][pos.x].TrapHp)
		{
			ObjPool->Maps.Map[pos.y - 1][pos.x].Tile_On = true;
			ObjPool->Maps.Map[pos.y - 1][pos.x].repairGage = 0;
		}
		break;
	case DOWN:
		if (ObjPool->Maps.Map[pos.y + 1][pos.x].Tile_On == false)
			ObjPool->Maps.Map[pos.y + 1][pos.x].repairGage++;
		if (ObjPool->Maps.Map[pos.y + 1][pos.x].repairGage >= ObjPool->Maps.Map[pos.y + 1][pos.x].TrapHp)
		{
			ObjPool->Maps.Map[pos.y + 1][pos.x].Tile_On = true;
			ObjPool->Maps.Map[pos.y + 1][pos.x].repairGage = 0;
		}
	}
}

void Hero::DrawSelectedTrapUI(HDC hMemDC)
{
	if (selectedTrap != NONE)
	{
		switch (selectedTrap)
		{
		case TRAP_Niddle:
			ObjPool->ingameUI_SelectedTrap.SetPosition(300, 540);
			break;
		case TRAP_ScareCrow:
			ObjPool->ingameUI_SelectedTrap.SetPosition(410, 540);
			break;
		case TRAP_Grab:
			ObjPool->ingameUI_SelectedTrap.SetPosition(520, 540);
			break;
		case TRAP_Cunfusion:
			ObjPool->ingameUI_SelectedTrap.SetPosition(630, 540);
			break;
		case TRAP_Hole:
			ObjPool->ingameUI_SelectedTrap.SetPosition(740, 540);
			break;
		}
		ObjPool->ingameUI_SelectedTrap.Draw(hMemDC);
		stateFrame_TrapSelect++;
		if (stateFrame_TrapSelect >= 10)
		{
			ObjPool->ingameUI_SelectedTrap.NextFrameSprite_Trap();
			stateFrame_TrapSelect = 0;
		}
	}
		
}

bool Hero::isDead()
{
	return !(health);
}

bool Hero::isWalk()
{
	if (nowAnimation != WALK) return false;
	if (nowFrame == (maxFrame * 4)) return false;

	return true;
}
