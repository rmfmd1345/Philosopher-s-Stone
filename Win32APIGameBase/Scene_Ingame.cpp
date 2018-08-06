#include "stdafx.h"
#include "Scene.h"

//For test
static int x = 5;
static int y = 5;

void Ingame::Draw(HDC hMemDC)
{
	ObjPool->Gdi.SetBrushColor(RGB(0, 0, 0));
	ObjPool->Gdi.Rect(hMemDC, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });

	ObjPool->Maps.DrawMap(hMemDC, x, y);
	ObjPool->ingameBtn_Option.Draw(hMemDC);
	ObjPool->ingameUI_Stone.Draw(hMemDC);
	ObjPool->ingameUI_Trap.Draw(hMemDC);
	ObjPool->ingameUI_Skill.Draw(hMemDC);
	ObjPool->ingameUI_Stage.Draw(hMemDC);
	ObjPool->ingameUI_Time.Draw(hMemDC);
}

void Ingame::OnTimer(HWND hWnd, int timer)
{

}

void Ingame::OnMouseLButtonDown(HWND hWnd, int x, int y)
{
	ObjPool->ingameBtn_Option.isClickDown(x, y);
}

void Ingame::OnMouseLButtonUp(HWND hWnd, int x, int y)
{
	if (ObjPool->ingameBtn_Option.isClickUp(x, y))
	{
		ObjPool->System.SetScene(SCENE_OPTION);
	}
	
	//For test
	ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Floor, x / 80, y / 80);
}

void Ingame::OnMouseRButtonDown(HWND hWnd, int x, int y)
{
	
}

void Ingame::OnMouseRButtonUp(HWND hWnd, int x, int y)
{
	//For test
	ObjPool->Maps.SetTileOnMap(ObjPool->Maps.Trap_Niddle, x / 80, y / 80);
}

void Ingame::OnMouseMove(HWND hWnd, int x, int y)
{
	ObjPool->ingameBtn_Option.isOver(x, y);
}

void Ingame::OnKeyborad()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		x--;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		x++;
	}
	else if (GetAsyncKeyState(VK_UP))
	{
		y--;
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		y++;
	}
}