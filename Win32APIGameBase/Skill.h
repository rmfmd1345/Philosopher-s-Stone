#pragma once
using namespace std;

enum Skill_ID
{
	ATK_SKILL,
	PUSH_SKILL,
	AGGRO_SKILL,
	BARRICADE_SKILL
};

class Skill
{
public:
	SpriteHelper Ani_Skill[4];
	POINT Skill_Range[8];
	int nowFrame;
	int maxFrame;

	int nowDirection;
	bool Check_Active;

	int ID;

public:
	void InitSkill(HWND hWnd, int ID, int f);
	void ActiveSkill();
	void Animation();
	void Draw(HDC hMemDC);

	void Terminate();
};