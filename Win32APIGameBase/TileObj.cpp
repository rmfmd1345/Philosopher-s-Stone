#include "stdafx.h"
#include "TileObj.h"

void CMap::InitMap()
{
	None = None.InitTile(NONE, L"./Image/", [&] {});
	Floor = Floor.InitTile(FLOOR, L"./Image/", [&] {});
	Wall = Wall.InitTile(WALL, L"./Image/", [&] {});
	Trap_Niddle = Trap_Niddle.InitTile(TRAP_Niddle, L"./Image/", [&] {});
	Trap_Hole = Trap_Hole.InitTile(TRAP_Hole, L"./Image/", [&] {});
	Trap_ScareCrow = Trap_ScareCrow.InitTile(TRAP_ScareCrow, L"./Image/", [&] {});
	Trap_Cunfution = Trap_Cunfution.InitTile(TRAP_Cunfution, L"./Image/", [&] {});
	Trap_Grap = Trap_Grap.InitTile(TRAP_Grap, L"./Image/", [&] {});
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

void CMap::SetTileOnMap(CTile Tile, int x, int y)
{
	Map[x][y].Tile_ID = Tile.Tile_ID;
	Map[x][y].Tile_On = Tile.Tile_On;

	Map[x][y].hBitMap = Tile.hBitMap;

	Map[x][y].btn_Func = Tile.btn_Func;
}

void CMap::SetMap()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
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

void CMap::DrawMap()
{

}

void CMap::DistroyMap()
{

}

CTile CTile::InitTile(int ID, LPCWSTR szFileName, std::function<void()> btn_Function)
{
	CTile Temp;

	Temp.Tile_ID = ID;
	Temp.Tile_On = true;

	WCHAR str[128];
	wsprintf(str, szFileName);
	Temp.hBitMap = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (Temp.hBitMap == NULL)
	{
		MessageBox(NULL, L"이미지가 없습니다.", L"에러!!!", MB_OK);	//이미지불러오기 실패
		exit(0);
	}

	Temp.btn_Func = btn_Function;

	return Temp;
}
