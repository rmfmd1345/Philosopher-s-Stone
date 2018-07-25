#include "stdafx.h"
#include "TileObj.h"

void CTile::InitTile(HWND hwnd, int ID, LPCWSTR szFileName, std::function<void()> Tile_Function)
{
	Tile_ID = ID;
	Tile_On = true;

	WCHAR str[128];
	wsprintf(str, szFileName);
	Tile_Bitmap.Init(hwnd, 0, 0, 80, 80, szFileName);

	Tile_Func = Tile_Function;
}

void CTile::DestroyTile(CTile Tile)
{
	Tile.Tile_Bitmap.Ternimate();
}

void CMap::InitMap(HWND hwnd)
{
	None.InitTile(hwnd, NONE, L"./Image/", [&] {});
	Floor.InitTile(hwnd, FLOOR, L"./Image/", [&] {});
	Wall.InitTile(hwnd, WALL, L"./Image/", [&] {});
	Trap_Niddle.InitTile(hwnd, TRAP_Niddle, L"./Image/", [&] {});
	Trap_Hole.InitTile(hwnd, TRAP_Hole, L"./Image/", [&] {});
	Trap_ScareCrow.InitTile(hwnd, TRAP_ScareCrow, L"./Image/", [&] {});
	Trap_Cunfution.InitTile(hwnd, TRAP_Cunfution, L"./Image/", [&] {});
	Trap_Grap.InitTile(hwnd, TRAP_Grap, L"./Image/", [&] {});

	Brick[UP].Init(hwnd, 0, 0, 80, 80, L"./Image/");
	Brick[DOWN].Init(hwnd, 0, 0, 80, 80, L"./Image/");
	Brick[LEFT].Init(hwnd, 0, 0, 80, 80, L"./Image/");
	Brick[RIGHT].Init(hwnd, 0, 0, 80, 80, L"./Image/");
}

void CMap::ResetMap()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Map[i][j] = None;
		}
	}

	//플레이어 위치에 바닥 설정
}

void CMap::ActiveTile()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			switch (Map[i][j].Tile_ID)
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
				Trap_Cunfution.Tile_Func();
				break;
			case TRAP_Grap:
				Trap_Grap.Tile_Func();
				break;
			}
		}
	}
}

void CMap::SetTileOnMap(CTile Tile, int x, int y)
{
	Map[x][y] = Tile;
}

void CMap::DrawMap() // 플레이어 기준으로 일정 타일만 출력
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			switch (Map[i][j].Tile_ID)
			{
			case NONE:
				
				break;
			case FLOOR:

				break;
			case WALL:

				break;
			case TRAP_Niddle:

				break;
			case TRAP_Hole:

				break;
			case TRAP_ScareCrow:

				break;
			case TRAP_Cunfution:

				break;
			case TRAP_Grap:

				break;
			}
		}
	}
}

void CMap::DrawBrick()
{
	// 벽 위에 벽돌 출력
	// 바닥 아래에 벽돌 출력
	// 길 양 옆에 벽돌 출력
}

void CMap::DestroyMap()
{
	None.DestroyTile(None);
	Floor.DestroyTile(Floor);
	Wall.DestroyTile(Wall);
	Trap_Niddle.DestroyTile(Trap_Niddle);
	Trap_Hole.DestroyTile(Trap_Hole);
	Trap_ScareCrow.DestroyTile(Trap_ScareCrow);
	Trap_Cunfution.DestroyTile(Trap_Cunfution);
	Trap_Grap.DestroyTile(Trap_Grap);
}