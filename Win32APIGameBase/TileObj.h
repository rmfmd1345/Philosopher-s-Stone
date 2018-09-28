#pragma once
#include "EntityObj.h"
class CTile
{
public:
	int Tile_ID; // 타일 식별 번호
	bool Tile_On; // 함정 재장전 여부

	float damgeDelay; //함정 밟았을 때 연속해서 함수가 발동되기까지의 간격
	float SpinSpeed; //구멍함정에서 엔티티가 도는 속도

	bool Brick_Up;
	bool Brick_Down;
	bool Brick_Left;
	bool Brick_Right;
	bool SubWall_Left;
	bool SubWall_Right;

	SpriteHelper Tile_Sprite; // 애니메이션 스프라이트 (정방향 출력 시 : 발동 애니메이션 / 역방향 출력 시 : 재장전 애니메이션)

	std::function<void(Entity* ent)> Tile_Func; // 람다식 (함정 발동 시 프레임 진행)

	void InitTile(HWND hwnd, int Frame, int ID, LPCWSTR szFileName, std::function<void(Entity* ent)> Tile_Function); //타일 초기화
	void DestroyTile(CTile Tile); // 타일 이미지 파괴
};

class CMap
{

public:
	CTile Map[MAX_TILE_Y][MAX_TILE_X]; // 맵

	CTile None; // 아무것도 없음
	CTile Floor; // 바닥
	CTile Wall; // 벽
	CTile Trap_Niddle; // 가시 함정
	CTile Trap_Hole; // 구멍 함정
	CTile Trap_ScareCrow; // 허수아비 함정
	CTile Trap_Cunfusion; // 혼란 함정
	CTile Trap_Grab; // 갈고리 함정

	Bitmap Brick[6]; // 벽돌 이미지

	enum Brick_ID_List
	{
		B_UP,
		B_LEFT,
		B_RIGHT,
		B_DOWN,
		SW_LEFT,
		SW_RIGHT
	};

	void InitMap(HWND hwnd); // 타일 이미지 초기화
	void NiddleActive(Entity* ent);
	void ScareCrowActive(Entity* ent);
	void GrabActive(Entity* ent);
	void ConfusionActive(Entity* ent);
	void HoleActive(Entity* ent);
	void ResetMap(int Character_x, int Character_y); // 스테이지 넘어갈 때 맵을 초기화
	void ActiveTile(Entity* ent); // 해당 타일의 기능을 실행 (람다 사용)
	void SetTileOnMap(CTile Tile, int x, int y); // 타일을 맵에 배치
	void DrawMap(HDC hMemDC, int x, int y); //  플레이어를 기준으로 화면에 나오는 타일을 계산하여 출력
	void SetBrick(int x, int y); // 벽돌 위치를 설정
	void DrawBrick(HDC hMemDC, int x, int y); // 벽돌을 그려냄
	void DestroyMap(); // 맵 타일 파괴

	int GetTileID(int x, int y);
	bool CheckTrap(int diraction, POINT pos);
};