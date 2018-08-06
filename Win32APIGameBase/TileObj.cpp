#include "stdafx.h"
#include "TileObj.h"

void CTile::InitTile(HWND hwnd, int Frame, int ID, LPCWSTR szFileName, std::function<void()> Tile_Function)
{
	Tile_ID = ID;
	Tile_On = true;

	Tile_Sprite.Init(hwnd, 0, 0, 80, 80, Frame, szFileName);

	Tile_Func = Tile_Function;
}

void CTile::DestroyTile(CTile Tile)
{
	Tile.Tile_Sprite.Ternimate();
}

void CMap::InitMap(HWND hwnd)
{
	None.InitTile(hwnd, 1 /*Frame*/, NONE, L"./Image/Tile/None.bmp", [&] {});
	Floor.InitTile(hwnd, 1 /*Frame*/, FLOOR, L"./Image/Tile/Floor.bmp", [&] {});
	Wall.InitTile(hwnd, 1 /*Frame*/, WALL, L"./Image/Tile/Wall.bmp", [&] {});
	Trap_Niddle.InitTile(hwnd, 1 /*Frame*/, TRAP_Niddle, L"./Image/Tile/Niddle.bmp", [&] {});
	Trap_Hole.InitTile(hwnd, 1 /*Frame*/, TRAP_Hole, L"./Image/Tile/Hole.bmp", [&] {});
	Trap_ScareCrow.InitTile(hwnd, 1 /*Frame*/, TRAP_ScareCrow, L"./Image/Tile/Scarecrow.bmp", [&] {});
	Trap_Cunfusion.InitTile(hwnd, 1 /*Frame*/, TRAP_Cunfution, L"./Image/Tile/Cunfusion.bmp", [&] {});
	Trap_Grap.InitTile(hwnd, 1 /*Frame*/, TRAP_Grap, L"./Image/Tile/Grap.bmp", [&] {});

	Brick[UP].Init(hwnd, 0, 0, 80, 80, L"./Image/Tile/Brick_Up.bmp");
	Brick[DOWN].Init(hwnd, 0, 0, 80, 80, L"./Image/Tile/Brick_Down.bmp");
	Brick[LEFT].Init(hwnd, 0, 0, 80, 80, L"./Image/Tile/Brick_Left.bmp");
	Brick[RIGHT].Init(hwnd, 0, 0, 80, 80, L"./Image/Tile/Brick_Right.bmp");
}

void CMap::ResetMap(int Character_x, int Character_y)
{
	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			Map[i][j] = None;
			Map[i][j].Tile_Sprite.SetPosition(j * 80, i * 80);
		}
	}

	Map[Character_x][Character_y] = Floor;
}

void CMap::ActiveTile(int Character_x, int Character_y)
{
	switch (Map[Character_x][Character_y].Tile_ID)
	{
	case NONE:
		None.Tile_Func();
		break;
	case FLOOR:
		Floor.Tile_Func();
		break;
	case WALL:
		Wall.Tile_Func();
		break;
	case TRAP_Niddle:
		Trap_Niddle.Tile_Func();
		break;
	case TRAP_Hole:
		Trap_Hole.Tile_Func();
		break;
	case TRAP_ScareCrow:
		Trap_ScareCrow.Tile_Func();
		break;
	case TRAP_Cunfution:
		Trap_Cunfusion.Tile_Func();
		break;
	case TRAP_Grap:
		Trap_Grap.Tile_Func();
		break;
	}
}

void CMap::SetTileOnMap(CTile Tile, int x, int y)
{
	Map[y][x] = Tile;
	Map[y][x].Tile_Sprite.SetPosition(y * 80, x * 80);
}

void CMap::DrawMap(HDC hMemDC, int x, int y)
{
	int Map_Start_x = x - 9;
	int Map_End_x = x + 9;
	int Map_Start_y = y - 5;
	int Map_End_y = y + 5;

	// TODO : 0에서 루프 종료로 수정
	if (Map_Start_x < 0)
		Map_Start_x = 0;
	if (Map_Start_y < 0)
		Map_Start_y = 0;
	if (Map_End_x > 32)
		Map_End_x = 32;
	if (Map_End_y > 16)
		Map_End_y = 16;

	for (int i = Map_Start_y; i < Map_End_y; i++)
	{
		for (int j = Map_Start_x; j < Map_End_x; j++)
		{
			if (Map[i][j].Tile_ID == Floor.Tile_ID && Map[i - 1][j].Tile_ID != Floor.Tile_ID)
			{
				Map[i - 1][j] = Wall;
				Map[i - 1][j].Tile_Sprite.SetPosition((j - Map_Start_x) * 80, ((i - Map_Start_y) - 1) * 80);
			}
		}
	}

	for (int i = Map_Start_y; i < Map_End_y; i++)
	{
		for (int j = Map_Start_x; j < Map_End_x; j++)
		{
			Map[i][j].Tile_Sprite.SetPosition((j - Map_Start_y) * 80, (i - Map_Start_x) * 80);

			Map[i][j].Tile_Sprite.Draw(hMemDC);
		}
	}

	//DrawBrick(hMemDC, x, y);
}

void CMap::SetBrick(int x, int y)
{
	
}

void CMap::DrawBrick(HDC hMemDC, int x, int y)
{
	int Map_Start_x = x - 9;
	int Map_End_x = x + 9;
	int Map_Start_y = y - 5;
	int Map_End_y = y + 5;

	// TODO : 0에서 루프 종료로 수정
	if (Map_Start_x < 0)
		Map_Start_x = 0;
	if (Map_Start_y < 0)
		Map_Start_y = 0;
	if (Map_End_x > 32)
		Map_End_x = 32;
	if (Map_End_y > 16)
		Map_End_y = 16;

	int Brick_ID;

	for (int i = Map_Start_y; i < Map_End_y; i++)
	{
		for (int j = Map_Start_x; j < Map_End_x; j++)
		{
			
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
	Trap_Grap.DestroyTile(Trap_Grap);
}