#pragma once

class CTile
{
public:
	int Tile_ID; // 타일 식별 번호
	bool Tile_On; // 함정 재장전 여부

	Bitmap Tile_Bitmap;

	std::function<void()> Tile_Func; // 람다식

	void InitTile(HWND hwnd, int ID, LPCWSTR szFileName, std::function<void()> Tile_Function); //타일 초기화
	void DestroyTile(CTile Tile); // 타일 이미지 파괴
};

class CMap
{
public:
	CTile Map[20][20]; // 맵

	CTile None; // 아무것도 없음
	CTile Floor; // 바닥
	CTile Wall; // 벽
	CTile Trap_Niddle; // 가시 함정
	CTile Trap_Hole; // 구멍 함정
	CTile Trap_ScareCrow; // 허수아비 함정
	CTile Trap_Cunfution; // 혼란 함정
	CTile Trap_Grap; // 갈고리 함정

	Bitmap Brick[4]; // 벽돌 이미지

	enum Tile_ID_List  // 식별 번호 리스트
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

	enum Brick_ID_List
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	void InitMap(HWND hwnd); // 타일 이미지 초기화
	void ResetMap(); // 스테이지 넘어갈 때 맵을 초기화
	void ActiveTile(/*현재 플레이어의 좌표*/); // 해당 타일의 기능을 실행 (람다 사용)
	void SetTileOnMap(CTile Tile, int x, int y); // 타일을 맵에 배치
	void DrawMap(); // 맵을 그려냄 (화면 스크롤링 포함)
	void DrawBrick(); // 벽을 그려냄
	void DestroyMap(); // 맵 타일 파괴
};