#include "stdafx.h"
#include "Sprite.h"
#include "EntityObj.h"

POINT Entity::spawnPosition = { 2, 5 };
bool Entity::isStill = false;

vector<POINT> Entity::BanRoad;
int Entity::StackRoad[MAX_TILE_Y][MAX_TILE_X] = { 0 };
bool Entity::isAllSearch = false;
POINT Entity::PlayerPos = { 0,0 };

void Entity::Init(HWND hWnd, int x, int y, int type, int hp, COLORREF sprite)
{
	this->type = type;
	this->pos = { x, y };

	nowState = FINDWAY;
	stateFrame = 0;

	nowAnimation = STAND;
	nowDirection = RIGHT;

	nowFrame = 0;
	maxFrame = 4;

	health = hp;

	isSearch = false;
	SearchStack = 0;
	SearchDirection = -1;
	SearchGap = 0;

	switch (type)
	{
	case DEALER:
		Ani_stand[UP].Init(hWnd, 0, 0, 80, 120, 1, L"./Image/Stand_Ani/dealer/dealer_back_standing.bmp");
		Ani_stand[DOWN].Init(hWnd, 0, 0, 80, 120, 1, L"./Image/Stand_Ani/dealer/dealer_front_standing.bmp");
		Ani_stand[LEFT].Init(hWnd, 0, 0, 80, 120, 1, L"./Image/Stand_Ani/dealer/dealer_left_standing.bmp");
		Ani_stand[RIGHT].Init(hWnd, 0, 0, 80, 120, 1, L"./Image/Stand_Ani/dealer/dealer_right_standing.bmp");

		Ani_walk[UP].Init(hWnd, 0, 0, 480, 120, 6, L"./Image/Walk_Ani/dealer_walk_back.bmp");
		Ani_walk[DOWN].Init(hWnd, 0, 0, 480, 120, 6, L"./Image/Walk_Ani/dealer_walk_front.bmp");
		Ani_walk[LEFT].Init(hWnd, 0, 0, 480, 120, 6, L"./Image/Walk_Ani/dealer_walk_left.bmp");
		Ani_walk[RIGHT].Init(hWnd, 0, 0, 480, 120, 6, L"./Image/Walk_Ani/dealer_walk_right.bmp");

		Ani_attack[UP].Init(hWnd, 0, 0, 480, 120, 6, L"./Image/Attack_Ani/dealer_attack_back.bmp");
		Ani_attack[DOWN].Init(hWnd, 0, 0, 480, 120, 6, L"./Image/Attack_Ani/dealer_attack_front.bmp");
		Ani_attack[LEFT].Init(hWnd, 0, 0, 480, 120, 6, L"./Image/Attack_Ani/dealer_attack_left.bmp");
		Ani_attack[RIGHT].Init(hWnd, 0, 0, 480, 120, 6, L"./Image/Attack_Ani/dealer_attack_right.bmp");
		break;
	case WIZARD:
		Ani_stand[UP].Init(hWnd, 0, 0, 80, 102, 1, L"./Image/Walk_Ani/Wizard_Back.bmp");
		Ani_stand[DOWN].Init(hWnd, 0, 0, 80, 102, 1, L"./Image/Walk_Ani/Wizard_Front.bmp");
		Ani_stand[LEFT].Init(hWnd, 0, 0, 80, 102, 1, L"./Image/Walk_Ani/Wizard_Left.bmp");
		Ani_stand[RIGHT].Init(hWnd, 0, 0, 80, 102, 1, L"./Image/Walk_Ani/Wizard_Right.bmp");

		Ani_walk[UP].Init(hWnd, 0, 0, 320, 102, 4, L"./Image/Walk_Ani/Wizard_Back.bmp");
		Ani_walk[DOWN].Init(hWnd, 0, 0, 320, 102, 4, L"./Image/Walk_Ani/Wizard_Front.bmp");
		Ani_walk[LEFT].Init(hWnd, 0, 0, 320, 102, 4, L"./Image/Walk_Ani/Wizard_Left.bmp");
		Ani_walk[RIGHT].Init(hWnd, 0, 0, 320, 102, 4, L"./Image/Walk_Ani/Wizard_Right.bmp");

		Ani_attack[UP].Init(hWnd, 0, 0, 480, 102, 6, L"./Image/Attack_Ani/wizard_attack_back.bmp");
		Ani_attack[DOWN].Init(hWnd, 0, 0, 480, 102, 6, L"./Image/Attack_Ani/wizard_attack_front.bmp");
		Ani_attack[LEFT].Init(hWnd, 0, 0, 480, 102, 6, L"./Image/Attack_Ani/wizard_attack_left.bmp");
		Ani_attack[RIGHT].Init(hWnd, 0, 0, 480, 102, 6, L"./Image/Attack_Ani/wizard_attack_right.bmp");
		break;
	case TANKER:
		Ani_stand[UP].Init(hWnd, 0, 0, 106, 138, 1, L"./Image/Walk_Ani/Tanker_Back.bmp");
		Ani_stand[DOWN].Init(hWnd, 0, 0, 88, 138, 1, L"./Image/Walk_Ani/Tanker_Front.bmp");
		Ani_stand[LEFT].Init(hWnd, 0, 0, 80, 138, 1, L"./Image/Walk_Ani/Tanker_Left.bmp");
		Ani_stand[RIGHT].Init(hWnd, 0, 0, 88, 138, 1, L"./Image/Walk_Ani/Tanker_Right.bmp");

		Ani_walk[UP].Init(hWnd, 0, 0, 424, 138, 4, L"./Image/Walk_Ani/Tanker_Back.bmp");
		Ani_walk[DOWN].Init(hWnd, 0, 0, 352, 138, 4, L"./Image/Walk_Ani/Tanker_Front.bmp");
		Ani_walk[LEFT].Init(hWnd, 0, 0, 320, 138, 4, L"./Image/Walk_Ani/Tanker_Left.bmp");
		Ani_walk[RIGHT].Init(hWnd, 0, 0, 352, 138, 4, L"./Image/Walk_Ani/Tanker_Right.bmp");

		Ani_attack[UP].Init(hWnd, 0, 0, 636, 138, 6, L"./Image/Attack_Ani/tanker_attack_back.bmp");
		Ani_attack[DOWN].Init(hWnd, 0, 0, 528, 138, 6, L"./Image/Attack_Ani/tanker_attack_front.bmp");
		Ani_attack[LEFT].Init(hWnd, 0, 0, 480, 138, 6, L"./Image/Attack_Ani/tanker_attack_left.bmp");
		Ani_attack[RIGHT].Init(hWnd, 0, 0, 528, 138, 6, L"./Image/Attack_Ani/tanker_attack_right.bmp");
		break;
	}

	Health_UI.Init(hWnd, 0, 0, 20, 20, L"./Image/UI/Ingame/heart.bmp");
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

	int Term_x = 0, Term_y = 0;

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

	if (nowAnimation == WALK)
	{
		switch (nowDirection)
		{
		case UP:
			Term_y -= (stateFrame * 8);
			break;
		case DOWN:
			Term_y += (stateFrame * 8);
			break;
		case LEFT:
			Term_x -= (stateFrame * 8);
			break;
		case RIGHT:
			Term_x += (stateFrame * 8);
			break;
		}
	}

	Term_x += ObjPool->Player.GetWalkTerm().x;
	Term_y += ObjPool->Player.GetWalkTerm().y;

	switch (nowAnimation)
	{
	case STAND:
		Ani_stand[nowDirection].SetPosition(((pos.x - Map_x) - 1) * 80 + Term_x - 40, ((pos.y - Map_y) - 1) * 80 + Term_y - 40);
		Ani_stand[nowDirection].Draw(hMemDC);
		for (int i = 0; i < health; i++)
		{
			Health_UI.SetPosition(((pos.x - Map_x) - 1) * 80 + Term_x - 40 + (Ani_stand[nowDirection].w / 2) - (20 * health / 2) + (20 * i), ((pos.y - Map_y) - 1) * 80 + Term_y - 40 - 20);
			Health_UI.Draw(hMemDC);
		}
		break;
	case WALK:
		Ani_walk[nowDirection].SetPosition(((pos.x - Map_x) - 1) * 80 + Term_x - 40, ((pos.y - Map_y) - 1) * 80 + Term_y - 40);
		Ani_walk[nowDirection].Draw(hMemDC);
		for (int i = 0; i < health; i++)
		{
			Health_UI.SetPosition(((pos.x - Map_x) - 1) * 80 + Term_x - 40 + (Ani_stand[nowDirection].w / 2) - (20 * health / 2) + (20 * i), ((pos.y - Map_y) - 1) * 80 + Term_y - 40 - 20);
			Health_UI.Draw(hMemDC);
		}
		break;
	case ATTACK:
		Ani_attack[nowDirection].SetPosition(((pos.x - Map_x) - 1) * 80 + Term_x - 40, ((pos.y - Map_y) - 1) * 80 + Term_y - 40);
		Ani_attack[nowDirection].Draw(hMemDC);

		for (int i = 0; i < health; i++)
		{
			Health_UI.SetPosition(((pos.x - Map_x) - 1) * 80 + Term_x - 40 + (Ani_stand[nowDirection].w / 2) - (20 * health / 2) + (20 * i), ((pos.y - Map_y) - 1) * 80 + Term_y - 40 - 18);
			Health_UI.Draw(hMemDC);
		}
		break;
	case MARKFORFIND:
		Ani_stand[nowDirection].SetPosition(((pos.x - Map_x) - 1) * 80 + Term_x - 40, ((pos.y - Map_y) - 1) * 80 + Term_y - 40);
		Ani_stand[nowDirection].Draw(hMemDC);

		switch (nowDirection)
		{
		case UP:
			ObjPool->FindEffect.SetPosition(((pos.x - Map_x) - 1) * 80 + Term_x, ((pos.y - Map_y) - 1) * 80 + Term_y - 70);
			break;
		case DOWN:
			ObjPool->FindEffect.SetPosition(((pos.x - Map_x) - 1) * 80 + Term_x - 10, ((pos.y - Map_y) - 1) * 80 + Term_y - 70);
			break;
		case LEFT:
			ObjPool->FindEffect.SetPosition(((pos.x - Map_x) - 1) * 80 + Term_x + 10, ((pos.y - Map_y) - 1) * 80 + Term_y - 70);
			break;
		case RIGHT:
			ObjPool->FindEffect.SetPosition(((pos.x - Map_x) - 1) * 80 + Term_x - 25, ((pos.y - Map_y) - 1) * 80 + Term_y - 70);
			break;
		}
		ObjPool->FindEffect.Draw(hMemDC);

		break;
	}

	switch (nowState)
	{
		case CONFUSE:
			ObjPool->ConfuseEffect.SetPosition(((pos.x - Map_x) - 1) * 80 + Term_x - 25, ((pos.y - Map_y) - 1) * 80 + Term_y - 70);
			ObjPool->ConfuseEffect.Draw(hMemDC);
			break;
		case STILLSTONE_FIND:
		case STILLSTONE_WALK:
			TCHAR str[5];
			wsprintf(str, L"↓");
			ObjPool->Gdi.Text(hMemDC, ((pos.x - Map_x) - 1) * 80 + Term_x - 25, ((pos.y - Map_y) - 1) * 80 + Term_y - 110, str, 36);
			break;
	}
}

void Entity::Animation()
{
	switch (nowAnimation)
	{
	case WALK:
		Ani_walk[nowDirection].NextFrameSprite(true);
		break;
	case ATTACK:
		Ani_attack[nowDirection].NextFrameSprite(true);
		break;
	}

	switch (nowState)
	{
	case CONFUSE:
		ObjPool->ConfuseEffect.NextFrameSprite(true);
		break;
	}
}

void Entity::UpdateState()
{
	//걷는중 건들 ㄴㄴ
	if (nowState == WALK)
	{
		if (stateFrame < 10)
		{
			stateFrame++;
		}
		else
		{
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
			nowAnimation = STAND;
			nowState = FINDWAY;
			stateFrame = 0;
		}
		return;
	}

	//공격
	if (nowState == ATTACK)
	{
		if (stateFrame < 6)
		{
			stateFrame++;
		}
		else
		{
			this->Ani_attack[nowDirection].SetFrameSprite(0);

			int Temp_X = pos.x;
			int Temp_Y = pos.y;

			switch (nowDirection)
			{
			case LEFT: Temp_X = pos.x - 1;
				break;
			case RIGHT: Temp_X = pos.x + 1;
				break;
			case UP: Temp_Y = pos.y - 1;
				break;
			case DOWN: Temp_Y = pos.y + 1;
				break;
			}

			if (ObjPool->Player.GetPosition().x == Temp_X && ObjPool->Player.GetPosition().y == Temp_Y)
			{
				if (!isStill)
				{
					nowAnimation = STAND;
					nowState = STILLSTONE_FIND;
					stateFrame = 0;

					isStill = true;
					m_pathList.clear();
					return;
				}
				else
				{
					ObjPool->Player.Rock_Num -= 3;
					if (ObjPool->Player.Rock_Num < 0) ObjPool->Player.Rock_Num = 0;

					ObjPool->timeDropStone = 5;

					nowAnimation = ATTACK;
					nowState = ATTACK;
					stateFrame = 0;
					return;
				}
				//ObjPool->Sounds.Push(칼에 찔리는 소리);
			}
			//else if (ObjPool->Maps.Map[Temp_Y][Temp_X].Tile_ID == SKILL_Barricade)
			//{
			//	ObjPool->Maps.Map[Temp_Y][Temp_X].hp--;
			//	if (ObjPool->Maps.Map[Temp_Y][Temp_X].hp <= 0)
			//	{
			//		ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Floor, Temp_X, Temp_Y);
			//	}
			//	//ObjPool->Sounds.Push(칼이 튕겨나는 소리);
			//}
			else if (ObjPool->Maps.Map[Temp_Y][Temp_X].Tile_ID == TRAP_ScareCrow)
			{
				if(ObjPool->Maps.Map[Temp_Y][Temp_X].TrapHp_Now > 0)
					ObjPool->Maps.Map[Temp_Y][Temp_X].TrapHp_Now = 0;
				else
					ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Floor, Temp_X, Temp_Y);
				//ObjPool->Sounds.Push(칼이 튕겨나는 소리);
			}

			nowAnimation = STAND;
			nowState = FINDWAY;
			stateFrame = 0;
		}
		return;
	}

	//트랩 해체
	if (nowState == DISMANTLETRAP)
	{
		if (stateFrame < 60)
		{
			stateFrame++;

			if (stateFrame % 10 == 0)
				ObjPool->SoundPool.Play(EFFECT_DISMANTLETRAP);
		}
		else
		{
			int Temp_X = pos.x;
			int Temp_Y = pos.y;

			switch (nowDirection)
			{
			case LEFT: Temp_X = pos.x - 1;
				break;
			case RIGHT: Temp_X = pos.x + 1;
				break;
			case UP: Temp_Y = pos.y - 1;
				break;
			case DOWN: Temp_Y = pos.y + 1;
				break;
			}
			
			if ((ObjPool->Maps.Map[Temp_Y][Temp_X].Tile_ID == TRAP_Niddle
				|| ObjPool->Maps.Map[Temp_Y][Temp_X].Tile_ID == TRAP_Hole
				|| ObjPool->Maps.Map[Temp_Y][Temp_X].Tile_ID == TRAP_Confusion
				|| ObjPool->Maps.Map[Temp_Y][Temp_X].Tile_ID == TRAP_Grab) && type == WIZARD)
			{
				ObjPool->Maps.Map[Temp_Y][Temp_X].TrapHp_Now = 0;
				//ObjPool->Sounds.Push(칼이 튕겨나는 소리);
			}

			nowAnimation = STAND;
			nowState = FINDWAY;
			stateFrame = 0;
		}
		return;
	}

	//길찾기
	if (nowState == FINDWAY)
	{
		{
			switch (nowDirection)
			{
			case UP:
				if (ObjPool->Maps.GetTileID(pos.x, pos.y - 1) == SKILL_Barricade)
				{
					nowAnimation = ATTACK;
					nowState = ATTACK;
					return;
				}
			case DOWN:
				if (ObjPool->Maps.GetTileID(pos.x, pos.y + 1) == SKILL_Barricade)
				{
					nowAnimation = ATTACK;
					nowState = ATTACK;
					return;
				}
			case LEFT:
				if (ObjPool->Maps.GetTileID(pos.x - 1, pos.y) == SKILL_Barricade)
				{
					nowAnimation = ATTACK;
					nowState = ATTACK;
					return;
				}
			case RIGHT:
				if (ObjPool->Maps.GetTileID(pos.x + 1, pos.y) == SKILL_Barricade)
				{
					nowAnimation = ATTACK;
					nowState = ATTACK;
					return;
				}
			}

			for (int i = 0; i < MAX_TILE_Y; i++)
			{
				for (int j = 0; j < MAX_TILE_X; j++)
				{
					if (ObjPool->Maps.Map[i][j].TrapHp_Now != 0 && ObjPool->Maps.GetTileID(j, i) == TRAP_ScareCrow)
						if (isSearchFind(j, i))
						{
							if (SearchDirection == UP || SearchDirection == DOWN || SearchDirection == LEFT || SearchDirection == RIGHT)
							{
								SetDirection(SearchDirection);
							}
							else if ((SearchDirection == UPnLEFT || SearchDirection == UPnRIGHT) && !isRoadBlocked(UP))
							{
								SetDirection(UP);
							}
							else if ((SearchDirection == DOWNnLEFT || SearchDirection == DOWNnRIGHT) && !isRoadBlocked(DOWN))
							{
								SetDirection(DOWN);
							}
							else if ((SearchDirection == UPnLEFT || SearchDirection == DOWNnLEFT) && !isRoadBlocked(LEFT))
							{
								SetDirection(LEFT);
							}
							else if ((SearchDirection == UPnRIGHT || SearchDirection == DOWNnRIGHT) && !isRoadBlocked(RIGHT))
							{
								SetDirection(RIGHT);
							}

							if (SearchGap == 1)
							{
								nowAnimation = ATTACK;
								nowState = ATTACK;
								return;
							}
							else
							{
								nowAnimation = WALK;
								nowState = WALK;
								return;
							}
						}

					if (ObjPool->Maps.Map[i][j].TrapHp_Now != 0 && (type == WIZARD || type == TANKER) 
						&& (ObjPool->Maps.GetTileID(j, i) == TRAP_Niddle
						|| ObjPool->Maps.GetTileID(j, i) == TRAP_Hole
						|| ObjPool->Maps.GetTileID(j, i) == TRAP_Confusion
						|| ObjPool->Maps.GetTileID(j, i) == TRAP_Grab))
						if (isSearchFind(j, i) && SearchGap <= 2)
						{
							if (SearchDirection == UP || SearchDirection == DOWN || SearchDirection == LEFT || SearchDirection == RIGHT)
							{
								SetDirection(SearchDirection);
							}
							else if ((SearchDirection == UPnLEFT || SearchDirection == UPnRIGHT) && !isRoadBlocked(UP))
							{
								SetDirection(UP);
							}
							else if ((SearchDirection == DOWNnLEFT || SearchDirection == DOWNnRIGHT) && !isRoadBlocked(DOWN))
							{
								SetDirection(DOWN);
							}
							else if ((SearchDirection == UPnLEFT || SearchDirection == DOWNnLEFT) && !isRoadBlocked(LEFT))
							{
								SetDirection(LEFT);
							}
							else if ((SearchDirection == UPnRIGHT || SearchDirection == DOWNnRIGHT) && !isRoadBlocked(RIGHT))
							{
								SetDirection(RIGHT);
							}

							if (SearchGap == 1 && type == WIZARD)
							{
								nowAnimation = ATTACK;
								nowState = DISMANTLETRAP;
								return;
							}
							else
							{
								nowAnimation = WALK;
								nowState = WALK;
								return;
							}
						}
				}
			}
		}
		//트랩발견시 행동(플레이어 서치보다 우선순위 <<<허수아비때문에!!)

		{}

		{
			if (isSearchFind(ObjPool->Player.GetPosition().x, ObjPool->Player.GetPosition().y))
			{
				PlayerPos = ObjPool->Player.GetPosition();

				if (SearchDirection == UP || SearchDirection == DOWN || SearchDirection == LEFT || SearchDirection == RIGHT)
				{
					SetDirection(SearchDirection);
				}
				else if ((SearchDirection == UPnLEFT || SearchDirection == UPnRIGHT) && !isRoadBlocked(UP))
				{
					SetDirection(UP);
				}
				else if ((SearchDirection == DOWNnLEFT || SearchDirection == DOWNnRIGHT) && !isRoadBlocked(DOWN))
				{
					SetDirection(DOWN);
				}
				else if ((SearchDirection == UPnLEFT || SearchDirection == DOWNnLEFT) && !isRoadBlocked(LEFT))
				{
					SetDirection(LEFT);
				}
				else if ((SearchDirection == UPnRIGHT || SearchDirection == DOWNnRIGHT) && !isRoadBlocked(RIGHT))
				{
					SetDirection(RIGHT);
				}
				//방향 바꾸기
			}
			//일단 플레이어 위치 저장

			if (SearchGap == 1)
			{
				isAllSearch = true;

				nowAnimation = ATTACK;
				nowState = ATTACK;
				return;
			}
			//공격

			//여기서부터
			if (!isAllSearch)
			{
				if (SearchDirection != -1)
				{
					isAllSearch = true;

					ObjPool->FindEffect.SetFrameSprite(0);

					nowAnimation = MARKFORFIND;
					nowState = MARKFORFIND;
					//플레이어가 있는 방향만 보고 끝낸다(걷기x)
					return;
				}
			}

			if (isAllSearch)
			{
				if (!isSearch)
				{
					m_pathList.clear();
					isSearch = true;

					if (SearchStack > 5)
					{
						isSearch = false;
					}
					else if (PathFind(pos, PlayerPos))
					{
						if (m_pathList.empty())
						{
							isSearch = false;
							return;
						}

						list<POINT>::iterator it;
						it = m_pathList.begin();

						if (!isRoadBlocked(it->x, it->y))
						{
							if (pos.x == it->x && pos.y - 1 == it->y)
								SetDirection(UP);
							else if (pos.x == it->x && pos.y + 1 == it->y)
								SetDirection(DOWN);
							else if (pos.x - 1 == it->x && pos.y == it->y)
								SetDirection(LEFT);
							else if (pos.x + 1 == it->x && pos.y == it->y)
								SetDirection(RIGHT);
							else
							{
								m_pathList.clear();
								isSearch = false;
								return;
							}

							if (!isMonsterRoadOverlap(nowDirection))
							{
								nowAnimation = WALK;
								nowState = WALK;

								m_pathList.erase(it);
								return;
							}
							else
							{
								nowAnimation = STAND;
								nowState = FINDWAY;
								return;
							}
						}

						SearchStack = 0;
					}
					else
					{
						isSearch = false;
						SearchStack++;
						return;
					}
				}
				else if (isSearch)
				{
					if (m_pathList.empty())
					{
						isSearch = false;
						return;
					}

					list<POINT>::iterator it;
					it = m_pathList.begin();

					if (!isRoadBlocked(it->x, it->y))
					{
						if (pos.x == it->x && pos.y - 1 == it->y)
							SetDirection(UP);
						else if (pos.x == it->x && pos.y + 1 == it->y)
							SetDirection(DOWN);
						else if (pos.x - 1 == it->x && pos.y == it->y)
							SetDirection(LEFT);
						else if (pos.x + 1 == it->x && pos.y == it->y)
							SetDirection(RIGHT);
						else
						{
							m_pathList.clear();
							isSearch = false;
							return;
						}

						if (!isMonsterRoadOverlap(nowDirection))
						{
							nowAnimation = WALK;
							nowState = WALK;

							m_pathList.erase(it);
							return;
						}
						else
						{
							nowAnimation = STAND;
							nowState = FINDWAY;
							return;
						}
					}
				}
			}

		}
		//서치중이면 플레이어에게 간다 

		{}

		{
			/*
			StackRoad[pos.y][pos.x]++;

			if (StackRoad[pos.y][pos.x] > FirstSpawnMonsterNum)
			{
			SetBanRoad(pos.x, pos.y);
			}
			*/
			
			int BlockedRoadNum = 0;
			for (int i = 0; i < 4; i++)
			{
				if (isRoadBlocked(i) || isBanRoad(i))
					BlockedRoadNum++;
			}

			if (BlockedRoadNum >= 3)
			{
				if(pos.x != spawnPosition.x && pos.y != spawnPosition.y)
				SetBanRoad(pos.x, pos.y);
			}
		}
		//막다른 길이거나 / 스택 쌓아서 일정정도가 넘으면 밴

		{
			for (auto it = ObjPool->MonsterPool.ePool.begin(); it != ObjPool->MonsterPool.ePool.end(); it++)
			{
				switch (nowDirection)
				{
				case UP:
					if (it->pos.x == pos.x && it->pos.y == pos.y - 1)
					{
						if (nowDirection == returnReverseDirection(it->nowDirection))
						{
							srand((unsigned)time(NULL));
							if (rand() % 2)
								RotateClockwise();
							else
								RotateCounterclockwise();
						}
					}
					break;
				case DOWN:
					if (it->pos.x == pos.x && it->pos.y == pos.y + 1)
					{
						if (nowDirection == returnReverseDirection(it->nowDirection))
						{
							srand((unsigned)time(NULL));
							if (rand() % 2)
								RotateClockwise();
							else
								RotateCounterclockwise();
						}
					}
						break;
				case LEFT:
					if (it->pos.x == pos.x - 1 && it->pos.y == pos.y)
					{
						if (nowDirection == returnReverseDirection(it->nowDirection))
						{
							srand((unsigned)time(NULL));
							if (rand() % 2)
								RotateClockwise();
							else
								RotateCounterclockwise();
						}
					}
						break;
				case RIGHT:
					if (it->pos.x == pos.x + 1 && it->pos.y == pos.y)
					{
						if (nowDirection == returnReverseDirection(it->nowDirection))
						{
							srand((unsigned)time(NULL));
							if (rand() % 2)
								RotateClockwise();
							else
								RotateCounterclockwise();
						}
					}
						break;
				}
			}
		}
		//몬스터끼리 서로 마주보고 있어서 교통체증 방지

		{
			int BlockedRoadNum = 0;
			int BlockedRoad[4] = { 0 };
			for (int i = 0; i < 4; i++)
			{
				if (!isRoadBlocked(i) && !isBanRoad(i) && !isMonsterRoadOverlap(i) && returnReverseDirection(nowDirection) != i)
				{
					BlockedRoad[BlockedRoadNum] = { i };
					BlockedRoadNum++;
				}
			}

			if (BlockedRoadNum > 0)
			{
				srand((unsigned)time(NULL));
				SetDirection(BlockedRoad[rand() % BlockedRoadNum]);

				nowAnimation = WALK;
				nowState = WALK;
				ObjPool->debug = 1;
				return;
			}
		}
		//갈림길에서 어디로 갈지 랜덤으로 체크

		{
			if (isBanRoad(pos.x, pos.y))
			{
				if (!isRoadBlocked(nowDirection) && !isMonsterRoadOverlap(nowDirection))
				{
					nowAnimation = WALK;
					nowState = WALK;
					ObjPool->debug = 2;
					return;
				}
				else if (isRoadBlocked(nowDirection) && !isMonsterRoadOverlap(returnReverseDirection(nowDirection)))
				{
					SetDirection(returnReverseDirection(nowDirection));

					nowAnimation = WALK;
					nowState = WALK;
					ObjPool->debug = 3;
					return;
				}
				else
				{
					int BlockedRoadNum = 0;
					int BlockedRoad[4] = { 0 };
					for (int i = 0; i < 4; i++)
					{
						if (!isRoadBlocked(i) && !isMonsterRoadOverlap(i))
						{
							BlockedRoad[BlockedRoadNum] = { i };
							BlockedRoadNum++;
						}
					}

					if (BlockedRoadNum > 0)
					{
						srand((unsigned)time(NULL));
						SetDirection(BlockedRoad[rand() % BlockedRoadNum]);

						nowAnimation = WALK;
						nowState = WALK;
						ObjPool->debug = 4;
						return;
					}
				}
			}
		}
		//자신이 왔던 길이 벤되어있다면 반대 방향으로 걸어감

		return;
	}

	//플레이어 발견했을때 느낌표!
	if (nowState == MARKFORFIND)
	{
		if (stateFrame < 10)
		{
			stateFrame++;
			if (stateFrame < 7 && stateFrame % 2)
				ObjPool->FindEffect.NextFrameSprite(false);
		}
		else
		{
			if (!isRoadBlocked(nowDirection) && !isMonsterRoadOverlap(nowDirection))
			{
				nowAnimation = WALK;
				nowState = WALK;
			}
			else
			{
				nowAnimation = STAND;
				nowState = FINDWAY;
			}
			stateFrame = 0;
		}
		return;
	}

	//혼란..?
	if (nowState == CONFUSE)
	{
		if (stateFrame < 100)
		{
			stateFrame++;
		}
		else
		{
			nowAnimation = STAND;
			nowState = FINDWAY;
		}
	}
	
	//돌 뺏음
	if (nowState == STILLSTONE_FIND)
	{
		if (pos.x == spawnPosition.x && pos.y == spawnPosition.y)
		{
			ObjPool->System.SetScene(SCENE_ENDING);
		}
		
		if (!isStill)
		{
			nowAnimation = STAND;
			nowState = FINDWAY;
			return;
		}

		if (m_pathList.empty())
		{
			if (PathFind(pos, spawnPosition))
			{
				if (m_pathList.empty())
				{
					return;
				}

				list<POINT>::iterator it;
				it = m_pathList.begin();

				if (!isRoadBlocked(it->x, it->y))
				{
					if (pos.x == it->x && pos.y - 1 == it->y)
						SetDirection(UP);
					else if (pos.x == it->x && pos.y + 1 == it->y)
						SetDirection(DOWN);
					else if (pos.x - 1 == it->x && pos.y == it->y)
						SetDirection(LEFT);
					else if (pos.x + 1 == it->x && pos.y == it->y)
						SetDirection(RIGHT);

					nowAnimation = WALK;
					nowState = STILLSTONE_WALK;

					m_pathList.erase(it);
					return;
				}
			}
			else
			{
				return;
			}
		}
		else
		{
			list<POINT>::iterator it;
			it = m_pathList.begin();

			if (!isRoadBlocked(it->x, it->y))
			{
				if (pos.x == it->x && pos.y - 1 == it->y)
					SetDirection(UP);
				else if (pos.x == it->x && pos.y + 1 == it->y)
					SetDirection(DOWN);
				else if (pos.x - 1 == it->x && pos.y == it->y)
					SetDirection(LEFT);
				else if (pos.x + 1 == it->x && pos.y == it->y)
					SetDirection(RIGHT);

				nowAnimation = WALK;
				nowState = STILLSTONE_WALK;

				m_pathList.erase(it);
				return;
			}
		}
	}

	if (nowState == STILLSTONE_WALK)
	{
		if (pos.x == spawnPosition.x && pos.y == spawnPosition.y)
		{
			ObjPool->System.SetScene(SCENE_ENDING);
		}

		if (!isStill)
		{
			nowAnimation = STAND;
			nowState = FINDWAY;
			return;
		}

		if (stateFrame < 10)
		{
			stateFrame++;
		}
		else
		{
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
			nowAnimation = STAND;
			nowState = STILLSTONE_FIND;
			stateFrame = 0;
		}
		return;
	}
}

bool Entity::GetAllSearch()
{
	return isAllSearch;
}

bool Entity::GetSearch()
{
	return isSearch;
}

void Entity::SetAllSearch(bool is)
{
	isAllSearch = is;
}

bool Entity::isSearchFind(int x, int y)
{
	POINT temp;
	temp.x = x;
	temp.y = y;

	SearchDirection = -1;
	SearchGap = 0;

	if ((temp.y < pos.y && temp.y + 4 >= pos.y && pos.x == temp.x))
	{
		SearchDirection = UP;
		SearchGap = pos.y - temp.y;

		for (int i = 1; i <= SearchGap; i++)
		{
			if (i == SearchGap && ObjPool->Maps.GetTileID(temp.x, temp.y) == TRAP_ScareCrow) break;

			if (isRoadBlocked(pos.x, pos.y - i))
			{
				SearchDirection = -1;
				return false;
			}
		}
	}
	else if ((temp.y > pos.y && temp.y - 4 <= pos.y && pos.x == temp.x))
	{
		SearchDirection = DOWN;
		SearchGap = temp.y - pos.y;

		for (int i = 1; i <= SearchGap; i++)
		{
			if (i == SearchGap && ObjPool->Maps.GetTileID(temp.x, temp.y) == TRAP_ScareCrow) break;

			if (isRoadBlocked(pos.x, pos.y + i))
			{
				SearchDirection = -1;
				return false;
			}
		}
	}
	else if ((temp.x < pos.x && temp.x + 4 >= pos.x && pos.y == temp.y))
	{
		SearchDirection = LEFT;
		SearchGap = pos.x - temp.x;

		for (int i = 1; i <= SearchGap; i++)
		{
			if (i == SearchGap && ObjPool->Maps.GetTileID(temp.x, temp.y) == TRAP_ScareCrow) break;

			if (isRoadBlocked(pos.x - i, pos.y))
			{
				SearchDirection = -1;
				return false;
			}
		}
	}
	else if ((temp.x > pos.x && temp.x - 4 <= pos.x && pos.y == temp.y))
	{
		SearchDirection = RIGHT;
		SearchGap = temp.x - pos.x;

		for (int i = 1; i <= SearchGap; i++)
		{
			if (i == SearchGap && ObjPool->Maps.GetTileID(temp.x, temp.y) == TRAP_ScareCrow) break;

			if (isRoadBlocked(pos.x + i, pos.y))
			{
				SearchDirection = -1;
				return false;
			}
		}
	}

	else if ((temp.x == pos.x - 1 && temp.y == pos.y - 1))
	{
		if (!isRoadBlocked(UP) || !isRoadBlocked(LEFT))
		{
			SearchDirection = UPnLEFT;
			SearchGap = 2;
		}
		else
		{
			return false;
		}
	}
	else if ((temp.x == pos.x + 1 && temp.y == pos.y - 1))
	{
		if (!isRoadBlocked(UP) || !isRoadBlocked(RIGHT))
		{
			SearchDirection = UPnRIGHT;
			SearchGap = 2;
		}
		else
		{
			return false;
		}
	}
	else if ((temp.x == pos.x - 1 && temp.y == pos.y + 1))
	{
		if (!isRoadBlocked(DOWN) || !isRoadBlocked(LEFT))
		{
			SearchDirection = DOWNnLEFT;
			SearchGap = 2;
		}
		else
		{
			return false;
		}
	}
	else if ((temp.x == pos.x + 1 && temp.y == pos.y + 1))
	{
		if (!isRoadBlocked(DOWN) || !isRoadBlocked(RIGHT))
		{
			SearchDirection = DOWNnRIGHT;
			SearchGap = 2;
		}
		else
		{
			return false;
		}
	}

	if (SearchDirection != -1 && SearchGap != 0)
	{
		return true;
	}

	return false;
}

bool Entity::isRoadBlocked()
{
	return isRoadBlocked(nowDirection);
}

bool Entity::isRoadBlocked(int x, int y)
{
	if (ObjPool->Maps.GetTileMoveID(x, y))
		return false;

	return true;
}

bool Entity::isRoadBlocked(int dire)
{
	switch (dire)
	{
	case UP:
		if (ObjPool->Maps.GetTileMoveID(pos.x, pos.y - 1))
			return false;

		break;
	case DOWN:
		if (ObjPool->Maps.GetTileMoveID(pos.x, pos.y + 1))
			return false;

		break;
	case LEFT:
		if (ObjPool->Maps.GetTileMoveID(pos.x - 1, pos.y))
			return false;

		break;
	case RIGHT:
		if (ObjPool->Maps.GetTileMoveID(pos.x + 1, pos.y))
			return false;

		break;
	}

	return true;
}

void Entity::RotateClockwise()
{
	switch (nowDirection)
	{
	case UP:
		nowDirection = RIGHT;
		break;
	case DOWN:
		nowDirection = LEFT;
		break;
	case LEFT:
		nowDirection = UP;
		break;
	case RIGHT:
		nowDirection = DOWN;
		break;
	}
}

void Entity::RotateCounterclockwise()
{
	switch (nowDirection)
	{
	case UP:
		nowDirection = LEFT;
		break;
	case DOWN:
		nowDirection = RIGHT;
		break;
	case LEFT:
		nowDirection = DOWN;
		break;
	case RIGHT:
		nowDirection = UP;
		break;
	}
}

void Entity::RotateReverse()
{
	switch (nowDirection)
	{
	case UP:
		nowDirection = DOWN;
		break;
	case DOWN:
		nowDirection = UP;
		break;
	case LEFT:
		nowDirection = RIGHT;
		break;
	case RIGHT:
		nowDirection = LEFT;
		break;
	}
}

void Entity::SetBanRoad(int x, int y)
{
	POINT temp = { x,y };

	BanRoad.push_back(temp);
}

bool Entity::isBanRoad(int x, int y)
{
	for (auto it = BanRoad.begin(); it != BanRoad.end(); it++)
		if (it->x == x && it->y == y)
			return true;

	return false;
}

bool Entity::isBanRoad(int dire)
{
	switch (dire)
	{
	case UP:
		return isBanRoad(pos.x, pos.y - 1);

		break;
	case DOWN:
		return isBanRoad(pos.x, pos.y + 1);

		break;
	case LEFT:
		return isBanRoad(pos.x - 1, pos.y);

		break;
	case RIGHT:
		return isBanRoad(pos.x + 1, pos.y);

		break;
	}

	return true;
}

bool Entity::isMonsterRoadOverlap(int x, int y)
{
	for (auto it = ObjPool->MonsterPool.ePool.begin(); it != ObjPool->MonsterPool.ePool.end(); it++)
	{
		if (it->nowState != STILLSTONE_FIND && it->nowState != STILLSTONE_WALK)
		if (it->nowState == WALK)
		{
			switch (it->nowDirection)
			{
			case UP:
				if ((it->pos.x == x && it->pos.y - 1 == y) || (it->pos.x == x && it->pos.y == y)) return true;

				break;
			case DOWN:
				if ((it->pos.x == x && it->pos.y + 1 == y) || (it->pos.x == x && it->pos.y == y)) return true;

				break;
			case LEFT:
				if ((it->pos.x - 1 == x && it->pos.y == y) || (it->pos.x == x && it->pos.y == y)) return true;

				break;
			case RIGHT:
				if ((it->pos.x + 1 == x && it->pos.y == y) || (it->pos.x == x && it->pos.y == y)) return true;

				break;
			}
		}
		else
		{
			if (it->pos.x == x && it->pos.y == y)
				return true;
		}
	}

	return false;
}

bool Entity::isMonsterRoadOverlap(int dire)
{
	switch (dire)
	{
	case UP:
		return isMonsterRoadOverlap(pos.x, pos.y - 1);

		break;
	case DOWN:
		return isMonsterRoadOverlap(pos.x, pos.y + 1);

		break;
	case LEFT:
		return isMonsterRoadOverlap(pos.x - 1, pos.y);

		break;
	case RIGHT:
		return isMonsterRoadOverlap(pos.x + 1, pos.y);

		break;
	}
}

POINT Entity::GetPosition()
{
	return pos;
}

POINT Entity::GetSpawnPosition()
{
	return spawnPosition;
}

Entity* Entity::GetEntity()
{
	return this;
}

int Entity::GetDirection()
{
	return nowDirection;
}

int Entity::GetHealth()
{
	return health;
}

int Entity::GetState()
{
	return nowState;
}

int Entity::GetType()
{
	return type;
}

void Entity::SetPosition(int x, int y)
{
	this->pos.x = x;
	this->pos.y = y;
}

void Entity::SetSpawnPosition(int x, int y)
{
	spawnPosition = { x,y };
}

void Entity::SetAnimation(int ani)
{
	nowAnimation = ani;
}

void Entity::SetDirection(int dire)
{
	nowDirection = dire;
}

void Entity::SetHealth(int hp)
{
	health = hp;
}

void Entity::AddHealth(int a)
{
	health += a;

	if (health <= 0 && (nowState == STILLSTONE_FIND || nowState == STILLSTONE_WALK))
	{
		isStill = false;
	}
}

void Entity::SetState(int state)
{
	nowState = state;
}

void Entity::SetStateFrame(int Frame)
{
	stateFrame = Frame;
}

bool Entity::isDead()
{
	return !(health > 0);
}

bool Entity::isWalk()
{
	if (nowAnimation != WALK) return false;
	if (nowFrame == (maxFrame * 4)) return false;

	return true;
}

int Entity::returnReverseDirection(int dire)
{
	switch (dire)
	{
	case UP:
		return DOWN;

		break;
	case DOWN:
		return UP;

		break;
	case LEFT:
		return RIGHT;

		break;
	case RIGHT:
		return LEFT;

		break;
	}
}

void Monster::Init(HWND hWnd)
{
	Dealer.Init(hWnd, 0, 0, DEALER, 2);
	Wizard.Init(hWnd, 0, 0, WIZARD, 1);
	Tanker.Init(hWnd, 0, 0, TANKER, 5);
}

Monster Monster::GetMonster()
{
	return *this;
}

void Monster::Ternimate()
{
	Dealer.Ternimate();
	Wizard.Ternimate();
	Tanker.Ternimate();

	if (ePool.empty()) return;

	for (auto it = ePool.begin(); it != ePool.end(); it++)
	{
		it->Ternimate();
	}

	ePool.clear();
}

void Monster::Draw(HDC hMemDC, int x, int y)
{
	//if (ePool.empty())	//몬스터가 없으면 플레이어만 생성
	//{
	//	ObjPool->Player.Draw(hMemDC, x, y);
	//	return;
	//}

	bool isPlayer = false;

	for (int i = 0; i < MAX_TILE_Y; i++)
	{
		for (int j = 0; j < MAX_TILE_X; j++)
		{
			if (!ePool.empty())
			{
				for (auto it = ePool.begin(); it != ePool.end(); it++)
					if (it->GetPosition().y == i && it->GetPosition().x == j) it->Draw(hMemDC, x, y);
			}

			if (!isPlayer)
				if (ObjPool->Player.GetPosition().y == i && ObjPool->Player.GetPosition().x == j)
				{
					if (ObjPool->Player.ATK_Skill.Check_Active)
					{
						ObjPool->Player.ATK_Skill.Draw(hMemDC);
					}
					if (ObjPool->Player.PUSH_Skill.Check_Active && ObjPool->Player.GetDirection() != DOWN)
					{
						ObjPool->Player.PUSH_Skill.Draw(hMemDC);
					}
					if (ObjPool->Player.BARRICADE_Skill.Check_Active && ObjPool->Player.GetDirection() != DOWN)
					{
						ObjPool->Player.BARRICADE_Skill.Draw(hMemDC);
					}

					ObjPool->Player.Draw(hMemDC, x, y);
					isPlayer = true;

					if (ObjPool->Player.PUSH_Skill.Check_Active && ObjPool->Player.GetDirection() == DOWN)
					{
						ObjPool->Player.PUSH_Skill.Draw(hMemDC);
					}
					if (ObjPool->Player.BARRICADE_Skill.Check_Active && ObjPool->Player.GetDirection() == DOWN)
					{
						ObjPool->Player.BARRICADE_Skill.Draw(hMemDC);
					}
				}

				if (ObjPool->Maps.Map[i][j].Tile_ID == TRAP_ScareCrow)
				{
					if (ObjPool->Maps.Map[i][j].Tile_On)
						ObjPool->Maps.Map[i][j].Tile_Sprite_On.Draw(hMemDC);
					else
						ObjPool->Maps.Map[i][j].Tile_Sprite_Off.Draw(hMemDC);
				}
		}
	}

	DrawMap(hMemDC, x, y);
}

void Monster::Animation()
{
	if (ePool.empty()) return;

	for (auto it = ePool.begin(); it != ePool.end(); it++)
	{
		it->Animation();
	}
}

void Monster::UpdateState()
{
	if (ePool.empty()) return;

	bool isSearch = false;
	for (auto it = ePool.begin(); it != ePool.end(); it++)
	{
		if (it->GetHealth() <= 0)
		{
			it = ePool.erase(it);
		}

		it->UpdateState();

		if (it->GetAllSearch())
		{
			if (it->GetSearch()) isSearch = true;
		}
	}
	if (!isSearch)
	{
		if(ePool.size() != 1)
			ePool.begin()->SetAllSearch(false);
	}
}

void Monster::AddMonster(int type, int x, int y)
{
	switch (type)
	{
	case DEALER:
		Dealer.SetPosition(x, y);
		ePool.push_back(Dealer);
		break;
	case WIZARD:
		Wizard.SetPosition(x, y);
		ePool.push_back(Wizard);
		break;
	case TANKER:
		Tanker.SetPosition(x, y);
		ePool.push_back(Tanker);
		break;
	}
}

void Monster::AddMonster(int type)
{
	AddMonster(type, Dealer.GetSpawnPosition().x, Dealer.GetSpawnPosition().y);
}

void Monster::AddMonster_Next(int type, int x, int y)
{
	switch (type)
	{
	case DEALER:
		Dealer.SetPosition(x, y);
		ePool_Next.push_back(Dealer);
		break;
	case WIZARD:
		Wizard.SetPosition(x, y);
		ePool_Next.push_back(Wizard);
		break;
	case TANKER:
		Tanker.SetPosition(x, y);
		ePool_Next.push_back(Tanker);
		break;
	}
}

void Monster::AddMonster_Next(int type)
{
	AddMonster_Next(type, Dealer.GetSpawnPosition().x, Dealer.GetSpawnPosition().y);
	CheckMonsters_Num[type]++;
}

void Monster::NextWave()
{
	for (auto it = ePool_Next.begin(); it != ePool_Next.end(); it++)
		AddMonster(it->GetEntity()->GetType());

	ePool_Next.clear();

	for (int i = 0; i < 3; i++)
		CheckMonsters_Num[i] = 0;

	int Temp;

	AddMonster_Next(WIZARD);

	for (int i = 0; i < 2; i++)
	{
		Temp = rand() % 3;

		switch (Temp)
		{
		case 0:
			AddMonster_Next(DEALER);
			break;
		case 1:
			AddMonster_Next(TANKER);
			break;
		case 2:
			AddMonster_Next(WIZARD);
			break;
		}
	}

	ObjPool->MonsterTimer = 30;

	for (int i = 0; i < 3; i++)
		wsprintf(CheckMonsters_Num_UI[i], L"%d", CheckMonsters_Num[i]);
}

bool Monster::CheckHealth(Entity* ent)
{
	if (ePool.empty()) return false;

	if (ent->isDead())
	{
		Wizard.SetHealth(1);
		Dealer.SetHealth(2);
		Tanker.SetHealth(5);
		return true;
	}

	return false;
}

void Monster::SetDirection(int dire)
{
	if (ePool.empty()) return;

	for (auto it = ePool.begin(); it != ePool.end(); it++)
	{
		it->SetDirection(dire);
	}
}

void Monster::DrawMap(HDC hMemDC, int x, int y)
{
	if (x <= 8)
		x = 8;
	if (y <= 5)
		y = 5;
	if (x >= MAX_TILE_X - 9)
		x = 27;
	if (y >= MAX_TILE_Y - 4)
		y = 18;

	int Map_Start_x = x - 9;
	int Map_End_x = x + 10;
	int Map_Start_y = y - 6;
	int Map_End_y = y + 5;

	int Term_x = ObjPool->Player.GetWalkTerm().x, Term_y = ObjPool->Player.GetWalkTerm().y;

	for (int i = Map_Start_y; i < Map_End_y; i++)
	{
		for (int j = Map_Start_x; j < Map_End_x; j++)
		{
			if (i < 1 || j < 1 || i >= MAX_TILE_Y || j >= MAX_TILE_X)
				continue;

			TCHAR str[10];
			ObjPool->Gdi.SetTextsColor(RGB(250, 250, 250));

			if (Dealer.isBanRoad(j, i))
				wsprintf(str, L"X");
			else
				wsprintf(str, L" ");

			ObjPool->Gdi.Text(hMemDC, ((j - Map_Start_x) - 1) * 80 + Term_x - 40 + 30, ((i - Map_Start_y) - 2) * 80 + Term_y + 40, str, 36);
		}
	}
}