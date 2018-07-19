#include "stdafx.h"
#include "Scene.h"

void Title::Draw(HDC hMemDC)
{

	ObjPool->titleBg.Draw(hMemDC);
	//��Ʈ�� ���

	ObjPool->titleBtn.Draw(hMemDC);
	//��ư ���

	ObjPool->Gdi.SetTextsColor(RGB(255, 0, 0));
	ObjPool->Gdi.Text(hMemDC, SCREEN_WIDTH / 2 - 175, SCREEN_HEIGHT / 2 + 100, L"���� ����");

	TCHAR str[20];
	wsprintf(str, L"FPS : %d", (int)ObjPool->System.GetFPS());
	ObjPool->Gdi.Text(hMemDC, 0, 0, str, 36);
	//fpsȮ��

	ObjPool->Gdi.Text(hMemDC, 100, 100, L"������ ��", 50);
}

void Title::OnTimer(HWND hWnd, int timer)
{

}

void Title::OnMouseLButton(HWND hWnd, int x, int y)
{
	if (ObjPool->titleBtn.isClick(x, y))	//��ư�� Ŭ������ ��
	{
		ObjPool->System.SetScene(SCENE_INGAME);	//���� �ٲ۴�
	}
}

void Title::OnMouseRButton(HWND hWnd, int x, int y)
{

}

void Title::OnMouseMove(HWND hWnd, int x, int y)
{
	ObjPool->titleBtn.isOver(x, y);	//��� ���콺������ Ȯ�� (Ȯ�� �Ǿ��� �� ��ü ���ο��� On�� true�� �ٲ���)
}

void Title::OnKeyborad()
{

}