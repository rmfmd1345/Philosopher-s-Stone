#include "stdafx.h"
#include "Scene.h"

void Credit::Draw(HDC hMemDC)
{
	ObjPool->creditBg.Draw(hMemDC);
}

void Credit::OnTimer(HWND hWnd, int timer)
{

}

void Credit::OnMouseLButtonDown(HWND hWnd, int x, int y)
{

}

void Credit::OnMouseLButtonUp(HWND hWnd, int x, int y)
{

}

void Credit::OnMouseRButtonDown(HWND hWnd, int x, int y)
{

}

void Credit::OnMouseRButtonUp(HWND hWnd, int x, int y)
{

}

void Credit::OnMouseMove(HWND hWnd, int x, int y)
{

}

void Credit::OnKeyborad()
{
	if (GetAsyncKeyState(VK_SPACE))	//Ű���� �Է��� VK_SPACE��� Ÿ��Ʋ�� ���ư���
	{
		ObjPool->System.SetScene(SCENE_TITLE);	//���� �ٲ۴�
	}
}