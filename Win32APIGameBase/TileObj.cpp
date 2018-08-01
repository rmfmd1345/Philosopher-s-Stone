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
	None.InitTile(hwnd, 0 /*Frame*/, NONE, L"./Image/Tile/", [&] {});
	Floor.InitTile(hwnd, 0 /*Frame*/, FLOOR, L"./Image/Tile/Floor.bmp", [&] {});
	Wall.InitTile(hwnd, 0 /*Frame*/, WALL, L"./Image/Tile/Wall.bmp", [&] {});
	Trap_Niddle.InitTile(hwnd, 0 /*Frame*/, TRAP_Niddle, L"./Image/Tile/", [&] {});
	Trap_Hole.InitTile(hwnd, 0 /*Frame*/, TRAP_Hole, L"./Image/Tile/", [&] {});
	Trap_ScareCrow.InitTile(hwnd, 0 /*Frame*/, TRAP_ScareCrow, L"./Image/Tile/", [&] {});
	Trap_Cunfution.InitTile(hwnd, 0 /*Frame*/, TRAP_Cunfution, L"./Image/Tile/", [&] {});
	Trap_Grap.InitTile(hwnd, 0 /*Frame*/, TRAP_Grap, L"./Image/Tile/", [&] {});

	Brick[UP].Init(hwnd, 0, 0, 80, 80, L"./Image/Tile/Brick_Up.bmp");
	Brick[DOWN].Init(hwnd, 0, 0, 80, 80, L"./Image/Tile/Brick_Down.bmp");
	Brick[LEFT].Init(hwnd, 0, 0, 80, 80, L"./Image/Tile/Brick_Left.bmp");
	Brick[RIGHT].Init(hwnd, 0, 0, 80, 80, L"./Image/Tile/Brick_Right.bmp");
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
		Trap_Cunfution.Tile_Func();
		break;
	case TRAP_Grap:
		Trap_Grap.Tile_Func();
		break;
	}
}

void CMap::SetTileOnMap(CTile Tile, int x, int y)
{
	Map[x][y] = Tile;
}

void CMap::DrawMap(HDC hMemDC)
{
	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			switch (Map[i][j].Tile_ID)
			{
			case NONE:
				None.Tile_Sprite.Draw(hMemDC);
				break;
			case FLOOR:
				Floor.Tile_Sprite.Draw(hMemDC);
				break;
			case WALL:
				Wall.Tile_Sprite.Draw(hMemDC);
				break;
			case TRAP_Niddle:
				Trap_Niddle.Tile_Sprite.Draw(hMemDC);
				break;
			case TRAP_Hole:
				Trap_Hole.Tile_Sprite.Draw(hMemDC);
				break;
			case TRAP_ScareCrow:
				Trap_ScareCrow.Tile_Sprite.Draw(hMemDC);
				break;
			case TRAP_Cunfution:
				Trap_Cunfution.Tile_Sprite.Draw(hMemDC);
				break;
			case TRAP_Grap:
				Trap_Grap.Tile_Sprite.Draw(hMemDC);
				break;
			}
		}
	}
}

void CMap::DrawBrick(HDC hMemDC)
{
	for (int a = 0; a < 4; a++)
	{
		int Istart, Iend, Jstart, Jend;
		int Brick_ID;

		switch (a)
		{
		case 0:
			Istart = 0;
			Iend = 17;
			Jstart = 0;
			Jend = 32;

			Brick_ID = UP;
			break;
		case 1:
			Istart = 0;
			Iend = 18;
			Jstart = 0;
			Jend = 31;

			Brick_ID = LEFT;
			break;
		case 2:
			Istart = 0;
			Iend = 18;
			Jstart = 32;
			Jend = 1;

			Brick_ID = RIGHT;
			break;
		case 3:
			Istart = 18;
			Iend = 1;
			Jstart = 0;
			Jend = 32;

			Brick_ID = DOWN;
			break;
		}

		for (int i = Istart; i < Iend; i++)
		{
			for (int j = Jstart; j < Jend; j++)
			{
				switch (a)
				{
				case 0:
					if (Map[i][j].Tile_ID == WALL)
					{
						Brick[Brick_ID].SetPosition(80 * (j - 1), 80 * (i - 1));
						Brick[Brick_ID].Draw(hMemDC);
					}
					break;
				case 1:
					if (Map[i][j].Tile_ID != Map[i][j + 1].Tile_ID && Map[i][j].Tile_ID == NONE)
					{
						Brick[Brick_ID].SetPosition(80 * (j - 1), 80 * (i - 1));
						Brick[Brick_ID].Draw(hMemDC);
					}
					break;
				case 2:
					if (Map[i][j].Tile_ID != Map[i][j - 1].Tile_ID && Map[i][j].Tile_ID == NONE)
					{
						Brick[Brick_ID].SetPosition(80 * (j - 1), 80 * (i - 1));
						Brick[Brick_ID].Draw(hMemDC);
					}
					break;
				case 3:
					if (Map[i][j].Tile_ID != Map[i - 1][j].Tile_ID && Map[i][j].Tile_ID == NONE)
					{
						Brick[Brick_ID].SetPosition(80 * (j - 1), 80 * (i - 1));
						Brick[Brick_ID].Draw(hMemDC);
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
	Trap_Cunfution.DestroyTile(Trap_Cunfution);
	Trap_Grap.DestroyTile(Trap_Grap);
}