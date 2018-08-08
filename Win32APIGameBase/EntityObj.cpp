#include "stdafx.h"
#include "Sprite.h"
#include "EntityObj.h"

void Entity::Init(HWND hWnd, int x, int y, int type, COLORREF sprite)
{
	this->type = type;
	this->pos = { x, y };

	nowAnimation = STAND;
	nowDirection = DOWN;

	nowFrame = 0;
	maxFrame = 4;

	health = 100;

	switch (type)
	{
	case DEALER:
		Ani_stand[UP].Init(hWnd, 0, 0, 240, 122, 4, L"./Image/Walk_Ani/Dealer_Back.bmp");
		Ani_stand[DOWN].Init(hWnd, 0, 0, 216, 122, 4, L"./Image/Walk_Ani/Dealer_Front.bmp");
		Ani_stand[LEFT].Init(hWnd, 0, 0, 304, 122, 4, L"./Image/Walk_Ani/Dealer_Left.bmp");
		Ani_stand[RIGHT].Init(hWnd, 0, 0, 336, 122, 4, L"./Image/Walk_Ani/Dealer_Right.bmp");

		Ani_walk[UP].Init(hWnd, 0, 0, 240, 122, 4, L"./Image/Walk_Ani/Dealer_Back.bmp");
		Ani_walk[DOWN].Init(hWnd, 0, 0, 216, 122, 4, L"./Image/Walk_Ani/Dealer_Front.bmp");
		Ani_walk[LEFT].Init(hWnd, 0, 0, 304, 122, 4, L"./Image/Walk_Ani/Dealer_Left.bmp");
		Ani_walk[RIGHT].Init(hWnd, 0, 0, 336, 122, 4, L"./Image/Walk_Ani/Dealer_Right.bmp");
		
		Ani_attack[UP].Init(hWnd, 0, 0, 240, 122, 4, L"./Image/Walk_Ani/Dealer_Back.bmp");
		Ani_attack[DOWN].Init(hWnd, 0, 0, 216, 122, 4, L"./Image/Walk_Ani/Dealer_Front.bmp");
		Ani_attack[LEFT].Init(hWnd, 0, 0, 304, 122, 4, L"./Image/Walk_Ani/Dealer_Left.bmp");
		Ani_attack[RIGHT].Init(hWnd, 0, 0, 336, 122, 4, L"./Image/Walk_Ani/Dealer_Right.bmp");
		break;
	case WIZARD:
		Ani_stand[UP].Init(hWnd, 0, 0, 280, 102, 4, L"./Image/Walk_Ani/Wizard_Back.bmp");
		Ani_stand[DOWN].Init(hWnd, 0, 0, 264, 102, 4, L"./Image/Walk_Ani/Wizard_Front.bmp");
		Ani_stand[LEFT].Init(hWnd, 0, 0, 296, 102, 4, L"./Image/Walk_Ani/Wizard_Left.bmp");
		Ani_stand[RIGHT].Init(hWnd, 0, 0, 256, 102, 4, L"./Image/Walk_Ani/Wizard_Right.bmp");

		Ani_walk[UP].Init(hWnd, 0, 0, 280, 102, 4, L"./Image/Walk_Ani/Wizard_Back.bmp");
		Ani_walk[DOWN].Init(hWnd, 0, 0, 264, 102, 4, L"./Image/Walk_Ani/Wizard_Front.bmp");
		Ani_walk[LEFT].Init(hWnd, 0, 0, 296, 102, 4, L"./Image/Walk_Ani/Wizard_Left.bmp");
		Ani_walk[RIGHT].Init(hWnd, 0, 0, 256, 102, 4, L"./Image/Walk_Ani/Wizard_Right.bmp");

		Ani_attack[UP].Init(hWnd, 0, 0, 280, 102, 4, L"./Image/Walk_Ani/Wizard_Back.bmp");
		Ani_attack[DOWN].Init(hWnd, 0, 0, 264, 102, 4, L"./Image/Walk_Ani/Wizard_Front.bmp");
		Ani_attack[LEFT].Init(hWnd, 0, 0, 296, 102, 4, L"./Image/Walk_Ani/Wizard_Left.bmp");
		Ani_attack[RIGHT].Init(hWnd, 0, 0, 256, 102, 4, L"./Image/Walk_Ani/Wizard_Right.bmp");
		break;
	case TANKER:
		Ani_stand[UP].Init(hWnd, 0, 0, 424, 138, 4, L"./Image/Walk_Ani/Tanker_Back.bmp");
		Ani_stand[DOWN].Init(hWnd, 0, 0, 352, 138, 4, L"./Image/Walk_Ani/Tanker_Front.bmp");
		Ani_stand[LEFT].Init(hWnd, 0, 0, 280, 138, 4, L"./Image/Walk_Ani/Tanker_Left.bmp");
		Ani_stand[RIGHT].Init(hWnd, 0, 0, 248, 138, 4, L"./Image/Walk_Ani/Tanker_Right.bmp");

		Ani_walk[UP].Init(hWnd, 0, 0, 424, 138, 4, L"./Image/Walk_Ani/Tanker_Back.bmp");
		Ani_walk[DOWN].Init(hWnd, 0, 0, 352, 138, 4, L"./Image/Walk_Ani/Tanker_Front.bmp");
		Ani_walk[LEFT].Init(hWnd, 0, 0, 280, 138, 4, L"./Image/Walk_Ani/Tanker_Left.bmp");
		Ani_walk[RIGHT].Init(hWnd, 0, 0, 248, 138, 4, L"./Image/Walk_Ani/Tanker_Right.bmp");

		Ani_attack[UP].Init(hWnd, 0, 0, 424, 138, 4, L"./Image/Walk_Ani/Tanker_Back.bmp");
		Ani_attack[DOWN].Init(hWnd, 0, 0, 352, 138, 4, L"./Image/Walk_Ani/Tanker_Front.bmp");
		Ani_attack[LEFT].Init(hWnd, 0, 0, 280, 138, 4, L"./Image/Walk_Ani/Tanker_Left.bmp");
		Ani_attack[RIGHT].Init(hWnd, 0, 0, 248, 138, 4, L"./Image/Walk_Ani/Tanker_Right.bmp");
		break;
	}

}
void Entity::Ternimate()
{
	for (int i = 0; i < 4; i++)
	{
		Ani_stand[i].Ternimate();
		Ani_walk[i].Ternimate();
		Ani_attack[i].Ternimate();
	}
}

void Entity::Draw(HDC hMemDC, int x, int y)
{
	if (x <= 9)
		x = 9;
	if (y <= 5)
		y = 5;
	if (x >= 23)
		x = 23;
	if (y >= 11)
		y = 11;

	int Map_x = x - 9;
	int Map_y = y - 5;

	int Term_x = 0;
	int Term_y = 0;

	switch (type)
	{
	case DEALER:
		switch (nowDirection)
		{
		case UP:
			Term_x = 5;
			break;
		case DOWN:
			Term_x = 15;
			break;
		case LEFT:
			Term_x = -12;
			break;
		case RIGHT:
			Term_x = 15;
			break;
		}
		Term_y = -55;
		break;
	case WIZARD:
		switch (nowDirection)
		{
		case UP:
			Term_x = 5;
			break;
		case DOWN:
			Term_x = 5;
			break;
		case LEFT:
			Term_x = 3;
			break;
		case RIGHT:
			Term_x = 3;
			break;
		}
		Term_y = -45;
		break;
	case TANKER:
		switch (nowDirection)
		{
		case UP:
			Term_x = -13;
			break;
		case DOWN:
			Term_x = -3;
			break;
		case LEFT:
			Term_x = -8;
			break;
		case RIGHT:
			Term_x = 15;
			break;
		}
		Term_y = -65;
		break;
	}

	switch (nowAnimation)
	{
	case STAND:
		Ani_stand[nowDirection].SetPosition((pos.x - Map_x) * 80 + Term_x, (pos.y - Map_y ) * 80 + Term_y);
		Ani_stand[nowDirection].Draw(hMemDC);						 
		break;														 
	case WALK:														 
		Ani_walk[nowDirection].SetPosition((pos.x - Map_x) * 80 + Term_x, (pos.y - Map_y) * 80 + Term_y);
		Ani_walk[nowDirection].Draw(hMemDC);						 
		break;														 
	case ATTACK:													 
		Ani_attack[nowDirection].SetPosition((pos.x - Map_x) * 80 + Term_x, (pos.y - Map_y) * 80 + Term_y);
		Ani_attack[nowDirection].Draw(hMemDC);
		break;
	}
}

void Entity::Animaition()
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

void Entity::SetPosition(int x, int y)
{
	this->pos.x = x;
	this->pos.y = y;
}
void Entity::SetAnimation(int ani)
{
	nowAnimation = ani;
}
void Entity::SetDirection(int dire)
{
	nowDirection = dire;
}

void Entity::PlusHealth(int plus)
{
	health += plus;
}

bool Entity::isDead()
{
	return !(health);
}

bool Entity::isWalk()
{
	if (nowAnimation != WALK) return false;
	if (nowFrame == (maxFrame * 4)) return false;

	return true;
}

void Monster::Init(HWND hWnd)
{
	Dealer.Init(hWnd, 0, 0, DEALER);
	Wizard.Init(hWnd, 0, 0, WIZARD);
	Tanker.Init(hWnd, 0, 0, TANKER);

	AddMonster(hWnd, DEALER, 5, 5);
	AddMonster(hWnd, WIZARD, 7, 5);
	AddMonster(hWnd, TANKER, 9, 5);
}

void Monster::Ternimate()
{
	Dealer.Ternimate();
	Wizard.Ternimate();
	Tanker.Ternimate();

	if (pool.empty()) return;

	for (auto it = pool.begin(); it != pool.end(); it++)
	{
		it->Ternimate();
	}

	pool.clear();
}

void Monster::Draw(HDC hMemDC, int x, int y)
{
	if (pool.empty()) return;

	for (auto it = pool.begin(); it != pool.end(); it++)
	{
		it->Draw(hMemDC, x, y);
	}
}
void Monster::Animation()
{
	if (pool.empty()) return;

	for (auto it = pool.begin(); it != pool.end(); it++)
	{
		it->Animaition();
	}
}

void Monster::AddMonster(HWND hWnd, int type, int x, int y)
{
	switch (type)
	{
	case DEALER:
		Dealer.SetPosition(x, y);
		pool.push_back(Dealer);
		break;
	case WIZARD:
		Wizard.SetPosition(x, y);
		pool.push_back(Wizard);
		break;
	case TANKER:
		Tanker.SetPosition(x, y);
		pool.push_back(Tanker);
		break;
	}
}

void Monster::AddMonster(HWND hWnd, int type)
{
	AddMonster(hWnd, type, spawnPosition.x, spawnPosition.y);
}

void Monster::CheckHealth()
{
	if (pool.empty()) return;

	for (auto it = pool.begin(); it != pool.end(); it++)
	{
		if (it->isDead())
		{
			it->Ternimate();
			it = pool.erase(it);

			if (pool.empty()) return;
		}
	}
}

void Monster::SetDirection(int dire)
{
	if (pool.empty()) return;

	for (auto it = pool.begin(); it != pool.end(); it++)
	{
		it->SetDirection(dire);
	}
}