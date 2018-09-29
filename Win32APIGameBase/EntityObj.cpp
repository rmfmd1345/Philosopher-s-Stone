#include "stdafx.h"
#include "Sprite.h"
#include "EntityObj.h"

POINT Entity::spawnPosition = { 0,0 };

vector<POINT> Entity::BanRoad;
int Entity::StackRoad[MAX_TILE_Y][MAX_TILE_X] = { 0 };
bool Entity::isAllSearch = false;
POINT Entity::PlayerPos = { 0,0 };

void Entity::Init(HWND hWnd, int x, int y, int type, COLORREF sprite)
{
	this->type = type;
	this->pos = { x, y };

	nowState = WALK;
	stateFrame = 0;

	nowAnimation = WALK;
	nowDirection = RIGHT;

	nowFrame = 0;
	maxFrame = 4;

	health = 100;

	switch (type)
	{
	case DEALER:
<<<<<<< HEAD
		Ani_stand[UP].Init(hWnd, 0, 0, 60, 122, 1, L"./Image/Walk_Ani/Dealer_Back.bmp");
		Ani_stand[DOWN].Init(hWnd, 0, 0, 54, 122, 1, L"./Image/Walk_Ani/Dealer_Front.bmp");
		Ani_stand[LEFT].Init(hWnd, 0, 0, 76, 122, 1, L"./Image/Walk_Ani/Dealer_Left.bmp");
		Ani_stand[RIGHT].Init(hWnd, 0, 0, 84, 122, 1, L"./Image/Walk_Ani/Dealer_Right.bmp");

		Ani_walk[UP].Init(hWnd, 0, 0, 240, 122, 4, L"./Image/Walk_Ani/Dealer_Back.bmp");
		Ani_walk[DOWN].Init(hWnd, 0, 0, 216, 122, 4, L"./Image/Walk_Ani/Dealer_Front.bmp");
		Ani_walk[LEFT].Init(hWnd, 0, 0, 304, 122, 4, L"./Image/Walk_Ani/Dealer_Left.bmp");
		Ani_walk[RIGHT].Init(hWnd, 0, 0, 336, 122, 4, L"./Image/Walk_Ani/Dealer_Right.bmp");

		Ani_attack[UP].Init(hWnd, 0, 0, 240, 122, 4, L"./Image/Walk_Ani/Dealer_Back.bmp");
		Ani_attack[DOWN].Init(hWnd, 0, 0, 216, 122, 4, L"./Image/Walk_Ani/Dealer_Front.bmp");
		Ani_attack[LEFT].Init(hWnd, 0, 0, 304, 122, 4, L"./Image/Walk_Ani/Dealer_Left.bmp");
		Ani_attack[RIGHT].Init(hWnd, 0, 0, 336, 122, 4, L"./Image/Walk_Ani/Dealer_Right.bmp");
=======
		Ani_stand[UP].Init(hWnd, 0, 0, 80, 120, 1, L"./Image/Walk_Ani/dealer_walk_back.bmp");
		Ani_stand[DOWN].Init(hWnd, 0, 0, 80, 120, 1, L"./Image/Walk_Ani/dealer_walk_front.bmp");
		Ani_stand[LEFT].Init(hWnd, 0, 0, 80, 120, 1, L"./Image/Walk_Ani/dealer_walk_left.bmp");
		Ani_stand[RIGHT].Init(hWnd, 0, 0, 80, 120, 1, L"./Image/Walk_Ani/dealer_walk_right.bmp");

		Ani_walk[UP].Init(hWnd, 0, 0, 480, 120, 6, L"./Image/Walk_Ani/dealer_walk_back.bmp");
		Ani_walk[DOWN].Init(hWnd, 0, 0, 480, 120, 6, L"./Image/Walk_Ani/dealer_walk_front.bmp");
		Ani_walk[LEFT].Init(hWnd, 0, 0, 480, 120, 6, L"./Image/Walk_Ani/dealer_walk_left.bmp");
		Ani_walk[RIGHT].Init(hWnd, 0, 0, 480, 120, 6, L"./Image/Walk_Ani/dealer_walk_right.bmp");
		
		/*Ani_attack[B_UP].Init(hWnd, 0, 0, 240, 122, 4, L"./Image/Walk_Ani/Dealer_Back.bmp");
		Ani_attack[B_DOWN].Init(hWnd, 0, 0, 216, 122, 4, L"./Image/Walk_Ani/Dealer_Front.bmp");
		Ani_attack[B_LEFT].Init(hWnd, 0, 0, 304, 122, 4, L"./Image/Walk_Ani/Dealer_Left.bmp");
		Ani_attack[B_RIGHT].Init(hWnd, 0, 0, 336, 122, 4, L"./Image/Walk_Ani/Dealer_Right.bmp");*/
>>>>>>> 03c2574cc853778e0e6192347a15cbd10c81ab21
		break;
	case WIZARD:
		Ani_stand[UP].Init(hWnd, 0, 0, 70, 102, 1, L"./Image/Walk_Ani/Wizard_Back.bmp");
		Ani_stand[DOWN].Init(hWnd, 0, 0, 66, 102, 1, L"./Image/Walk_Ani/Wizard_Front.bmp");
		Ani_stand[LEFT].Init(hWnd, 0, 0, 74, 102, 1, L"./Image/Walk_Ani/Wizard_Left.bmp");
		Ani_stand[RIGHT].Init(hWnd, 0, 0, 64, 102, 1, L"./Image/Walk_Ani/Wizard_Right.bmp");

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
		Ani_stand[UP].Init(hWnd, 0, 0, 106, 138, 1, L"./Image/Walk_Ani/Tanker_Back.bmp");
		Ani_stand[DOWN].Init(hWnd, 0, 0, 88, 138, 1, L"./Image/Walk_Ani/Tanker_Front.bmp");
		Ani_stand[LEFT].Init(hWnd, 0, 0, 70, 138, 1, L"./Image/Walk_Ani/Tanker_Left.bmp");
		Ani_stand[RIGHT].Init(hWnd, 0, 0, 62, 138, 1, L"./Image/Walk_Ani/Tanker_Right.bmp");

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
		/*switch (nowDirection)
		{
		case B_UP:
			Term_x = 5;
			break;
		case B_DOWN:
			Term_x = 15;
			break;
		case B_LEFT:
			Term_x = -12;
			break;
		case B_RIGHT:
			Term_x = 15;
			break;
		}*/
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

	if (nowState == WALK)
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

	Term_x += ObjPool->Player.GetWalkTerm().x;
	Term_y += ObjPool->Player.GetWalkTerm().y;

	switch (nowAnimation)
	{
	case STAND:
		Ani_stand[nowDirection].SetPosition(((pos.x - Map_x) - 1) * 80 + Term_x - 40, ((pos.y - Map_y) - 1) * 80 + Term_y - 40);
		Ani_stand[nowDirection].Draw(hMemDC);
<<<<<<< HEAD
		break;
	case WALK:
		Ani_walk[nowDirection].SetPosition(((pos.x - Map_x) - 1) * 80 + Term_x - 40, ((pos.y - Map_y) - 1) * 80 + Term_y);
		Ani_walk[nowDirection].Draw(hMemDC);
		break;
	case ATTACK:
		Ani_attack[nowDirection].SetPosition(((pos.x - Map_x) - 1) * 80 + Term_x - 40, ((pos.y - Map_y) - 1) * 80 + Term_y);
=======
		break;														 
	case WALK:														 
		Ani_walk[nowDirection].SetPosition(((pos.x - Map_x) - 1) * 80 + Term_x - 40, ((pos.y - Map_y) - 1) * 80 + Term_y - 40);
		Ani_walk[nowDirection].Draw(hMemDC); 
		break;														 
	case ATTACK:													 
		Ani_attack[nowDirection].SetPosition(((pos.x - Map_x) - 1) * 80 + Term_x - 40, ((pos.y - Map_y) - 1) * 80 + Term_y - 40);
>>>>>>> 03c2574cc853778e0e6192347a15cbd10c81ab21
		Ani_attack[nowDirection].Draw(hMemDC);
		break;
	case MARKFORFIND:
		Ani_stand[nowDirection].SetPosition(((pos.x - Map_x) - 1) * 80 + Term_x - 40, ((pos.y - Map_y) - 1) * 80 + Term_y);
		Ani_stand[nowDirection].Draw(hMemDC);
		ObjPool->Gdi.SetBrushColor(RGB(255, 255, 255));
		ObjPool->Gdi.Rect(hMemDC, { ((pos.x - Map_x) - 1) * 80 + Term_x - 40, ((pos.y - Map_y) - 1) * 80 + Term_y - 40,((pos.x - Map_x) - 1) * 80 + Term_x + 40, ((pos.y - Map_y) - 1) * 80 + Term_y });
		ObjPool->Gdi.SetTextsColor(RGB(255, 50, 50));
		ObjPool->Gdi.Text(hMemDC, ((pos.x - Map_x) - 1) * 80 + Term_x - 10, ((pos.y - Map_y) - 1) * 80 + Term_y - 30, L"!!!", 24);
		break;
	}
}

void Entity::Animation()
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
		if (stateFrame < 5)
		{
			stateFrame++;
		}
		else
		{
			//ObjPool->Player.AddHealth(-10);

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
			StackRoad[pos.y][pos.x]++;

			if (StackRoad[pos.y][pos.x] > FirstSpawnMonsterNum)
			{
				SetBanRoad(pos.x, pos.y);
			}

			int BlockedRoadNum = 0;
			for (int i = 0; i < 4; i++)
			{
				if (isRoadBlocked(i) || isBanRoad(i))
					BlockedRoadNum++;
			}

			if (BlockedRoadNum >= 3)
			{
				SetBanRoad(pos.x, pos.y);
			}
		}
		//막다른 길이거나 / 스택 쌓아서 일정정도가 넘으면 밴

		/*
		{
			int SearchDirection = -1;
			int SearchGap = 0;
			if ((ObjPool->Player.GetPosition().y < pos.y && ObjPool->Player.GetPosition().y + 7 >= pos.y && pos.x == ObjPool->Player.GetPosition().x))
			{
				SearchDirection = UP;
				SearchGap = pos.y - ObjPool->Player.GetPosition().y;
			}
			else if ((ObjPool->Player.GetPosition().y > pos.y && ObjPool->Player.GetPosition().y - 7 <= pos.y && pos.x == ObjPool->Player.GetPosition().x))
			{
				SearchDirection = DOWN;
				SearchGap = pos.y - ObjPool->Player.GetPosition().y;
			}
			else if ((ObjPool->Player.GetPosition().x < pos.x && ObjPool->Player.GetPosition().x + 7 >= pos.x && pos.y == ObjPool->Player.GetPosition().y))
			{
				SearchDirection = LEFT;
				SearchGap = pos.x - ObjPool->Player.GetPosition().x;
			}
			else if ((ObjPool->Player.GetPosition().x > pos.x && ObjPool->Player.GetPosition().x - 7 <= pos.x && pos.y == ObjPool->Player.GetPosition().y))
			{
				SearchDirection = RIGHT;
				SearchGap = pos.x - ObjPool->Player.GetPosition().x;
			}

			if (SearchGap < 0) SearchGap = -(SearchGap);

			switch (SearchDirection)
			{
			case UP:
				for (int i = 1; i <= SearchGap; i++)
				{
					if (ObjPool->Maps.GetTileID(pos.x, pos.y - i) != FLOOR)
					{
						SearchDirection = -1;
						break;
					}
				}
				break;
			case DOWN:
				for (int i = 1; i <= SearchGap; i++)
				{
					if (ObjPool->Maps.GetTileID(pos.x, pos.y + i) != FLOOR)
					{
						SearchDirection = -1;
						break;
					}
				}
				break;
			case LEFT:
				for (int i = 1; i <= SearchGap; i++)
				{
					if (ObjPool->Maps.GetTileID(pos.x - i, pos.y) != FLOOR)
					{
						SearchDirection = -1;
						break;
					}
				}
				break;
			case RIGHT:
				for (int i = 1; i <= SearchGap; i++)
				{
					if (ObjPool->Maps.GetTileID(pos.x + i, pos.y) != FLOOR)
					{
						SearchDirection = -1;
						break;
					}
				}
				break;
			}

			//여기서부터 
			if (!isAllSearch)
			{
				if (SearchDirection != -1)
				{
					PlayerPos = ObjPool->Player.GetPosition();
					isAllSearch = true;
					isSearch = true;

					SetDirection(SearchDirection);
					if (PathFind(pos, PlayerPos))
					{
						list<POINT>::iterator it;
						it = m_pathList.begin();

						it = m_pathList.erase(it);

						if (SearchGap == 1)
						{
							SetDirection(SearchDirection);

							nowAnimation = ATTACK;
							nowState = ATTACK;
							return;
						}
						else
						{
							nowAnimation = MARKFORFIND;
							nowState = MARKFORFIND;
							return;
						}
					}
					else
					{
						isSearch = false;
					}
				}
			}

			if (isAllSearch)
			{
				if (m_pathList.empty())
				{
					isSearch = true;
					if (PathFind(pos, PlayerPos))
					{
						list<POINT>::iterator it;
						it = m_pathList.begin();

						it = m_pathList.erase(it);
					}
					else
					{
						isSearch = false;
					}
				}

				if (isSearch)
				{
					if (m_pathList.empty())
					{
						isSearch = false;
					}
					else
					{
						if (SearchGap == 1)
						{
							SetDirection(SearchDirection);

							nowAnimation = ATTACK;
							nowState = ATTACK;
							return;
						}

						list<POINT>::iterator it;
						it = m_pathList.begin();

						if (it->x == pos.x && it->y == pos.y - 1)
						{
							it = m_pathList.erase(it);

							SetDirection(UP);

							if (!isRoadBlocked(nowDirection))
							{
								nowAnimation = WALK;
								nowState = WALK;
								return;
							}
						}
						else if (it->x == pos.x && it->y == pos.y + 1)
						{
							it = m_pathList.erase(it);

							SetDirection(DOWN);

							if (!isRoadBlocked(nowDirection))
							{
								nowAnimation = WALK;
								nowState = WALK;
								return;
							}
						}
						else if (it->x == pos.x - 1 && it->y == pos.y)
						{
							it = m_pathList.erase(it);

							SetDirection(LEFT);

							if (!isRoadBlocked(nowDirection))
							{
								nowAnimation = WALK;
								nowState = WALK;
								return;
							}
						}
						else if (it->x == pos.x + 1 && it->y == pos.y)
						{
							it = m_pathList.erase(it);

							SetDirection(RIGHT);

							if (!isRoadBlocked(nowDirection))
							{
								nowAnimation = WALK;
								nowState = WALK;
								return;
							}
						}
						else
						{
							isSearch = false;
						}
					}
				}
			}
		}
		*/
		//서치중이면 플레이어에게 간다

		{
			int BlockedRoadNum = 0;
			int BlockedRoad[4] = { 0 };
			for (int i = 0; i < 4; i++)
			{
				if (!isRoadBlocked(i) && !isBanRoad(i) && returnReverseDirection(nowDirection) != i)
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
			if (!isRoadBlocked(returnReverseDirection(nowDirection)))
			{
				if (!(!isRoadBlocked(nowDirection) && isBanRoad(pos.x, pos.y)))
					SetDirection(returnReverseDirection(nowDirection));

				nowAnimation = WALK;
				nowState = WALK;
				ObjPool->debug = 2;
				return;
			}
			else
			{
				int BlockedRoadNum = 0;
				int BlockedRoad[4] = { 0 };
				for (int i = 0; i < 4; i++)
				{
					if (!isRoadBlocked(i))
					{
						BlockedRoad[BlockedRoadNum] = { i };
						BlockedRoadNum++;
					}
				}
				srand((unsigned)time(NULL));
				SetDirection(BlockedRoad[rand() % BlockedRoadNum]);

				nowAnimation = WALK;
				nowState = WALK;
				ObjPool->debug = 3;
				return;
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
		}
		else
		{
			nowAnimation = WALK;
			nowState = WALK;
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

bool Entity::isRoadBlocked()
{
	return isRoadBlocked(nowDirection);
}

bool Entity::isRoadBlocked(int x, int y)
{
	if (ObjPool->Maps.GetTileID(x, y) == FLOOR)
		return false;

	return true;
}

bool Entity::isRoadBlocked(int dire)
{
	switch (dire)
	{
	case UP:
<<<<<<< HEAD
		return isRoadBlocked(pos.x, pos.y - 1);

		break;
	case DOWN:
		return isRoadBlocked(pos.x, pos.y + 1);

		break;
	case LEFT:
		return isRoadBlocked(pos.x - 1, pos.y);

		break;
	case RIGHT:
		return isRoadBlocked(pos.x + 1, pos.y);
=======
		if (ObjPool->Maps.GetTileID(pos.x, pos.y - 1) != NONE && ObjPool->Maps.GetTileID(pos.x, pos.y - 1) != WALL && ObjPool->Maps.GetTileID(pos.x, pos.y - 1) != MENTLE)
			return false;
		
		break;
	case DOWN:
		if (ObjPool->Maps.GetTileID(pos.x, pos.y + 1) != NONE && ObjPool->Maps.GetTileID(pos.x, pos.y + 1) != WALL && ObjPool->Maps.GetTileID(pos.x, pos.y + 1) != MENTLE)
			return false;
		
		break;
	case LEFT:
		if (ObjPool->Maps.GetTileID(pos.x - 1, pos.y) != NONE && ObjPool->Maps.GetTileID(pos.x - 1, pos.y) != WALL && ObjPool->Maps.GetTileID(pos.x - 1, pos.y) != MENTLE)
			return false;

		break;
	case RIGHT:
		if (ObjPool->Maps.GetTileID(pos.x + 1, pos.y) != NONE && ObjPool->Maps.GetTileID(pos.x + 1, pos.y) != WALL && ObjPool->Maps.GetTileID(pos.x + 1, pos.y) != MENTLE)
			return false;
>>>>>>> 03c2574cc853778e0e6192347a15cbd10c81ab21

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

POINT Entity::GetPosition()
{
	return pos;
}

<<<<<<< HEAD
POINT Entity::GetSpawnPosition()
{
	return spawnPosition;
=======
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
>>>>>>> 03c2574cc853778e0e6192347a15cbd10c81ab21
}

void Entity::SetPosition(int x, int y)
{
	this->pos.x = x;
	this->pos.y = y;
}

<<<<<<< HEAD
void Entity::SetSpawnPosition(int x, int y)
{
	spawnPosition = { x,y };
}

=======
>>>>>>> 03c2574cc853778e0e6192347a15cbd10c81ab21
void Entity::SetAnimation(int ani)
{
	nowAnimation = ani;
}

void Entity::SetDirection(int dire)
{
	nowDirection = dire;
}

<<<<<<< HEAD
void Entity::AddHealth(int plus)
=======
void Entity::SetState(int state)
{
	nowState = state;
}

void Entity::PlusHealth(int plus)
>>>>>>> 03c2574cc853778e0e6192347a15cbd10c81ab21
{
	health += plus;
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
	Dealer.Init(hWnd, 0, 0, DEALER);
	Wizard.Init(hWnd, 0, 0, WIZARD);
	Tanker.Init(hWnd, 0, 0, TANKER);
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

	if (pool.empty()) return;

	for (auto it = pool.begin(); it != pool.end(); it++)
	{
		it->Ternimate();
	}

	pool.clear();
}

void Monster::Draw(HDC hMemDC, int x, int y)
{

	if (pool.empty())	//몬스터가 없으면 플레이어만 생성
	{
		ObjPool->Player.Draw(hMemDC, x, y);
		return;
	}

	bool isPlayer = false;

	for (int i = 0; i < MAX_TILE_Y; i++)
	{
		for (int j = 0; j < MAX_TILE_X; j++)
		{
			for (auto it = pool.begin(); it != pool.end(); it++)
				if (it->GetPosition().y == i && it->GetPosition().x == j) it->Draw(hMemDC, x, y);

			if (!isPlayer)
				if (ObjPool->Player.GetPosition().y == i && ObjPool->Player.GetPosition().x == j)
				{
					ObjPool->Player.Draw(hMemDC, x, y);
					isPlayer = true;
				}

			if (ObjPool->Maps.Map[i][j].Tile_ID == TRAP_ScareCrow)
			{
				ObjPool->Maps.Map[i][j].Tile_Sprite.Draw(hMemDC);
			}
		}
	}


	DrawMap(hMemDC, x, y);
}

void Monster::Animation()
{
	if (pool.empty()) return;

	for (auto it = pool.begin(); it != pool.end(); it++)
	{
		it->Animation();
	}
}

void Monster::UpdateState()
{
	if (pool.empty()) return;

	bool isSearch = false;
	for (auto it = pool.begin(); it != pool.end(); it++)
	{
		it->UpdateState();

		if (it->GetAllSearch())
		{
			if (it->GetSearch()) isSearch = true;
		}
	}
	if (!isSearch)
	{
		pool.begin()->SetAllSearch(false);
	}
}

void Monster::AddMonster(int type, int x, int y)
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

void Monster::AddMonster(int type)
{
	AddMonster(type, Dealer.GetSpawnPosition().x, Dealer.GetSpawnPosition().y);
}

void Monster::CheckHealth()
{
	if (pool.empty()) return;

	for (auto it = pool.begin(); it != pool.end();)
	{
		if (it->isDead())
		{
   			it->Ternimate();
			it = pool.erase(it);

			if (pool.empty()) return;
		}
		else
		{
			it++;
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

			ObjPool->Gdi.Text(hMemDC, ((j - Map_Start_x) - 1) * 80 + Term_x - 40 + 30, ((i - Map_Start_y) - 2) * 80 + Term_y + 90, str, 36);
		}
	}
}