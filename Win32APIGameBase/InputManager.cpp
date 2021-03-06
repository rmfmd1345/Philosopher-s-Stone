#include "stdafx.h"
#include "InputManager.h"
#include "Scene.h"

int InputManager::OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	SetTimer(hWnd, UPDATE, 1, NULL); //업데이트를 위해 타이머 1초간격으로 설정
	SetTimer(hWnd, ANIMATION, 50, NULL);

	return 1;
}

int InputManager::OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (ObjPool->System.GetScene())	//옵젝풀에서 씬을 불러옴
	{
	case SCENE_TITLE:	//씬이 타이틀 이라면
		Title::OnTimer(hWnd, wParam);	//타이틀 타이머로 보냄
		break;
	case SCENE_INGAME:	//씬이 인게임 이라면
		Ingame::OnTimer(hWnd, wParam);	//인게임 타이머로 보냄
		break;
	}
	return 1;
}

int InputManager::OnMouseLButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (ObjPool->System.GetScene())	//설명 생략
	{
	case SCENE_TITLE:
		Title::OnMouseLButtonDown(hWnd, LOWORD(lParam), HIWORD(lParam));	//마우스의 위치 값을 가진 lParam을 앞단어, 뒷단어로 분해해서 testC_x,y가 됨 (?비트연산)
		break;
	case SCENE_INGAME:
		Ingame::OnMouseLButtonDown(hWnd, LOWORD(lParam), HIWORD(lParam));
		break;
	}
	return 1;
}

int InputManager::OnMouseLButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (ObjPool->System.GetScene())	//설명 생략
	{
	case SCENE_TITLE:
		Title::OnMouseLButtonUp(hWnd, LOWORD(lParam), HIWORD(lParam));	//마우스의 위치 값을 가진 lParam을 앞단어, 뒷단어로 분해해서 testC_x,y가 됨 (?비트연산)
		break;
	case SCENE_INGAME:
		Ingame::OnMouseLButtonUp(hWnd, LOWORD(lParam), HIWORD(lParam));
		break;
	}
	return 1;
}
int InputManager::OnMouseRButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (ObjPool->System.GetScene()) //설명 생략
	{
	case SCENE_TITLE:
		Title::OnMouseRButtonDown(hWnd, LOWORD(lParam), HIWORD(lParam));
		break;
	case SCENE_INGAME:
		Ingame::OnMouseRButtonDown(hWnd, LOWORD(lParam), HIWORD(lParam));
		break;
	}
	return 1;
}

int InputManager::OnMouseRButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (ObjPool->System.GetScene())	//설명 생략
	{
	case SCENE_TITLE:
		Title::OnMouseRButtonUp(hWnd, LOWORD(lParam), HIWORD(lParam));	//마우스의 위치 값을 가진 lParam을 앞단어, 뒷단어로 분해해서 testC_x,y가 됨 (?비트연산)
		break;
	case SCENE_INGAME:
		Ingame::OnMouseRButtonUp(hWnd, LOWORD(lParam), HIWORD(lParam));
		break;
	}
	return 1;
}

int InputManager::OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (ObjPool->System.GetScene()) //설명 생략
	{
	case SCENE_TITLE:
		Title::OnMouseMove(hWnd, LOWORD(lParam), HIWORD(lParam));
		break;
	case SCENE_INGAME:
		Ingame::OnMouseMove(hWnd, LOWORD(lParam), HIWORD(lParam));
		break;
	}
	return 1;
}

int InputManager::OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
	return 1;
}

// Not Message
void InputManager::InputUpdate()		//메세지가 아닌 다른 인풋의 처리 (ex. 키보드)
{
	if (GetAsyncKeyState(VK_ESCAPE))	//키보드 입력이 VK_ESCAPE(=ESC)라면 프로그램 종료
	{
		exit(0);
	}

	switch (ObjPool->System.GetScene()) //설명 생략
	{
	case SCENE_TITLE:
		Title::OnKeyborad();
		break;
	case SCENE_CREDIT:
		Credit::OnKeyborad();
		break;
	case SCENE_INGAME:
		Ingame::OnKeyborad();
		break;
	}
}

// Proc
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)	//콜백에서 메세지 받으면 각각 함수로 전송
{
	switch (message)
	{
	case WM_CREATE:
		return InputManager::OnCreate(hWnd, wParam, lParam);
	case WM_TIMER:
		return InputManager::OnTimer(hWnd, wParam, lParam);
	case WM_LBUTTONDOWN:
		return InputManager::OnMouseLButtonDown(hWnd, wParam, lParam);
	case WM_LBUTTONUP:
		return InputManager::OnMouseLButtonUp(hWnd, wParam, lParam);
	case WM_RBUTTONDOWN:
		return InputManager::OnMouseRButtonDown(hWnd, wParam, lParam);
	case WM_RBUTTONUP:
		return InputManager::OnMouseRButtonUp(hWnd, wParam, lParam);
	case WM_MOUSEMOVE:
		return InputManager::OnMouseMove(hWnd, wParam, lParam);
	case WM_DESTROY:
		return InputManager::OnDestroy(hWnd, wParam, lParam);
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}