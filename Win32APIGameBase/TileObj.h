#pragma once
#include "EntityObj.h"

class CTile
{
public:
	int Tile_ID; // 타일 식별 번호
	int hp;
	bool Tile_On; // 함정 재장전 여부
	bool Tile_SelectArea; //플레이어 고정시 함정 설치가능 영역인가
	bool Tile_isCanMove; //지나갈 수 있는 타일인가

	bool GrabArea_Row; //가로
	bool GrabArea_Column; //세로
	bool Brick_Up;
	bool Brick_Down;
	bool Brick_Left;
	bool Brick_Right;
	bool SubWall_Left;
	bool SubWall_Right;

	SpriteHelper Tile_Sprite_On;
	SpriteHelper Tile_Sprite_Off;
	SpriteHelper Ani_Trap[4]; // 애니메이션 스프라이트 (정방향 출력 시 : 발동 애니메이션 / 역방향 출력 시 : 재장전 애니메이션) (보류)
	SpriteHelper Ani_SelectedArea;

	std::function<void(Entity* ent)> Tile_Func; // 람다식 (함정 발동 시 프레임 진행)

	void InitTile(HWND hwnd, int Frame, int ID, int MoveID, int traphp, std::function<void(Entity* ent)> Tile_Function); //타일 초기화
	void DestroyTile(CTile Tile); // 타일 이미지 파괴

public:
	//함정 공통
	float TrapHp; //함정 체력 (수리게이지 최대치) //임시로 여기서 초기화함
	int TrapHp_Now; //수리 진행도 게이지
	int stateFrame; //함정 애니메이션 프레임상태
	int nowTrapDirection; //함정 애니메이션 방향

	//혼란함정
	int stunTime; //함정 걸렸을때 멈추는 시간
	//구멍함정
	float damgeDelay; //함정 밟았을 때 연속해서 함수가 발동되기까지의 간격
	float SpinSpeed; //구멍함정에서 엔티티가 도는 속도

	//갈고리함정
	POINT Grab_POS; //갈고리 함정을 밟으면 끌려갈 위치

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
	CTile Trap_Grab; // 갈고리함정
	CTile Trap_GrabArea; // 갈고리함정 영향권
	CTile Skill_Barricade; // 바리게이트 타일

	Bitmap Brick[6]; // 벽돌 이미지
	Bitmap ingameUI_TrapHpBar_edge; //함정 체력바 테두리
	Bitmap ingameUI_TrapHpBar_fill; //함정 체력바 채우기
	Bitmap ingameUI_TrapArea; //함정 설치가능 영역

	Bitmap Trap_GrabArea_row; // 갈고리함정 영향권 (가로)
	Bitmap Trap_GrabArea_column; // 갈고리함정 영향권 (세로)

	Bitmap Barricade_Health_UI; // 바리케이드 체력 UI

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
	int SetTrapOnMap(CTile Tile, int x, int y); // 함정을 맵에 배치
	bool isCanTrapSet(int x, int y); //설치할 수 있는 곳인가
	void DrawMap(HDC hMemDC, int x, int y); //  플레이어를 기준으로 화면에 나오는 타일을 계산하여 출력
	void DrawTileUI(HDC hMemDC, int x, int y); //체력바, 선택 영역 등 UI 표시
	void SetBrick(int x, int y); // 벽돌 위치를 설정
	void DrawBrick(HDC hMemDC, int x, int y); // 벽돌을 그려냄
	void DestroyMap(); // 맵 타일 파괴

	int GetTileID(int x, int y);
	int GetTileMoveID(int x, int y);
	bool CheckTrap(int diraction, POINT pos);
};