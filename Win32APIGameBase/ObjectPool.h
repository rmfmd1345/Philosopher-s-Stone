#pragma once
#include "Sprite.h"
#include "A_Star.h"
#include "GdiObj.h"
#include "SystemObj.h"
#include "SoundObj.h"
#include "BitmapObj.h"
#include "ButtonObj.h"
#include "TileObj.h"
#include "Skill.h"
#include "HeroObj.h"
#include "EntityObj.h"

#define BADENDING 1
#define HAPPYENDING 2

enum Tile_ID_List  // �ĺ� ��ȣ ����Ʈ
{
	NONE,
	FLOOR,
	WALL,
	MENTLE,
	TRAP_Niddle,
	TRAP_Hole,
	TRAP_ScareCrow,
	TRAP_Confusion,
	TRAP_Grab,
	TRAP_GrabArea,
	SKILL_Barricade,
	ALTAR
};

enum eDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT,

	//KEY
	SPACE,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_F,
	KEY_P,

	UPnLEFT,
	UPnRIGHT,
	DOWNnLEFT,
	DOWNnRIGHT,
};

enum eTimer
{
	UPDATE,
	ANIMATION,
	PLAYERWALK,
	MONSTERTM,
	SOUND,
	ENDING
};

class ObjectPool		//������Ʈ Ǯ (������������ ����)
{
private:
	ObjectPool(void) { }
	~ObjectPool(void) { }
	static ObjectPool *pool;

public:
	static ObjectPool *getInstance()	//�̱��� ����
	{
		if (!pool)
			pool = new ObjectPool;
		return pool;
	}

public:
	void CreateObject(HWND hWnd);		//�ʱ�ȭ (hWnd�� ��Ʈ�ʶ����� �޾���� �մϴ�)
	void DeleteObject();				//����

public:
	System System;		//�ý��� ������ �־�δ� ��
	Sounds SoundPool;	//����
	Gdi Gdi;			//�׸��� �Լ��� ����ϴ� ��

	//Entity(Monster)
	Monster MonsterPool;
	SpriteHelper FindEffect;
	SpriteHelper ConfuseEffect;
	Bitmap StoneEffect;
	int debug = 0;

	Hero Player;
	TCHAR TIMER[10];

	int MonsterTimer = 0;
	int Wave = -1;
	TCHAR Wave_UI[10];

	int timeDropStone = 0;
	bool CheckMonster;

	int howtonum = 0;
	bool optionover = false;
	bool optiondown = false;

	int aniEnding = 0;
	POINT EndingPos;

public:
	int Endingnum = 0;

	//title Scene
	Button titleBtn_Start;	//��ư
	Button titleBtn_Credit;
	Button titleBtn_Exit;

	Bitmap titleBg;		//��Ʈ��
	Bitmap badendingBg;
	Bitmap happyendingBg;


	//credit Scene
	Bitmap creditBg;		

	//howto Scene
	Bitmap howto[3];

	//ingame Scene
	CMap Maps;
	Button ingameBtn_Option;
	SpriteHelper ingameSprite_Option;
	Bitmap ingameUI_Stone;
	Bitmap ingameUI_Trap;
	Bitmap ingameUI_Skill;
	Bitmap ingameUI_Stage;
	Bitmap ingameUI_Stage_Steal;
	Bitmap ingameUI_Time;

	SpriteHelper ingameUI_SelectedTrap; //���� ���� �ִϸ��̼�
};
