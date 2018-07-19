#include "stdafx.h"
#include "Scene.h"

void Title::Draw(HDC hMemDC)
{
	ObjPool->titleBg.Draw(hMemDC);

	TCHAR str[20];
	wsprintf(str, L"FPS : %d", (int)ObjPool->System.GetFPS());
	ObjPool->Gdi.Text(hMemDC, 0, 0, str, 36);
	//fps확인

	ObjPool->Mermaid.Draw(hMemDC);
}

void Title::OnTimer(HWND hWnd, int timer)
{
	ObjPool->Mermaid.NextFrameSprite();
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