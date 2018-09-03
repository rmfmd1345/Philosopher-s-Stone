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

	Ani_stand[UP].Init(hWnd, 0, 0, 62, 132, 1, L"./Image/Walk_Ani/Hero_Back.bmp");
	Ani_stand[DOWN].Init(hWnd, 0, 0, 62, 132, 1, L"./Image/Walk_Ani/Hero_Front.bmp");
	Ani_stand[LEFT].Init(hWnd, 0, 0, 58, 132, 1, L"./Image/Walk_Ani/Hero_Left.bmp");
	Ani_stand[RIGHT].Init(hWnd, 0, 0, 58, 132, 1, L"./Image/Walk_Ani/Hero_Right.bmp");

	Ani_walk[UP].Init(hWnd, 0, 0, 248, 132, 4, L"./Image/Walk_Ani/Hero_Back.bmp");
	Ani_walk[DOWN].Init(hWnd, 0, 0, 248, 132, 4, L"./Image/Walk_Ani/Hero_Front.bmp");
	Ani_walk[LEFT].Init(hWnd, 0, 0, 232, 132, 4, L"./Image/Walk_Ani/Hero_Left.bmp");
	Ani_walk[RIGHT].Init(hWnd, 0, 0, 232, 132, 4, L"./Image/Walk_Ani/Hero_Right.bmp");

	Ani_attack[UP].Init(hWnd, 0, 0, 240, 122, 4, L"./Image/Walk_Ani/Hero_Back.bmp");
	Ani_attack[DOWN].Init(hWnd, 0, 0, 216, 122, 4, L"./Image/Walk_Ani/Hero_Front.bmp");
	Ani_attack[LEFT].Init(hWnd, 0, 0, 304, 122, 4, L"./Image/Walk_Ani/Hero_Left.bmp");
	Ani_attack[RIGHT].Init(hWnd, 0, 0, 336, 122, 4, L"./Image/Walk_Ani/Hero_Right.bmp");
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

	switch (nowDirection)
	{
	case UP:
		Term_x = 5;
		break;
	case DOWN:
		Term_x = 15;
		break;
	case LEFT:
		Term_x = 12;
		break;
	case RIGHT:
		Term_x = 15;
		break;
	}
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
		Ani_stand[nowDirection].SetPosition(((pos.x - Map_x) - 1) * 80 + Term_x - 40, ((pos.y - Map_y) - 1) * 80 + Term_y);
		Ani_stand[nowDirection].Draw(hMemDC);
		break;
	case WALK:
		Ani_walk[nowDirection].SetPosition(((pos.x - Map_x) - 1) * 80 + Term_x - 40, ((pos.y - Map_y) - 1) * 80 + Term_y);
		Ani_walk[nowDirection].Draw(hMemDC);
		break;
	case ATTACK:
		Ani_attack[nowDirection].SetPosition(((pos.x - Map_x) - 1) * 80 + Term_x - 40, ((pos.y - Map_y) - 1) * 80 + Term_y);
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
		if (ObjPool->Maps.Map[pos.y][(pos.x - 1)].Tile_ID != MENTLE && ObjPool->Maps.Map[pos.y][(pos.x - 1)].Tile_ID == NONE) //멘틀이 아니고 파려는 곳이 NONE이면
			ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Floor, (pos.x - 1), pos.y); //floor 로 바닥 설정
		break;
	case RIGHT:
		if (ObjPool->Maps.Map[pos.y][(pos.x + 1)].Tile_ID != MENTLE && ObjPool->Maps.Map[pos.y][(pos.x + 1)].Tile_ID == NONE)
			ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Floor, (pos.x + 1), pos.y);
		break;
	case UP:
		if (ObjPool->Maps.Map[(pos.y - 1)][pos.x].Tile_ID != MENTLE && ObjPool->Maps.Map[pos.y - 1][(pos.x)].Tile_ID == NONE)
			ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Floor, pos.x, (pos.y - 1));
		break;
	case DOWN:
		if (ObjPool->Maps.Map[(pos.y + 1)][pos.x].Tile_ID != MENTLE && ObjPool->Maps.Map[pos.y + 1][(pos.x - 1)].Tile_ID == NONE)
			ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Floor, pos.x, (pos.y + 1));
		break;
	default:
		break;
	}
}

void Hero::SetTrap()
{
	switch (selectedTrap)
	{
	case NONE:
		break;
	case TRAP_Niddle:
		ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Trap_Niddle, pos.x, pos.y);
		break;
	case TRAP_Hole:
		ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Trap_Hole, pos.x, pos.y);
		break;
	case TRAP_ScareCrow:
		ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Trap_ScareCrow, pos.x, pos.y);
		break;
	case TRAP_Grap:
		ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Trap_Grap, pos.x, pos.y);
		break;
	default:
		break;
	}
	selectedTrap = NONE; //선택된 함정이 없도록 초기화
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
