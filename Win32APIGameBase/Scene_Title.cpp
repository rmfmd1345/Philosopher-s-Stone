#include "stdafx.h"
#include "Scene.h"

void Title::Draw(HDC hMemDC)
{

	ObjPool->titleBg.Draw(hMemDC);
	////��Ʈ�� ���
	//
	ObjPool->titleBtn_Start.Draw(hMemDC);
	ObjPool->titleBtn_Credit.Draw(hMemDC);
	ObjPool->titleBtn_Exit.Draw(hMemDC);
	////��ư ���
	//
	//ObjPool->Gdi.SetTextsColor(RGB(255, 0, 0));
	//ObjPool->Gdi.Text(hMemDC, SCREEN_WIDTH / 2 - 175, SCREEN_HEIGHT / 2 + 100, L"���� ����");
	//
	//TCHAR str[20];
	//wsprintf(str, L"FPS : %d", (int)ObjPool->System.GetFPS());
	//ObjPool->Gdi.Text(hMemDC, 0, 0, str, 36);
	////fpsȮ��
	//
	//ObjPool->Gdi.Text(hMemDC, 100, 100, L"������ ��", 50);
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