#include "stdafx.h"
#include "Scene.h"

void Title::Draw(HDC hMemDC)
{
	ObjPool->Gdi.SetTextsColor(RGB(255, 255, 255));
	ObjPool->Gdi.Text(hMemDC, 755, 140, L"이거 마젠타처리", 25);
	ObjPool->Gdi.Text(hMemDC, 810, 190, L"된거임", 35);
	//비트맵 출력 전에 글자를 먼저 출력해서 마젠타처리 여부 확인	

	ObjPool->titleBg.Draw(hMemDC);
	//비트맵 출력

	ObjPool->Gdi.SetTextsColor(RGB(0, 0, 0));
	ObjPool->Gdi.Text(hMemDC, 100, 100, L"모두의 마블 모두 해~");
	ObjPool->Gdi.Text(hMemDC, 500, 150, L"모두의 마블을 다 같이 해~");

	ObjPool->titleBtn.Draw(hMemDC);
	//버튼 출력

	ObjPool->Gdi.SetTextsColor(RGB(255, 0, 0));
	ObjPool->Gdi.Text(hMemDC, SCREEN_WIDTH / 2 - 175, SCREEN_HEIGHT / 2 + 100, L"게임 시작");

	TCHAR str[20];
	wsprintf(str, L"FPS : %d", (int)ObjPool->System.GetFPS());
	ObjPool->Gdi.Text(hMemDC, 0, 0, str, 36);
	//fps확인
}

void Title::OnTimer(HWND hWnd, int timer)
{

}

void Title::OnMouseLButton(HWND hWnd, int x, int y)
{
	if (ObjPool->titleBtn.isClick(x, y))	//버튼을 클릭했을 때
	{
		ObjPool->System.SetScene(SCENE_INGAME);	//씬을 바꾼다
	}
}

void Title::OnMouseRButton(HWND hWnd, int x, int y)
{

}

void Title::OnMouseMove(HWND hWnd, int x, int y)
{
	ObjPool->titleBtn.isOver(x, y);	//계속 마우스오버를 확인 (확인 되었을 때 객체 내부에서 On을 true로 바꿔줌)
}

void Title::OnKeyborad()
{

}