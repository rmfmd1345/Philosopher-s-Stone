#pragma once
using namespace std;

class Hero	//:	protected Astar
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
	int Rock_Num;
	TCHAR Rock_Num_UI[10];
	int selectedTrap;
	bool isWatingTrapSet;

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
	int GetDiraction();

	POINT GetPosition();
	int GetWalkState();
	POINT GetWalkTerm();

	void AddHealth(int a);
	void DigMap();
	void SetTrap();
	void RepairTrap();

	bool isDead();
	bool isWalk();
};
