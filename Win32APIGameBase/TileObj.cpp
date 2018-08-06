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
			Map[i][j].Tile_Sprite.SetPosition(i * 80, j * 80);
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
	Map[x][y] = Tile;
	Map[x][y].Tile_Sprite.SetPosition(x * 80, y * 80);
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
	if (Map_End_y > 32)
		Map_End_y = 32;

	for (int i = Map_Start_x; i < Map_End_x; i++)
	{
		for (int j = Map_Start_y; j < Map_End_y; j++)
		{
			if (Map[i][j].Tile_ID == Floor.Tile_ID && Map[i][j - 1].Tile_ID != Floor.Tile_ID)
			{
				Map[i][j - 1] = Wall;
				Map[i][j - 1].Tile_Sprite.SetPosition((i - Map_Start_x) * 80, ((j - Map_Start_y) - 1) * 80);
			}
		}
	}

	for (int i = Map_Start_x; i < Map_End_x; i++)
	{
		for (int j = Map_Start_y; j < Map_End_y; j++)
		{
			Map[i][j].Tile_Sprite.SetPosition((i - Map_Start_x) * 80, (j - Map_Start_y) * 80);

			Map[i][j].Tile_Sprite.Draw(hMemDC);
		}
	}

	DrawBrick(hMemDC, x, y);
}

void CMap::DrawBrick(HDC hMemDC, int x, int y)
{
	int Map_Start_x = x - 9;
	int Map_End_x = x + 9;
	int Map_Start_y = y - 5;
	int Map_End_y = y + 5;

	if (Map_Start_x < 0)
		Map_Start_x = 0;
	if (Map_Start_y < 0)
		Map_Start_y = 0;
	if (Map_End_x > 32)
		Map_End_x = 32;
	if (Map_End_y > 32)
		Map_End_y = 32;

	int Istart, Iend, Jstart, Jend;
	int Brick_ID;

	for (int a = 0; a < 4; a++)
	{
		switch (a)
		{
		case UP:
			Brick_ID = UP;
			break;
		case LEFT:
			Brick_ID = LEFT;
			break;
		case RIGHT:
			Brick_ID = RIGHT;
			break;
		case DOWN:
			Brick_ID = DOWN;
			break;
		}

		for (int i = Istart; i != Iend;)
		{
			for (int j = Jstart; j != Jend;)
			{
				switch (a)
				{
				case UP:
					if (Map[i][j].Tile_ID == WALL)
					{
						Brick[Brick_ID].SetPosition(80 * j, 80 * i);
						Brick[Brick_ID].Draw(hMemDC);
					}
					j++;
					if (j == Jend)
					{
						i++;
					}
					break;
				case LEFT:
					if (Map[i][j].Tile_ID != Map[i + 1][j].Tile_ID && Map[i][j].Tile_ID == NONE)
					{
						Brick[Brick_ID].SetPosition(80 * i, 80 * j);
						Brick[Brick_ID].Draw(hMemDC);
					}
					j++;
					if (j == Jend)
					{
						i++;
					}
					break;
				case RIGHT:
					if (Map[i][j].Tile_ID != Map[i - 1][j].Tile_ID && Map[i][j].Tile_ID == NONE)
					{
						Brick[Brick_ID].SetPosition(80 * i, 80 * j);
						Brick[Brick_ID].Draw(hMemDC);
					}
					j--;
					if (j == Jend)
					{
						i++;
					}
					break;
				case DOWN:
					if (Map[i][j].Tile_ID != Map[i][j - 1].Tile_ID && Map[i][j].Tile_ID == NONE)
					{
						Brick[Brick_ID].SetPosition(80 * i, 80 * (j - 1));
						Brick[Brick_ID].Draw(hMemDC);
					}
					j++;
					if (j == Jend)
					{
						i--;
					}
					break;
				}
			}
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