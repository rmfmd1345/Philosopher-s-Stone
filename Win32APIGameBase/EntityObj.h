#pragma once
using namespace std;

#define FirstSpawnMonsterNum 50

enum eState
{
	STAND,
	WALK,
	ATTACK,
	CLEAR,
	FINDWAY,
	MARKFORFIND,
	INTRAP,
	CONFUSE,
	TRAPSETTING,
	SKILLPREPARING,
	DISMANTLETRAP,

	STILLSTONE_FIND,
	STILLSTONE_WALK
};

enum eEntity
{
	DEALER,
	WIZARD,
	TANKER
};

class Entity		: protected A_Star
{
private:
	int type;		//엔티티 타입
	POINT pos;		//엔티티 위치

	static POINT spawnPosition;
	static bool isStill;

	int nowState;
	int stateFrame;

	int nowAnimation;		//지금 엔티티 애니메이션 상태
	int nowDirection;
	SpriteHelper Ani_stand[4];
	SpriteHelper Ani_walk[4];
	SpriteHelper Ani_attack[4];
	Bitmap Health_UI;
	int nowFrame;
	int maxFrame;

	int health;

public:
	void Init(HWND hWnd, int x, int y, int type, int hp, COLORREF sprite = RGB(255, 0, 255));
	void Draw(HDC hMemDC, int x, int y);
	void Ternimate();

	void Animation();
	void UpdateState();

	POINT GetPosition();
	POINT GetSpawnPosition();
	Entity* GetEntity();
	int GetDirection();
	int GetHealth();
	int GetState();
	int GetType();

	void SetPosition(int x, int y);
	void SetSpawnPosition(int x, int y);
	void SetAnimation(int ani);
	void SetDirection(int dire);
	void SetState(int state);
	void SetStateFrame(int Frame);

	void SetHealth(int hp);
	void AddHealth(int a);

	bool isDead();
	bool isWalk();

private:
	static vector<POINT> BanRoad;				  //막 다른 길
	static int StackRoad[MAX_TILE_Y][MAX_TILE_X]; //스택되는 길

	static bool isAllSearch;					  //찾는 중 인가
	static POINT PlayerPos;						  //플레이어 위치

	bool isSearch;
	int SearchStack;
	int SearchDirection;
	int SearchGap;

public:
	bool isRoadBlocked();
	bool isRoadBlocked(int x, int y);
	bool isRoadBlocked(int dire);

	bool isSearchFind(int x, int y);

	void RotateClockwise();
	void RotateCounterclockwise();
	void RotateReverse();

	void SetBanRoad(int x, int y);
	bool isBanRoad(int x, int y);
	bool isBanRoad(int dire);

	bool isMonsterRoadOverlap(int x, int y);
	bool isMonsterRoadOverlap(int dire);

	int returnReverseDirection(int dire);

public:
	bool GetAllSearch();
	bool GetSearch();
	void SetAllSearch(bool is);

};

class Monster
{
public:
	Monster() { };
	~Monster() { };

//private: /*ActiveTile 접근하려고 풀어둠*/
	Entity Dealer;
	Entity Wizard;
	Entity Tanker;
	vector<Entity> ePool;
	vector<Entity> ePool_Next;

	POINT spawnPosition = { 2, 5 };

	bool CheckMonsters;

public:
	void Init(HWND hWnd);
	void Ternimate();
	
	Monster GetMonster();

	void Draw(HDC hMemDC, int x, int y);
	void Animation();
	void UpdateState();

	void AddMonster(int type, int x, int y);
	void AddMonster(int type);
	void AddMonster_Next(int type, int x, int y);
	void AddMonster_Next(int type);
	void NextWave();
	bool CheckHealth(Entity* ent);

	void SetDirection(int dire);

private:
	void DrawMap(HDC hMemDC, int x, int y);

};