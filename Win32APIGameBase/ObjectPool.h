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

enum Tile_ID_List  // 식별 번호 리스트
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
	SOUND
};

class ObjectPool		//오브젝트 풀 (전역변수같이 사용됨)
{
private:
	ObjectPool(void) { }
	~ObjectPool(void) { }
	static ObjectPool *pool;

public:
	static ObjectPool *getInstance()	//싱글톤 적용
	{
		if (!pool)
			pool = new ObjectPool;
		return pool;
	}

public:
	void CreateObject(HWND hWnd);		//초기화 (hWnd는 비트맵때문에 받아줘야 합니다)
	void DeleteObject();				//종료

public:
	System System;		//시스템 변수를 넣어두는 곳
	Sounds SoundPool;	//사운드
	Gdi Gdi;			//그리기 함수를 사용하는 곳

	//Entity(Monster)
	Monster MonsterPool;
	SpriteHelper FindEffect;
	SpriteHelper ConfuseEffect;
	int debug = 0;

	Hero Player;
	TCHAR TIMER[10];

	int MonsterTimer = 0;
	int Wave = 1;

public:
	//title Scene
	Button titleBtn_Start;	//버튼
	Button titleBtn_Credit;
	Button titleBtn_Exit;

	Bitmap titleBg;		//비트맵
	Bitmap EndingBg_Dead;
	Bitmap EndingBg_Clear;

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

	SpriteHelper ingameUI_SelectedTrap; //함정 선택 애니메이션
};
