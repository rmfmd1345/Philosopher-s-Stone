#pragma once
using namespace std;

class Hero	//:	protected Astar
{
private:
	int type;		//엔티티 타입
	POINT pos;		//엔티티 위치

	int nowState;
	int stateFrame_Hero;
	int stateFrame_TrapSelect;

	int nowAnimation;		//지금 엔티티 애니메이션 상태
	int nowDirection;
	SpriteHelper Ani_stand[4];
	SpriteHelper Ani_walk[4];
	SpriteHelper Ani_attack[4];
	int nowFrame;
	int maxFrame;

public:
	int Rock_Num;
	TCHAR Rock_Num_UI[11];
	Skill ATK_Skill;
	Skill AGGRO_Skill;
	Skill PUSH_Skill;
	Skill BARRICADE_Skill;
	int selectedTrap;
	int selectedSkill;
	bool isWaitingTrapSet;
	bool isWaitingSkillSet;

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
	int GetDirection();

	POINT GetPosition();
	int GetWalkState();
	POINT GetWalkTerm();

	void DigMap();
	void SetSelectedArea(bool isCreate);
	void SetTrap();
	void UseSkill();
	void RepairTrap();
	void CheckEnding();

	void DrawSelectedTrapUI(HDC hMemDC);

	bool isWalk();
};
