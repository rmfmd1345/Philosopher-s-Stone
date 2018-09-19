#pragma once
#include "Sprite.h"
#include "GdiObj.h"
#include "SystemObj.h"
#include "SoundObj.h"
#include "BitmapObj.h"
#include "ButtonObj.h"
#include "TileObj.h"
#include "HeroObj.h"
#include "EntityObj.h"

enum Tile_ID_List  // �ĺ� ��ȣ ����Ʈ
{
	NONE,
	FLOOR,
	WALL,
	MENTLE,
	TRAP_Niddle,
	TRAP_Hole,
	TRAP_ScareCrow,
	TRAP_Cunfusion,
	TRAP_Grap
};

enum eDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	SPACE,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5
};

enum eTimer
{
	UPDATE,
	ANIMATION
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
	System System;	//�ý��� ������ �־�δ� �� 
	Gdi Gdi;		//�׸��� �Լ��� ����ϴ� ��

	//Entity(Monster)
	Monster MonsterPool;
	Hero Player;

public:
	//title Scene
	Button titleBtn_Start;	//��ư
	Button titleBtn_Credit;
	Button titleBtn_Exit;

	Bitmap titleBg;		//��Ʈ��

	//credit Scene
	Bitmap creditBg;		

	//ingame Scene
	CMap Maps;
	Button ingameBtn_Option;
	Bitmap ingameUI_Stone;
	Bitmap ingameUI_Trap;
	Bitmap ingameUI_Skill;
	Bitmap ingameUI_Stage;
	Bitmap ingameUI_Time;
};
