#pragma once

class CTile
{
public:
	int Tile_ID;
	bool Tile_On;
	HBITMAP hBitMap;

	std::function<void()> btn_Func;

	CTile InitTile(int ID, LPCWSTR szFileName, std::function<void()> btn_Function);
};

class CMap
{
public:
	CTile Map[10][10];

	CTile None;
	CTile Floor;
	CTile Wall;
	CTile Trap_Niddle;
	CTile Trap_Hole;
	CTile Trap_ScareCrow;
	CTile Trap_Cunfution;
	CTile Trap_Grap;     

	enum Tile_ID_List
	{
		NONE,
		FLOOR,
		WALL,
		TRAP_Niddle,
		TRAP_Hole,
		TRAP_ScareCrow,
		TRAP_Cunfution,
		TRAP_Grap
	};

	void InitMap();
	void ResetMap();
	void ActiveTile();
	void SetTileOnMap(CTile Tile, int x, int y);
	void SetMap();
	void DrawMap();
	void DistroyMap();
};