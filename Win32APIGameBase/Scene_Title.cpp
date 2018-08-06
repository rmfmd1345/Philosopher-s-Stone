#include "stdafx.h"
#include "Scene.h"

void Title::Draw(HDC hMemDC)
{
	//배경 출력
	ObjPool->titleBg.Draw(hMemDC);
	
	//버튼 출력
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
	if (ObjPool->titleBtn_Start.isClickUp(x, y))	//버튼을 클릭했을 때
	{
		ObjPool->System.SetScene(SCENE_INGAME);	//씬을 바꾼다
	}
	if (ObjPool->titleBtn_Credit.isClickUp(x, y))	//버튼을 클릭했을 때
	{
		ObjPool->System.SetScene(SCENE_CREDIT);	//씬을 바꾼다
	}
	if (ObjPool->titleBtn_Exit.isClickUp(x, y))	//버튼을 클릭했을 때
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
	ObjPool->titleBtn_Start.isOver(x, y);	//계속 마우스오버를 확인 (확인 되었을 때 객체 내부에서 On을 true로 바꿔줌)
	ObjPool->titleBtn_Credit.isOver(x, y);
	ObjPool->titleBtn_Exit.isOver(x, y);
}

void Title::OnKeyborad()
{

}