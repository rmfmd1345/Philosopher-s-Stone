#pragma once
#include "Sprite.h"
#include "GdiObj.h"
#include "SystemObj.h"
#include "BitmapObj.h"
#include "ButtonObj.h"

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
	System System;	//시스템 변수를 넣어두는 곳 
	Gdi Gdi;		//그리기 함수를 사용하는 곳

	// title scene
public:
	Button titleBtn_Start;	//버튼 (Rectangle로 그리지만 위치나 버튼 상태를 체크해야하므로 객체로 만듬)
	Button titleBtn_Credit;
	Button titleBtn_Exit;
	Bitmap titleBg;		//비트맵

};
