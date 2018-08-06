#include "stdafx.h"
#include "Scene.h"

void Title::Draw(HDC hMemDC)
{
	//��� ���
	ObjPool->titleBg.Draw(hMemDC);
	
	//��ư ���
	ObjPool->titleBtn_Start.Draw(hMemDC);
	ObjPool->titleBtn_Credit.Draw(hMemDC);
	ObjPool->titleBtn_Exit.Draw(hMemDC);
}

void Title::OnTimer(HWND hWnd, int timer)
{

}

void Title::OnMouseLButtonDown(HWND hWnd, int x, int y)
{
	ObjPool->titleBtn_Start.isClickDown(x, y);
	ObjPool->titleBtn_Credit.isClickDown(x, y);
	ObjPool->titleBtn_Exit.isClickDown(x, y);
}

void Title::OnMouseLButtonUp(HWND hWnd, int x, int y)
{
	if (ObjPool->titleBtn_Start.isClickUp(x, y))	//��ư�� Ŭ������ ��
	{
		ObjPool->System.SetScene(SCENE_INGAME);	//���� �ٲ۴�
	}
	if (ObjPool->titleBtn_Credit.isClickUp(x, y))	//��ư�� Ŭ������ ��
	{
		ObjPool->System.SetScene(SCENE_CREDIT);	//���� �ٲ۴�
	}
	if (ObjPool->titleBtn_Exit.isClickUp(x, y))	//��ư�� Ŭ������ ��
	{
		exit(0);
	}
}

void Title::OnMouseRButtonDown(HWND hWnd, int x, int y)
{

}

void Title::OnMouseRButtonUp(HWND hWnd, int x, int y)
{

}

void Title::OnMouseMove(HWND hWnd, int x, int y)
{
	ObjPool->titleBtn_Start.isOver(x, y);	//��� ���콺������ Ȯ�� (Ȯ�� �Ǿ��� �� ��ü ���ο��� On�� true�� �ٲ���)
	ObjPool->titleBtn_Credit.isOver(x, y);
	ObjPool->titleBtn_Exit.isOver(x, y);
}

void Title::OnKeyborad()
{

}