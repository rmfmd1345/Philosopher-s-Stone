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
	int type;		//��ƼƼ Ÿ��
	POINT pos;		//��ƼƼ ��ġ

	int nowState;
	int stateFrame;

	int nowAnimation;		//���� ��ƼƼ �ִϸ��̼� ����
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
	static vector<POINT> BanRoad;		//�� �ٸ� ��
	vector<POINT> SearchRoad;			//�÷��̾� ��ġ ��(�ƽ�Ÿ)

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