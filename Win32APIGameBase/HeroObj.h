#pragma once
using namespace std;

class Hero	//:	protected Astar
{
private:
	int type;		//엔티티 타입
	POINT pos;		//엔티티 위치

	int nowState;
	int stateFrame;

	int nowAnimation;		//지금 엔티티 애니메이션 상태
	int nowDirection;
	SpriteHelper Ani_stand[4];
	SpriteHelper Ani_walk[4];
	SpriteHelper Ani_attack[4];
	int nowFrame;
	int maxFrame;

public:
	int health;
	int selectedTrap;

public:
	void Init(HWND hWnd, int x, int y, COLORREF sprite = RGB(255, 0, 255));
	void Draw(HDC hMemDC, int x, int y);
	void Ternimate();

	void Animation();
	void UpdateState();

	void SetPosition(int x, int y);
	void SetAnimation(int ani);
	void SetDirection(int dire);
	void SetState(int state);
	int GetState();

	POINT GetPosition();
	int GetWalkState();
	POINT GetWalkTerm();

	void PlusHealth(int plus);
	void DigMap();
	void SetTrap();

	bool isDead();
	bool isWalk();
};
