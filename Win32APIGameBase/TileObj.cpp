#include "stdafx.h"
#include "TileObj.h"
#include "EntityObj.h"

void CTile::InitTile(HWND hwnd, int Frame, int ID, LPCWSTR szFileName, std::function<void(Entity* ent)> Tile_Function)
{
	Tile_ID = ID;
	Tile_On = true;

	Brick_Up = false;
	Brick_Down = false;
	Brick_Left = false;
	Brick_Right = false;

	if (Tile_ID == TRAP_ScareCrow)
		Tile_Sprite.Init(hwnd, 0, 0, 80, 160, Frame, szFileName);
	else
		Tile_Sprite.Init(hwnd, 0, 0, 80, 80, Frame, szFileName);

	damgeDelay = 0; 
	SpinSpeed = 3;

	Tile_Func = Tile_Function;
}

void CTile::DestroyTile(CTile Tile)
{
	Tile.Tile_Sprite.Ternimate();
}

void CMap::InitMap(HWND hwnd)
{
	None.InitTile(hwnd, 1 /*Frame*/, NONE, L"./Image/Tile/None.bmp", [&](Entity* ent) {});
	Floor.InitTile(hwnd, 1 /*Frame*/, FLOOR, L"./Image/Tile/Floor.bmp", [&](Entity* ent) {});
	Wall.InitTile(hwnd, 1 /*Frame*/, WALL, L"./Image/Tile/Wall.bmp", [&](Entity* ent) {});
	Trap_Niddle.InitTile(hwnd, 1 /*Frame*/, TRAP_Niddle, L"./Image/Tile/Niddle.bmp", [&](Entity* ent) {NiddleActive(ent);});
	Trap_ScareCrow.InitTile(hwnd, 1 /*Frame*/, TRAP_ScareCrow, L"./Image/Tile/Scarecrow_test.bmp", [&](Entity* ent) {ScareCrowActive(ent); });
	Trap_Grab.InitTile(hwnd, 1 /*Frame*/, TRAP_Grab, L"./Image/Tile/Grap.bmp", [&](Entity* ent) {GrabActive(ent);});
	Trap_Cunfusion.InitTile(hwnd, 1 /*Frame*/, TRAP_Cunfusion, L"./Image/Tile/Cunfusion.bmp", [&](Entity* ent) {ConfusionActive(ent); });
	Trap_Hole.InitTile(hwnd, 1 /*Frame*/, TRAP_Hole, L"./Image/Tile/Hole.bmp", [&](Entity* ent) {HoleActive(ent);});

	Brick[UP].Init(hwnd, 0, 0, 80, 80, L"./Image/Tile/Brick_Up.bmp");
	Brick[DOWN].Init(hwnd, 0, 0, 80, 80, L"./Image/Tile/Brick_Down.bmp");
	Brick[LEFT].Init(hwnd, 0, 0, 80, 80, L"./Image/Tile/Brick_Left.bmp");
	Brick[RIGHT].Init(hwnd, 0, 0, 80, 80, L"./Image/Tile/Brick_Right.bmp");
	Brick[SW_LEFT].Init(hwnd, 0, 0, 80, 80, L"./Image/Tile/SubWall_Left.bmp");
	Brick[SW_RIGHT].Init(hwnd, 0, 0, 80, 80, L"./Image/Tile/SubWall_Right.bmp");
}

void CMap::NiddleActive(Entity* ent)
{
	POINT pos = ent->GetPosition();

	if (Map[pos.y][pos.x].Tile_On) //함정이 깔려있으면
	{
		printf("체력 : %d\n", ent->GetHealth());
		ent->PlusHealth(-10);
		printf("체력 : %d\n", ent->GetHealth());
		Map[pos.y][pos.x].Tile_On = false; //재장전 필요한 상태로 변경
	}
}
void CMap::ScareCrowActive(Entity* ent)
{

}

void CMap::GrabActive(Entity* ent)
{

}

void CMap::ConfusionActive(Entity* ent)
{

}

void CMap::HoleActive(Entity* ent)
{
	POINT pos = ent->GetPosition();

	if (Map[pos.y][pos.x].Tile_On) //함정이 깔려있으면
	{
		ent->SetState(INTRAP); //엔티티 상태 인트랩 상태로 변경
		ent->SetAnimation(STAND); //엔티티 서있는 상태로 변경
		Map[pos.y][pos.x].damgeDelay++;
		printf("카운트 : %f\n 속도: %f\n", Map[pos.y][pos.x].damgeDelay, Map[pos.y][pos.x].SpinSpeed);
		if (Map[pos.y][pos.x].damgeDelay >= Map[pos.y][pos.x].SpinSpeed)
		{
			if (ent->GetDirection() != DOWN) //엔티티 돌리기
				ent->SetDirection(ent->GetDirection() + 1);
			else
				ent->SetDirection(UP);


			Map[pos.y][pos.x].SpinSpeed += 0.2; //도는 속도 서서히 낮추기

			if (Map[pos.y][pos.x].SpinSpeed >= 9) //충분히 엔티티가 돌았으면
			{
				ent->Ternimate(); //엔티티 삭제
				Map[pos.y][pos.x].Tile_On = false; //재장전 필요한 상태로 변경
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
			Map[i][j].Tile_Sprite.SetPosition(j * 80, i * 80);
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
	case TRAP_Cunfusion:
		Trap_Cunfusion.Tile_Func(ent);
		break;
	case TRAP_Grab:
		Trap_Grab.Tile_Func(ent);
		break;
	}
}

void CMap::SetTileOnMap(CTile Tile, int x, int y)
{
	Map[y][x] = Tile;
	Map[y][x].Tile_Sprite.SetPosition(x * 80, y * 80);
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
				Map[i - 1][j].Tile_Sprite.SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 40, ((i - Map_Start_y) - 2) * 80 + Term_y - 40);
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
				ObjPool->Maps.Floor.Tile_Sprite.SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 40, ((i - Map_Start_y) - 1) * 80 + Term_y - 40);
				ObjPool->Maps.Floor.Tile_Sprite.Draw(hMemDC);
				Map[i][j].Tile_Sprite.SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 40, ((i - Map_Start_y) - 2) * 80 + Term_y - 40);
				continue;
			}

			Map[i][j].Tile_Sprite.SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 40, ((i - Map_Start_y) - 1) * 80 + Term_y - 40);

			Map[i][j].Tile_Sprite.Draw(hMemDC);
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

			Brick[UP].SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 40, ((i - Map_Start_y) - 1) * 80 + Term_y - 40);
			Brick[LEFT].SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 40, ((i - Map_Start_y) - 1) * 80 + Term_y - 40);
			Brick[RIGHT].SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 40, ((i - Map_Start_y) - 1) * 80 + Term_y - 40);
			Brick[DOWN].SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 40, ((i - Map_Start_y) - 1) * 80 + Term_y - 40);
			Brick[SW_LEFT].SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 40, ((i - Map_Start_y) - 1) * 80 + Term_y - 40);
			Brick[SW_RIGHT].SetPosition(((j - Map_Start_x) - 1) * 80 + Term_x - 40, ((i - Map_Start_y) - 1) * 80 + Term_y - 40);

			if (Map[i][j].Brick_Up)
				Brick[UP].Draw(hMemDC);
			if (Map[i][j].Brick_Left)
				Brick[LEFT].Draw(hMemDC);
			if (Map[i][j].Brick_Right)
				Brick[RIGHT].Draw(hMemDC);
			if (Map[i][j].Brick_Down)
				Brick[DOWN].Draw(hMemDC);
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
}

int CMap::GetTileID(int x, int y)
{
	return Map[y][x].Tile_ID;
}