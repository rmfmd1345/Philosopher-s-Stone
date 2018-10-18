#include "stdafx.h"
#include "TileObj.h"
#include "EntityObj.h"

void CTile::InitTile(HWND hwnd, int Frame, int ID, int MoveID, std::function<void(Entity* ent)> Tile_Function)
{
	Tile_ID = ID;
	Tile_isCanMove = MoveID;
	Tile_On = true;

	Brick_Up = false;
	Brick_Down = false;
	Brick_Left = false;
	Brick_Right = false;

	switch (Tile_ID)
	{
	case NONE:
		Tile_Sprite_On.Init(hwnd, 0, 0, 80, 80, Frame, L"./Image/Tile/None.bmp");
		break;
	case FLOOR:
		Tile_Sprite_On.Init(hwnd, 0, 0, 80, 80, Frame, L"./Image/Tile/Floor.bmp");
		break;
	case WALL:
		Tile_Sprite_On.Init(hwnd, 0, 0, 80, 80, Frame, L"./Image/Tile/Wall.bmp");
		Tile_Sprite_Off.Init(hwnd, 0, 0, 80, 80, Frame, L"./Image/Tile/Wall.bmp");
		break;
	case TRAP_Niddle:
		Tile_Sprite_On.Init(hwnd, 0, 0, 80, 80, Frame, L"./Image/Tile/Niddle.bmp");
		Tile_Sprite_Off.Init(hwnd, 0, 0, 80, 80, Frame, L"./Image/Tile/Niddle_off.bmp");
		break;
	case TRAP_ScareCrow:
		Tile_Sprite_On.Init(hwnd, 0, 0, 80, 160, Frame, L"./Image/Tile/Scarecrow.bmp");
		Tile_Sprite_Off.Init(hwnd, 0, 0, 80, 160, Frame, L"./Image/Tile/Scarecrow_off.bmp");
		break;
	case TRAP_Grab:
		Ani_Trap[UP].Init(hwnd, 0, 0, 960, 240, Frame, L"./Image/Tile/hook_ani_up.bmp");
		Ani_Trap[DOWN].Init(hwnd, 0, 0, 960, 240, Frame, L"./Image/Tile/hook_ani_down.bmp");
		Ani_Trap[LEFT].Init(hwnd, 0, 0, 960, 240, Frame, L"./Image/Tile/hook_ani_left.bmp");
		Ani_Trap[RIGHT].Init(hwnd, 0, 0, 960, 240, Frame, L"./Image/Tile/hook_ani_right.bmp");
		break;
	case TRAP_GrabArea:
		Tile_Sprite_On.Init(hwnd, 0, 0, 80, 80, Frame, L"./Image/Tile/GrabArea.bmp");
		break;
	case TRAP_Confusion:
		Tile_Sprite_On.Init(hwnd, 0, 0, 80, 80, Frame, L"./Image/Tile/Confusion.bmp");
		Tile_Sprite_Off.Init(hwnd, 0, 0, 80, 80, Frame, L"./Image/Tile/Confusion_off.bmp");
		break;
	case TRAP_Hole:
		Tile_Sprite_On.Init(hwnd, 0, 0, 80, 80, Frame, L"./Image/Tile/Hole.bmp");
		Tile_Sprite_Off.Init(hwnd, 0, 0, 80, 80, Frame, L"./Image/Tile/Hole_off.bmp");
		break;
	case SKILL_Barricade:
		Ani_Trap[UP].Init(hwnd, 0, 0, 80, 160, Frame, L"./Image/Tile/Barricade_Up.bmp");
		Ani_Trap[DOWN].Init(hwnd, 0, 0, 80, 160, Frame, L"./Image/Tile/Barricade_Down.bmp");
		Ani_Trap[LEFT].Init(hwnd, 0, 0, 80, 160, Frame, L"./Image/Tile/Barricade_Left.bmp");
		Ani_Trap[RIGHT].Init(hwnd, 0, 0, 80, 160, Frame, L"./Image/Tile/Barricade_Right.bmp");
		hp = 3;
		break;
	}
	Ani_SelectedArea.Init(hwnd, 0, 0, 240, 240, 1, L"./Image/Tile/tileselect.bmp");

	stateFrame = 1;
	damgeDelay = 0;
	SpinSpeed = 3;
	repairGage = 0;
	TrapHp = 60;
	stunTime = 100;

	Tile_Func = Tile_Function;
}

void CTile::DestroyTile(CTile Tile)
{
	Tile.Tile_Sprite_On.Ternimate();
}

void CMap::InitMap(HWND hwnd)
{
	None.InitTile(hwnd, 1 /*Frame*/, NONE, false, [&](Entity* ent) {});
	Floor.InitTile(hwnd, 1 /*Frame*/, FLOOR, true, [&](Entity* ent) {});
	Wall.InitTile(hwnd, 1 /*Frame*/, WALL, false, [&](Entity* ent) {});
	Trap_Niddle.InitTile(hwnd, 1 /*Frame*/,TRAP_Niddle, true, [&](Entity* ent) {NiddleActive(ent);});
	Trap_ScareCrow.InitTile(hwnd, 1 /*Frame*/, TRAP_ScareCrow, false, [&](Entity* ent) {ScareCrowActive(ent); });
	Trap_Grab.InitTile(hwnd, 4 /*Frame*/, TRAP_Grab, true, [&](Entity* ent) {});
	Trap_GrabArea.InitTile(hwnd, 1 /*Frame*/, TRAP_GrabArea, true, [&](Entity* ent) {GrabActive(ent);});
	Trap_Cunfusion.InitTile(hwnd, 1 /*Frame*/, TRAP_Confusion, true, [&](Entity* ent) {ConfusionActive(ent); });
	Trap_Hole.InitTile(hwnd, 1 /*Frame*/, TRAP_Hole, true, [&](Entity* ent) {HoleActive(ent);});
	Skill_Barricade.InitTile(hwnd, 1 /*Frame*/, SKILL_Barricade, false, [&](Entity* ent) {});
	Barricade_Health_UI.Init(hwnd, 0, 0, 20, 20, L"./Image/UI/Ingame/heart.bmp");

	//ingameUI_TrapArea.Init(hwnd, 0, 0, 960, 240, L"./Image/Tile/tileselect.bmp");
	ingameUI_TrapHpBar_edge.Init(hwnd, 0, 0, 60, 14, L"./Image/UI/Ingame/bluebar_edge.bmp");
	ingameUI_TrapHpBar_fill.Init(hwnd, 0, 0, 60, 14, L"./Image/UI/Ingame/bluebar_fill.bmp");

	Brick[B_UP].Init(hwnd, 0, 0, 80, 80, L"./Image/Tile/Brick_Up.bmp");
	Brick[B_DOWN].Init(hwnd, 0, 0, 80, 80, L"./Image/Tile/Brick_Down.bmp");
	Brick[B_LEFT].Init(hwnd, 0, 0, 80, 80, L"./Image/Tile/Brick_Left.bmp");
	Brick[B_RIGHT].Init(hwnd, 0, 0, 80, 80, L"./Image/Tile/Brick_Right.bmp");
	Brick[SW_LEFT].Init(hwnd, 0, 0, 80, 80, L"./Image/Tile/SubWall_Left.bmp");
	Brick[SW_RIGHT].Init(hwnd, 0, 0, 80, 80, L"./Image/Tile/SubWall_Right.bmp");
}

void CMap::NiddleActive(Entity* ent)
{
	POINT pos = ent->GetPosition();

	if (Map[pos.y][pos.x].Tile_On) //함정이 깔려있으면
	{
		printf("체력 : %d\n", ent->GetHealth());
		ent->AddHealth(-1);
		printf("체력 : %d\n", ent->GetHealth());
		Map[pos.y][pos.x].Tile_On = false; //재장전 필요한 상태로 변경
	}
}

void CMap::ScareCrowActive(Entity* ent)
{

}

void CMap::GrabActive(Entity* ent)
{
	POINT pos = ent->GetPosition();
	POINT grabPos; //갈고리가 설치된 위치의 좌표
	grabPos.x = Map[pos.y][pos.x].Grab_POS.x;
	grabPos.y = Map[pos.y][pos.x].Grab_POS.y;

	if (Map[grabPos.y][grabPos.x].Tile_On && ent->GetState() != WALK) //쓸데없이 코드가 길다. 나중에 줄여야겠다
	{
		ent->SetState(INTRAP); //엔티티 인트랩 상태로 변경
		ent->SetAnimation(STAND); //엔티티 서있는 상태로 변경

			if (grabPos.y == pos.y + 1) //엔티티가 갈고리 위쪽에 있을 떄
			{
				Map[grabPos.y][grabPos.x].nowTrapDirection = UP;
				if (Map[grabPos.y][grabPos.x].stateFrame <= 40) //10, 20, 30, 40,
				{
					if (Map[grabPos.y][grabPos.x].stateFrame % 10 == 0)
						Map[grabPos.y][grabPos.x].Ani_Trap[UP].NextFrameSprite_Trap();

					Map[grabPos.y][grabPos.x].stateFrame++;
				}
				else
				{
					Map[grabPos.y][grabPos.x].stateFrame = 1;
					//Map[grabPos.y][grabPos.x].Ani_Trap[UP].SetCurrentFrame(0);
					Map[grabPos.y][grabPos.x].Tile_On = false; //재장전 필요한 상태로 변경
					ent->SetPosition(Map[pos.y][pos.x].Grab_POS.x, Map[pos.y][pos.x].Grab_POS.y);
					ent->SetState(FINDWAY);
					ent->AddHealth(-1);
				}
				return;
			}
			if (grabPos.y == pos.y - 1) //엔티티가 갈고리 아래쪽에 있을 떄
			{
				Map[grabPos.y][grabPos.x].nowTrapDirection = DOWN;
				if (Map[grabPos.y][grabPos.x].stateFrame <= 40)
				{
					if (Map[grabPos.y][grabPos.x].stateFrame % 10 == 0)
						Map[grabPos.y][grabPos.x].Ani_Trap[DOWN].NextFrameSprite_Trap();

					Map[grabPos.y][grabPos.x].stateFrame++;
				}
				else
				{
					Map[grabPos.y][grabPos.x].stateFrame = 1;
					Map[grabPos.y][grabPos.x].Tile_On = false; //재장전 필요한 상태로 변경
					ent->SetPosition(Map[pos.y][pos.x].Grab_POS.x, Map[pos.y][pos.x].Grab_POS.y);
					ent->SetState(FINDWAY);
					ent->AddHealth(-1);
				}
				return;
			}
			if (grabPos.x == pos.x + 1) //엔티티가 갈고리 왼쪽에 있을 때
			{
				Map[grabPos.y][grabPos.x].nowTrapDirection = LEFT;
				if (Map[grabPos.y][grabPos.x].stateFrame <= 40)
				{
					if (Map[grabPos.y][grabPos.x].stateFrame % 10 == 0)
						Map[grabPos.y][grabPos.x].Ani_Trap[LEFT].NextFrameSprite_Trap();

					Map[grabPos.y][grabPos.x].stateFrame++;
				}
				else
				{
					Map[grabPos.y][grabPos.x].stateFrame = 1;
					Map[grabPos.y][grabPos.x].Tile_On = false; //재장전 필요한 상태로 변경
					ent->SetPosition(Map[pos.y][pos.x].Grab_POS.x, Map[pos.y][pos.x].Grab_POS.y);
					ent->SetState(FINDWAY);
					ent->AddHealth(-1);
				}
				return;
			}
			if (grabPos.x == pos.x - 1) //엔티티가 갈고리 오른쪽에 있을 떄
			{
				Map[grabPos.y][grabPos.x].nowTrapDirection = RIGHT;
				if (Map[grabPos.y][grabPos.x].stateFrame <= 40)
				{
					if (Map[grabPos.y][grabPos.x].stateFrame % 10 == 0)
						Map[grabPos.y][grabPos.x].Ani_Trap[RIGHT].NextFrameSprite_Trap();

					Map[grabPos.y][grabPos.x].stateFrame++;
				}
				else
				{
					Map[grabPos.y][grabPos.x].stateFrame = 1;
					Map[grabPos.y][grabPos.x].Tile_On = false; //재장전 필요한 상태로 변경
					ent->SetPosition(Map[pos.y][pos.x].Grab_POS.x, Map[pos.y][pos.x].Grab_POS.y);
					ent->SetState(FINDWAY);
					ent->AddHealth(-1);
				}
				return;
			}
	}
}

void CMap::ConfusionActive(Entity* ent)
{
	POINT pos = ent->GetPosition();

	if (Map[pos.y][pos.x].Tile_On && ent->GetState() != WALK) //함정이 깔려있으면 //엔티티가 걷는 중이 아니면
	{
		ent->SetState(CONFUSE); //엔티티 혼란 상태로 변경
		Map[pos.y][pos.x].stateFrame++;
		if (Map[pos.y][pos.x].stateFrame >= Map[pos.y][pos.x].stunTime)
		{
			Map[pos.y][pos.x].stateFrame = 0;
			ent->SetState(FINDWAY); //엔티티 혼란 상태로 변경
			Map[pos.y][pos.x].Tile_On = false; //재장전 필요한 상태로 변경
		}
	}
}

void CMap::HoleActive(Entity* ent)
{
	POINT pos = ent->GetPosition();
	
	if (Map[pos.y][pos.x].Tile_On && ent->GetState() != WALK) //함정이 깔려있으면 //엔티티가 걷는 중이 아니면
	{
		ent->SetState(INTRAP); //엔티티 인트랩 상태로 변경
		ent->SetAnimation(STAND); //엔티티 서있는 상태로 변경
		Map[pos.y][pos.x].damgeDelay++;
		printf("카운트 : %f\n 속도: %f\n", Map[pos.y][pos.x].damgeDelay, Map[pos.y][pos.x].SpinSpeed);

		if (Map[pos.y][pos.x].damgeDelay >= Map[pos.y][pos.x].SpinSpeed)
		{
			if (ent->GetDirection() != RIGHT) //엔티티 돌리기
				ent->SetDirection(ent->GetDirection() + 1);
			else
				ent->SetDirection(UP);

			Map[pos.y][pos.x].SpinSpeed += 0.2; //도는 속도 서서히 낮추기

			if (Map[pos.y][pos.x].SpinSpeed >= 9) //충분히 엔티티가 돌았으면
			{
				ent->AddHealth(-5); //엔티티 삭제
				Map[pos.y][pos.x].Tile_On = false; //재장전 필요한 상태로 변경
				Map[pos.y][pos.x].SpinSpeed = 3;
			}
			Map[pos.y][pos.x].damgeDelay = 0;
		}
	}
}

void CMap::ResetMap(int Character_x, int Character_y)
{
	for (int i = 0; i < MAX_TILE_Y; i++)
	{
		for (int j = 0; j < MAX_TILE_X; j++)
		{
			Map[i][j] = None;
			Map[i][j].Tile_Sprite_On.SetPosition(j * 80, i * 80);
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < MAX_TILE_X; j++)
		{
			Map[i][j].Tile_ID = MENTLE;
		}
	}

	for (int i = 0; i < MAX_TILE_Y; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			Map[i][j].Tile_ID = MENTLE;
		}
	}

	for (int i = MAX_TILE_Y - 2; i < MAX_TILE_Y; i++)
	{
		for (int j = 0; j < MAX_TILE_X; j++)
		{
			Map[i][j].Tile_ID = MENTLE;
		}
	}

	for (int i = 0; i < MAX_TILE_Y; i++)
	{
		for (int j = MAX_TILE_X - 2; j < MAX_TILE_X; j++)
		{
			Map[i][j].Tile_ID = MENTLE;
		}
	}

	Map[Character_y][Character_x] = Floor;
}

void CMap::ActiveTile(Entity* ent)
{
	POINT pos;
	pos = ent->GetPosition();
	switch (Map[pos.y][pos.x].Tile_ID)
	{
	case NONE:
		None.Tile_Func(ent);
		break;
	case FLOOR:
		Floor.Tile_Func(ent);
		break;
	case WALL:
		Wall.Tile_Func(ent);
		break;
	case TRAP_Niddle:
		Trap_Niddle.Tile_Func(ent);
		break;
	case TRAP_Hole:
		Trap_Hole.Tile_Func(ent);
		break;
	case TRAP_ScareCrow:
		Trap_ScareCrow.Tile_Func(ent);
		break;
	case TRAP_Confusion:
		Trap_Cunfusion.Tile_Func(ent);
		break;
	case TRAP_Grab:
		Trap_Grab.Tile_Func(ent);
		break;
	case TRAP_GrabArea:
		Trap_GrabArea.Tile_Func(ent);
		break;
	}
}

void CMap::SetTileOnMap(CTile Tile, int x, int y)
{
	Map[y][x] = Tile;
	Map[y][x].Tile_Sprite_On.SetPosition(x * 80, y * 80);
}

int CMap::SetTrapOnMap(CTile Tile, int x, int y)
{
	if (Map[y][x].Tile_ID != FLOOR) return false;

	Map[y][x] = Tile;
	Map[y][x].Tile_Sprite_On.SetPosition(x * 80, y * 80);
	return true;
}

bool CMap::isCanTrapSet(int x, int y)
{
	if (Map[y][x].Tile_ID != FLOOR) return false;
	return true;
}

void CMap::DrawMap(HDC hMemDC, int x, int y)
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
	int Map_End_y = y + 6;

	int Term_x = ObjPool->Player.GetWalkTerm().x, Term_y = ObjPool->Player.GetWalkTerm().y;

	for (int i = Map_Start_y; i < Map_End_y; i++)
	{
		for (int j = Map_Start_x; j < Map_End_x; j++)
		{
			if (Map[i][j].Tile_ID == FLOOR && Map[i - 1][j].Tile_ID == NONE)
			{
				if (i < 1 || j < 1 || i >= MAX_TILE_Y || j >= MAX_TILE_X)
					continue;

				Map[i - 1][j] = Wall;
				Map[i - 1][j].Tile_Sprite_On.SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 40, ((i - Map_Start_y) - 2) * 80 + Term_y - 40);
			}
		}
	}

	for (int i = Map_Start_y; i < Map_End_y; i++)
	{
		for (int j = Map_Start_x; j < Map_End_x; j++)
		{
			if (i < 1 || j < 1 || i >= MAX_TILE_Y || j >= MAX_TILE_X)
				continue;

			if (Map[i][j].Tile_ID == TRAP_ScareCrow)
			{
				if (Map[i][j].Tile_On)
					Map[i][j].Tile_Sprite_On.SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 40, ((i - Map_Start_y) - 2) * 80 + Term_y - 40);
				else
					Map[i][j].Tile_Sprite_Off.SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 40, ((i - Map_Start_y) - 2) * 80 + Term_y - 40);
			}
			else if (Map[i][j].Tile_ID == TRAP_Grab)
			{
				ObjPool->Maps.Floor.Tile_Sprite_On.SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 40, ((i - Map_Start_y) - 1) * 80 + Term_y - 40);
				ObjPool->Maps.Floor.Tile_Sprite_On.Draw(hMemDC);
				Map[i][j].Ani_Trap[Map[i][j].nowTrapDirection].SetPosition(((j - Map_Start_x) - 2) * 80 + Term_x - 40, ((i - Map_Start_y) - 2) * 80 + Term_y - 40);
				Map[i][j].Ani_Trap[Map[i][j].nowTrapDirection].Draw(hMemDC);
			}
			else if (Map[i][j].Tile_ID == SKILL_Barricade)
			{
				Map[i][j].Ani_Trap[Map[i][j].nowTrapDirection].SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 40, ((i - Map_Start_y) - 2) * 80 + Term_y - 40);
				Map[i][j].Ani_Trap[Map[i][j].nowTrapDirection].Draw(hMemDC);
				for (int k = 0; k < Map[i][j].hp; k++)
				{
					Barricade_Health_UI.SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - (20 * Map[i][j].hp / 2) + (20 * k), ((i - Map_Start_y) - 1) * 80 + Term_y - 40 - 20);
					Barricade_Health_UI.Draw(hMemDC);
				}
			}
			else
			{
				if (Map[i][j].Tile_On)
				{
					Map[i][j].Tile_Sprite_On.SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 40, ((i - Map_Start_y) - 1) * 80 + Term_y - 40);
					Map[i][j].Tile_Sprite_On.Draw(hMemDC);
				}
				else
				{
					Map[i][j].Tile_Sprite_Off.SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 40, ((i - Map_Start_y) - 1) * 80 + Term_y - 40);
					Map[i][j].Tile_Sprite_Off.Draw(hMemDC);
				}
			}
		}
	}
}

void CMap::DrawTileUI(HDC hMemDC, int x, int y)
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
	int Map_End_y = y + 6;

	int Term_x = ObjPool->Player.GetWalkTerm().x, Term_y = ObjPool->Player.GetWalkTerm().y;
	for (int i = Map_Start_y; i < Map_End_y; i++)
	{
		for (int j = Map_Start_x; j < Map_End_x; j++)
		{
			if (i < 1 || j < 1 || i >= MAX_TILE_Y || j >= MAX_TILE_X)
				continue;

			//====체력바 UI====
			if (Map[i][j].Tile_On == false && Map[i][j].Tile_ID != TRAP_Hole) //만약 함정이 고장났다면
			{
				ingameUI_TrapHpBar_fill.SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 30, ((i - Map_Start_y) - 1) * 80 + Term_y + 15);
				ingameUI_TrapHpBar_edge.SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 30, ((i - Map_Start_y) - 1) * 80 + Term_y + 15);

				ingameUI_TrapHpBar_fill.SetDrawArea(Map[i][j].repairGage, 14);
				ingameUI_TrapHpBar_edge.SetDrawArea(60, 14);

				ingameUI_TrapHpBar_fill.Draw(hMemDC);
				ingameUI_TrapHpBar_edge.Draw(hMemDC);
			}
			//====함정 선택 UI====
			if (Map[i][j].Tile_SelectArea == true)
			{
				//ObjPool->Maps.Floor.Tile_Sprite_On.SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 40, ((i - Map_Start_y) - 1) * 80 + Term_y - 40);
				//ObjPool->Maps.Floor.Tile_Sprite_On.Draw(hMemDC);
				Map[i][j].Ani_SelectedArea.SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 120, ((i - Map_Start_y) - 1) * 80 + Term_y - 120);
				Map[i][j].Ani_SelectedArea.Draw(hMemDC);
			}
		}
	}
}

void CMap::SetBrick(int x, int y)
{
	if (Map[y][x].Tile_ID == WALL && (Map[y - 1][x].Tile_ID == NONE || Map[y - 1][x].Tile_ID == MENTLE))
		Map[y][x].Brick_Up = true;
	if (Map[y][x].Tile_ID != NONE && (Map[y + 1][x].Tile_ID == NONE || Map[y + 1][x].Tile_ID == WALL))
		Map[y][x].Brick_Down = true;
	if (Map[y][x].Tile_ID == NONE && Map[y][x + 1].Tile_ID != NONE)
		Map[y][x].Brick_Left = true;
	if (Map[y][x].Tile_ID == NONE && Map[y][x - 1].Tile_ID != NONE)
		Map[y][x].Brick_Right = true;
	if ((Map[y][x].Tile_ID != NONE && Map[y][x].Tile_ID != WALL) && (Map[y + 1][x].Tile_ID == WALL && Map[y][x - 1].Tile_ID == WALL))
	{
		Map[y][x - 1].Brick_Left = true;
		Map[y + 1][x - 1].SubWall_Left = true;
	}
	if ((Map[y][x].Tile_ID != NONE && Map[y][x].Tile_ID != WALL) && (Map[y + 1][x].Tile_ID == WALL && Map[y][x + 1].Tile_ID == WALL))
	{
		Map[y][x + 1].Brick_Right = true;
		Map[y + 1][x + 1].SubWall_Right = true;
	}
	if (Map[y][x].Tile_ID == WALL && (Map[y + 1][x].Tile_ID != NONE && Map[y + 1][x].Tile_ID != WALL) && Map[y][x - 1].Tile_ID == FLOOR && Map[y + 1][x - 1].Tile_ID == NONE)
		Map[y][x].Brick_Right = true;
	if (Map[y][x].Tile_ID == WALL && (Map[y + 1][x].Tile_ID != NONE && Map[y + 1][x].Tile_ID != WALL) && Map[y][x + 1].Tile_ID == FLOOR && Map[y + 1][x + 1].Tile_ID == NONE)
		Map[y][x].Brick_Left = true;
	if (Map[y][x].Tile_ID != MENTLE && Map[y + 1][x].Tile_ID == MENTLE)
		Map[y][x].Brick_Down = true;
}

void CMap::DrawBrick(HDC hMemDC, int x, int y)
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
	int Map_End_y = y + 6;

	int Term_x = ObjPool->Player.GetWalkTerm().x, Term_y = ObjPool->Player.GetWalkTerm().y;

	for (int i = Map_Start_y; i < Map_End_y; i++)
	{
		for (int j = Map_Start_x; j < Map_End_x; j++)
		{
			if (i < 1 || j < 1 || i >= MAX_TILE_Y || j >= MAX_TILE_X)
				continue;

			Map[i][j].Brick_Up = false;
			Map[i][j].Brick_Down = false;
			Map[i][j].Brick_Left = false;
			Map[i][j].Brick_Right = false;
			Map[i][j].SubWall_Left = false;
			Map[i][j].SubWall_Right = false;
		}
	}

	for (int i = Map_Start_y; i < Map_End_y; i++)
	{
		for (int j = Map_Start_x; j < Map_End_x; j++)
		{
			if (i < 1 || j < 1 || i >= MAX_TILE_Y - 1 || j >= MAX_TILE_X - 1)
				continue;

			SetBrick(j, i);
		}
	}

	for (int i = Map_Start_y; i < Map_End_y; i++)
	{
		for (int j = Map_Start_x; j < Map_End_x; j++)
		{
			if (i < 1 || j < 1 || i >= MAX_TILE_Y || j >= MAX_TILE_X)
				continue;

			Brick[B_UP].SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 40, ((i - Map_Start_y) - 1) * 80 + Term_y - 40);
			Brick[B_LEFT].SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 40, ((i - Map_Start_y) - 1) * 80 + Term_y - 40);
			Brick[B_RIGHT].SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 40, ((i - Map_Start_y) - 1) * 80 + Term_y - 40);
			Brick[B_DOWN].SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 40, ((i - Map_Start_y) - 1) * 80 + Term_y - 40);
			Brick[SW_LEFT].SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 40, ((i - Map_Start_y) - 1) * 80 + Term_y - 40);
			Brick[SW_RIGHT].SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 40, ((i - Map_Start_y) - 1) * 80 + Term_y - 40);

			if (Map[i][j].Brick_Up)
				Brick[B_UP].Draw(hMemDC);
			if (Map[i][j].Brick_Left)
				Brick[B_LEFT].Draw(hMemDC);
			if (Map[i][j].Brick_Right)
				Brick[B_RIGHT].Draw(hMemDC);
			if (Map[i][j].Brick_Down)
				Brick[B_DOWN].Draw(hMemDC);
			if (Map[i][j].SubWall_Left)
				Brick[SW_LEFT].Draw(hMemDC);
			if (Map[i][j].SubWall_Right)
				Brick[SW_RIGHT].Draw(hMemDC);
		}
	}
}

void CMap::DestroyMap()
{
	None.DestroyTile(None);
	Floor.DestroyTile(Floor);
	Wall.DestroyTile(Wall);
	Trap_Niddle.DestroyTile(Trap_Niddle);
	Trap_Hole.DestroyTile(Trap_Hole);
	Trap_ScareCrow.DestroyTile(Trap_ScareCrow);
	Trap_Cunfusion.DestroyTile(Trap_Cunfusion);
	Trap_Grab.DestroyTile(Trap_Grab);
	Skill_Barricade.DestroyTile(Skill_Barricade);
}

int CMap::GetTileID(int x, int y)
{
	return Map[y][x].Tile_ID;
}

int CMap::GetTileMoveID(int x, int y)
{
	return Map[y][x].Tile_isCanMove;
}

bool CMap::CheckTrap(int diraction, POINT pos)
{
	switch (diraction)
	{
	case LEFT:
		if (Map[pos.y][pos.x - 1].Tile_ID != NONE && Map[pos.y][pos.x - 1].Tile_ID != WALL && Map[pos.y][pos.x - 1].Tile_ID != FLOOR && Map[pos.y][pos.x - 1].Tile_ID != SKILL_Barricade)
			return true;
		break;
	case RIGHT:
		if (Map[pos.y][pos.x + 1].Tile_ID != NONE && Map[pos.y][pos.x + 1].Tile_ID != WALL && Map[pos.y][pos.x + 1].Tile_ID != FLOOR && Map[pos.y][pos.x + 1].Tile_ID != SKILL_Barricade)
			return true;
		break;
	case UP:
		if (Map[pos.y - 1][pos.x].Tile_ID != NONE && Map[pos.y - 1][pos.x].Tile_ID != WALL && Map[pos.y - 1][pos.x].Tile_ID != FLOOR && Map[pos.y - 1][pos.x].Tile_ID != SKILL_Barricade)
			return true;
		break;
	case DOWN:
		if (Map[pos.y + 1][pos.x].Tile_ID != NONE && Map[pos.y + 1][pos.x].Tile_ID != WALL && Map[pos.y + 1][pos.x].Tile_ID != FLOOR && Map[pos.y + 1][pos.x].Tile_ID != SKILL_Barricade)
			return true;
		break;
	}

	return false;
}
