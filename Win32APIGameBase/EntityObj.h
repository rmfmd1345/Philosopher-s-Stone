#pragma once
using namespace std;

enum eState
{
	STAND,
	WALK,
	ATTACK,
	CLEAR,
	FINDWAY
};

enum eEntity
{
	DEALER,
	WIZARD,
	TANKER
};

class Entity	//:	protected Astar
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

	int health;

public:
	void Init(HWND hWnd, int x, int y, int type, COLORREF sprite = RGB(255, 0, 255));
	void Draw(HDC hMemDC, int x, int y);
	void Ternimate();

	void Animation();
	void UpdateState();

	POINT GetPosition();

	void SetPosition(int x, int y);
	void SetAnimation(int ani);
	void SetDirection(int dire);

	void PlusHealth(int plus);

	bool isDead();
	bool isWalk();

private:
	static vector<POINT> BanRoad;		//막 다른 길
	vector<POINT> SearchRoad;			//플레이어 서치 길(아스타)

	bool isFindBanRoad = false;

public:
	bool isRoadBlocked();
	bool isRoadBlocked(int dire);

	void RotateClockwise();
	void RotateCounterclockwise();
	void RotateReverse();

	void FindPlayer();

	void SetBanRoad(int x, int y);
	bool isBanRoad(int x, int y);

};

class Monster
{
public:
	Monster() { };
	~Monster() { };

private:
	Entity Dealer;
	Entity Wizard;
	Entity Tanker;
	vector<Entity> pool;

	POINT spawnPosition = { 0,0 };

public:
	void Init(HWND hWnd);
	void Ternimate();
	
	void Draw(HDC hMemDC, int x, int y);
	void Animation();
	void UpdateState();

	void AddMonster(HWND hWnd, int type, int x, int y);
	void AddMonster(HWND hWnd, int type);
	void CheckHealth();

	void SetDirection(int dire);
};