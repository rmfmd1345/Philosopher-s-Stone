#pragma once

enum eAnimation
{
	STAND,
	WALK,
	ATTACK,
	CLEAR
};

enum eDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum eEntity
{
	DEALER,
	WIZARD,
	TANKER
};

class Entity	//:	protected Astar
{
public:
	Entity() { };
	~Entity() { };

private:
	int type;		//엔티티 타입
	POINT pos;		//엔티티 위치

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
	void Draw(HDC hMemDC);
	void Ternimate();

	void Animaition();

	void SetAnimation(int ani);
	void SetDirection(int dire);

	void PlusHealth(int plus);

	bool isDead();
	bool isWalk();
};

class Monster
{
public:
	Monster() { };
	~Monster() { };

private:
	vector<Entity> monsterPool;

	POINT spawnPosition;

public:
	void Init(HWND hWnd);
	void Ternimate();
	
	void Draw(HDC hMemDC);
	void Animation();

	void AddMonster(HWND hWnd, int type);
	void CheckHealth();

};