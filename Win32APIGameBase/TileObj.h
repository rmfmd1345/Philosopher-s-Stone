#pragma once

class CTile
{
public:
	int Tile_ID; // 타일 식별 번호
	bool Tile_On; // 함정 재장전 여부

	SpriteHelper Tile_Sprite; // 애니메이션 스프라이트 (정방향 출력 시 : 발동 애니메이션 / 역방향 출력 시 : 재장전 애니메이션)

	std::function<void()> Tile_Func; // 람다식 (함정 발동 시 프레임 진행)

	void InitTile(HWND hwnd, int Frame, int ID, LPCWSTR szFileName, std::function<void()> Tile_Function); //타일 초기화
	void DestroyTile(CTile Tile); // 타일 이미지 파괴
};

class CMap
{
public:
	CTile Map[18][32]; // 맵

	CTile None; // 아무것도 없음
	CTile Floor; // 바닥
	CTile Wall; // 벽
	CTile Trap_Niddle; // 가시 함정
	CTile Trap_Hole; // 구멍 함정
	CTile Trap_ScareCrow; // 허수아비 함정
	CTile Trap_Cunfusion; // 혼란 함정
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
		LEFT,
		RIGHT,
		DOWN
	};

	void InitMap(HWND hwnd); // 타일 이미지 초기화
	void ResetMap(int Character_x, int Character_y); // 스테이지 넘어갈 때 맵을 초기화
	void ActiveTile(int Character_x, int Character_y); // 해당 타일의 기능을 실행 (람다 사용)
	void SetTileOnMap(CTile Tile, int x, int y); // 타일을 맵에 배치
	void DrawMap(HDC hMemDC, int x, int y); //  플레이어를 기준으로 화면에 나오는 타일을 계산하여 출력
	void SetBrick(int x, int y); // 벽돌 위치를 설정
	void DrawBrick(HDC hMemDC, int x, int y); // 벽돌을 그려냄
	void DestroyMap(); // 맵 타일 파괴
};