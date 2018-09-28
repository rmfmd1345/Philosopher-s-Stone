#include "stdafx.h"
#include "Sprite.h"
#include "HeroObj.h"

void Hero::Init(HWND hWnd, int x, int y, COLORREF sprite)
{
	this->type = type;
	this->pos = { x, y };

	nowState = STAND;
	stateFrame = 0;

	nowAnimation = STAND;
	nowDirection = DOWN;

	nowFrame = 0;
	maxFrame = 4;

	health = 100;
	Rock_Num = 0;

	Ani_stand[UP].Init(hWnd, 0, 0, 80, 132, 1, L"./Image/Walk_Ani/hero_walk_back.bmp");
	Ani_stand[DOWN].Init(hWnd, 0, 0, 80, 132, 1, L"./Image/Walk_Ani/hero_walk_front.bmp");
	Ani_stand[LEFT].Init(hWnd, 0, 0, 80, 132, 1, L"./Image/Walk_Ani/hero_walk_left.bmp");
	Ani_stand[RIGHT].Init(hWnd, 0, 0, 80, 132, 1, L"./Image/Walk_Ani/hero_walk_right.bmp");

	Ani_walk[UP].Init(hWnd, 0, 0, 480, 132, 6, L"./Image/Walk_Ani/hero_walk_back.bmp");
	Ani_walk[DOWN].Init(hWnd, 0, 0, 480, 132, 6, L"./Image/Walk_Ani/hero_walk_front.bmp");
	Ani_walk[LEFT].Init(hWnd, 0, 0, 480, 132, 6, L"./Image/Walk_Ani/hero_walk_left.bmp");
	Ani_walk[RIGHT].Init(hWnd, 0, 0, 480, 132, 6, L"./Image/Walk_Ani/hero_walk_right.bmp");

	/*Ani_attack[B_UP].Init(hWnd, 0, 0, 240, 122, 4, L"./Image/Walk_Ani/Hero_Back.bmp");
	Ani_attack[B_DOWN].Init(hWnd, 0, 0, 216, 122, 4, L"./Image/Walk_Ani/Hero_Front.bmp");
	Ani_attack[B_LEFT].Init(hWnd, 0, 0, 304, 122, 4, L"./Image/Walk_Ani/Hero_Left.bmp");
	Ani_attack[B_RIGHT].Init(hWnd, 0, 0, 336, 122, 4, L"./Image/Walk_Ani/Hero_Right.bmp");*/
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
			Term_y -= (stateFrame * 8);

	if (nowDirection == DOWN)
		if (!(5 <= pos.y && pos.y < 18))
			Term_y += (stateFrame * 8);

	if (nowDirection == LEFT)
		if (!(8 < pos.x && pos.x <= 27))
			Term_x -= (stateFrame * 8);

	if (nowDirection == RIGHT)
		if (!(8 <= pos.x && pos.x < 27))
			Term_x += (stateFrame * 8);

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
	if (nowState == WALK)
	{
		if (stateFrame < 10)
		{
			stateFrame++;
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
			stateFrame = 0;
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
		if (ObjPool->Maps.GetTileID(pos.x, pos.y - 1) == FLOOR)
		{
			nowState = WALK;
			nowAnimation = WALK;
			return;
		}
		break;
	case DOWN:
		if (ObjPool->Maps.GetTileID(pos.x, pos.y + 1) == FLOOR)
		{
			nowState = WALK;
			nowAnimation = WALK;
			return;
		}
		break;
	case LEFT:
		if (ObjPool->Maps.GetTileID(pos.x - 1, pos.y) == FLOOR)
		{
			nowState = WALK;
			nowAnimation = WALK;
			return;
		}
		break;
	case RIGHT:
		if (ObjPool->Maps.GetTileID(pos.x + 1, pos.y) == FLOOR)
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

int Hero::GetDiraction()
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
		return stateFrame;
	else
		return 0;
}

POINT Hero::GetWalkTerm()
{
	POINT Term = { 0, 0 };

	if(nowDirection == UP)
		if (5 < pos.y && pos.y <= 18)
			Term.y += (stateFrame * 8);

	if (nowDirection == DOWN)
		if (5 <= pos.y && pos.y < 18)
			Term.y -= (stateFrame * 8);

	if (nowDirection == LEFT)
		if (8 < pos.x && pos.x <= 27)
			Term.x += (stateFrame * 8);

	if (nowDirection == RIGHT)
		if (8 <= pos.x && pos.x < 27)
			Term.x -= (stateFrame * 8);

	return Term;
}

void Hero::PlusHealth(int plus)
{
	health += plus;
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
		if (ObjPool->Maps.Map[Temp_Y][Temp_X].Tile_ID == FLOOR && ObjPool->Player.Rock_Num >= 10)
		{
			ObjPool->Player.Rock_Num -= 10;
			ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Trap_Niddle, Temp_X, Temp_Y);
		}
		break;
	case TRAP_Hole:
		if (ObjPool->Maps.Map[Temp_Y][Temp_X].Tile_ID == FLOOR && ObjPool->Player.Rock_Num >= 30)
		{
			ObjPool->Player.Rock_Num -= 30;
			ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Trap_Hole, Temp_X, Temp_Y);
		}
		break;
	case TRAP_ScareCrow:
		if (ObjPool->Maps.Map[Temp_Y][Temp_X].Tile_ID == FLOOR && ObjPool->Player.Rock_Num >= 15)
		{
			ObjPool->Player.Rock_Num -= 15;
			ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Trap_ScareCrow, Temp_X, Temp_Y);
		}
		break;
	case TRAP_Grab:
		if (ObjPool->Maps.Map[Temp_Y][Temp_X].Tile_ID == FLOOR && ObjPool->Player.Rock_Num >= 20)
		{
			ObjPool->Player.Rock_Num -= 20;
			ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Trap_Grab, Temp_X, Temp_Y);
		}
		break;
	case TRAP_Cunfusion:
		if (ObjPool->Maps.Map[Temp_Y][Temp_X].Tile_ID == FLOOR && ObjPool->Player.Rock_Num >= 25)
		{
			ObjPool->Player.Rock_Num -= 25;
			ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Trap_Cunfusion, Temp_X, Temp_Y);
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
	switch (nowDirection)
	{
	case LEFT:
		ObjPool->Maps.Map[pos.y][pos.x - 1].Tile_On = true;
			
		break;
	case RIGHT:
		ObjPool->Maps.Map[pos.y][pos.x + 1].Tile_On = true;
		break;
	case UP:
		ObjPool->Maps.Map[pos.y - 1][pos.x].Tile_On = true;
		break;
	case DOWN:
		ObjPool->Maps.Map[pos.y + 1][pos.x].Tile_On = true;
		break;
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
