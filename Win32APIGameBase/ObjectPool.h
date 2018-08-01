#pragma once
#include "Sprite.h"
#include "GdiObj.h"
#include "SystemObj.h"
#include "BitmapObj.h"
#include "ButtonObj.h"

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

	// title scene
public:
	Button titleBtn_Start;	//��ư (Rectangle�� �׸����� ��ġ�� ��ư ���¸� üũ�ؾ��ϹǷ� ��ü�� ����)
	Button titleBtn_Credit;
	Button titleBtn_Exit;
	Bitmap titleBg;		//��Ʈ��

};
