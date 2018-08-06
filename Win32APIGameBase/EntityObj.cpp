#include "stdafx.h"
#include "Sprite.h"
#include "EntityObj.h"

void Entity::Init(HWND hWnd, int x, int y, int type, COLORREF sprite)
{
	this->type = type;
	this->pos = { x, y };

	nowAnimation = STAND;
	nowDirection = DOWN;

	health = 100;

	switch (type)
	{
	case DEALER:
		Ani_stand[UP].Init(hWnd, x, y, 240, 122, 4, L"./Image/Walk_Ani/Dealer_Back.bmp");
		Ani_stand[DOWN].Init(hWnd, x, y, 216, 122, 4, L"./Image/Walk_Ani/Dealer_Front.bmp");
		Ani_stand[LEFT].Init(hWnd, x, y, 304, 122, 4, L"./Image/Walk_Ani/Dealer_Left.bmp");
		Ani_stand[RIGHT].Init(hWnd, x, y, 336, 122, 4, L"./Image/Walk_Ani/Dealer_Right.bmp");

		Ani_walk[UP].Init(hWnd, x, y, 240, 122, 4, L"./Image/Walk_Ani/Dealer_Back.bmp");
		Ani_walk[DOWN].Init(hWnd, x, y, 216, 122, 4, L"./Image/Walk_Ani/Dealer_Front.bmp");
		Ani_walk[LEFT].Init(hWnd, x, y, 304, 122, 4, L"./Image/Walk_Ani/Dealer_Left.bmp");
		Ani_walk[RIGHT].Init(hWnd, x, y, 336, 122, 4, L"./Image/Walk_Ani/Dealer_Right.bmp");
		
		Ani_attack[UP].Init(hWnd, x, y, 240, 122, 4, L"./Image/Walk_Ani/Dealer_Back.bmp");
		Ani_attack[DOWN].Init(hWnd, x, y, 216, 122, 4, L"./Image/Walk_Ani/Dealer_Front.bmp");
		Ani_attack[LEFT].Init(hWnd, x, y, 304, 122, 4, L"./Image/Walk_Ani/Dealer_Left.bmp");
		Ani_attack[RIGHT].Init(hWnd, x, y, 336, 122, 4, L"./Image/Walk_Ani/Dealer_Right.bmp");
		break;
	case WIZARD:
		Ani_stand[UP].Init(hWnd, x, y, 280, 102, 4, L"./Image/Walk_Ani/Wizard_Back.bmp");
		Ani_stand[DOWN].Init(hWnd, x, y, 264, 102, 4, L"./Image/Walk_Ani/Wizard_Front.bmp");
		Ani_stand[LEFT].Init(hWnd, x, y, 296, 102, 4, L"./Image/Walk_Ani/Wizard_Left.bmp");
		Ani_stand[RIGHT].Init(hWnd, x, y, 256, 102, 4, L"./Image/Walk_Ani/Wizard_Right.bmp");

		Ani_walk[UP].Init(hWnd, x, y, 280, 102, 4, L"./Image/Walk_Ani/Wizard_Back.bmp");
		Ani_walk[DOWN].Init(hWnd, x, y, 264, 102, 4, L"./Image/Walk_Ani/Wizard_Front.bmp");
		Ani_walk[LEFT].Init(hWnd, x, y, 296, 102, 4, L"./Image/Walk_Ani/Wizard_Left.bmp");
		Ani_walk[RIGHT].Init(hWnd, x, y, 256, 102, 4, L"./Image/Walk_Ani/Wizard_Right.bmp");

		Ani_attack[UP].Init(hWnd, x, y, 280, 102, 4, L"./Image/Walk_Ani/Wizard_Back.bmp");
		Ani_attack[DOWN].Init(hWnd, x, y, 264, 102, 4, L"./Image/Walk_Ani/Wizard_Front.bmp");
		Ani_attack[LEFT].Init(hWnd, x, y, 296, 102, 4, L"./Image/Walk_Ani/Wizard_Left.bmp");
		Ani_attack[RIGHT].Init(hWnd, x, y, 256, 102, 4, L"./Image/Walk_Ani/Wizard_Right.bmp");
		break;
	case TANKER:
		Ani_stand[UP].Init(hWnd, x, y, 424, 138, 4, L"./Image/Walk_Ani/Tanker_Back.bmp");
		Ani_stand[DOWN].Init(hWnd, x, y, 352, 138, 4, L"./Image/Walk_Ani/Tanker_Front.bmp");
		Ani_stand[LEFT].Init(hWnd, x, y, 280, 138, 4, L"./Image/Walk_Ani/Tanker_Left.bmp");
		Ani_stand[RIGHT].Init(hWnd, x, y, 248, 138, 4, L"./Image/Walk_Ani/Tanker_Right.bmp");

		Ani_walk[UP].Init(hWnd, x, y, 424, 138, 4, L"./Image/Walk_Ani/Tanker_Back.bmp");
		Ani_walk[DOWN].Init(hWnd, x, y, 352, 138, 4, L"./Image/Walk_Ani/Tanker_Front.bmp");
		Ani_walk[LEFT].Init(hWnd, x, y, 280, 138, 4, L"./Image/Walk_Ani/Tanker_Left.bmp");
		Ani_walk[RIGHT].Init(hWnd, x, y, 248, 138, 4, L"./Image/Walk_Ani/Tanker_Right.bmp");

		Ani_attack[UP].Init(hWnd, x, y, 424, 138, 4, L"./Image/Walk_Ani/Tanker_Back.bmp");
		Ani_attack[DOWN].Init(hWnd, x, y, 352, 138, 4, L"./Image/Walk_Ani/Tanker_Front.bmp");
		Ani_attack[LEFT].Init(hWnd, x, y, 280, 138, 4, L"./Image/Walk_Ani/Tanker_Left.bmp");
		Ani_attack[RIGHT].Init(hWnd, x, y, 248, 138, 4, L"./Image/Walk_Ani/Tanker_Right.bmp");
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

void Entity::Draw(HDC hMemDC)
{
	switch (nowAnimation)
	{
	case STAND:
		Ani_stand[nowDirection].Draw(hMemDC);
		break;
	case WALK:
		Ani_walk[nowDirection].Draw(hMemDC);
		break;
	case ATTACK:
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

void Monster::Init(HWND hWnd)
{
	spawnPosition = { 0,0 };
}
void Monster::Ternimate()
{
	if (monsterPool.empty()) return;

	for (auto it = monsterPool.begin(); it != monsterPool.end(); it++)
	{
		it->Ternimate();
		it = monsterPool.erase(it);

		if (monsterPool.empty()) return;
	}
}

void Monster::Draw(HDC hMemDC)
{
	if (monsterPool.empty()) return;

	for (auto it = monsterPool.begin(); it != monsterPool.end(); it++)
	{
		it->Draw(hMemDC);
	}
}
void Monster::Animation()
{
	if (monsterPool.empty()) return;

	for (auto it = monsterPool.begin(); it != monsterPool.end(); it++)
	{
		it->Animaition();
	}
}

void Monster::AddMonster(HWND hWnd, int type)
{
	Entity temp;
	temp.Init(hWnd, spawnPosition.x, spawnPosition.y, type);

	monsterPool.push_back(temp);

	temp.Ternimate();
}
void Monster::CheckHealth()
{
	if (monsterPool.empty()) return;

	for (auto it = monsterPool.begin(); it != monsterPool.end(); it++)
	{
		if (it->isDead())
		{
			it->Ternimate();
			it = monsterPool.erase(it);

			if (monsterPool.empty()) return;
		}
	}
}