#include "stdafx.h"
#include "InputManager.h"
#include "Scene.h"

int InputManager::OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	SetTimer(hWnd, 0, 100, NULL);
	return 1;
}

int InputManager::OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (ObjPool->System.GetScene())	//����Ǯ���� ���� �ҷ���
	{
	case SCENE_TITLE:	//���� Ÿ��Ʋ �̶��
		Title::OnTimer(hWnd, wParam);	//Ÿ��Ʋ Ÿ�̸ӷ� ����
		break;
	case SCENE_INGAME:	//���� �ΰ��� �̶��
		Ingame::OnTimer(hWnd, wParam);	//�ΰ��� Ÿ�̸ӷ� ����
		break;
	}
	return 1;
}

int InputManager::OnMouseLButton(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (ObjPool->System.GetScene())	//���� ����
	{
	case SCENE_TITLE:
		Title::OnMouseLButton(hWnd, LOWORD(lParam), HIWORD(lParam));	//���콺�� ��ġ ���� ���� lParam�� �մܾ�, �޴ܾ�� �����ؼ� x,y�� �� (?��Ʈ����)
		break;
	case SCENE_INGAME:
		Ingame::OnMouseLButton(hWnd, LOWORD(lParam), HIWORD(lParam));
		break;
	}
	return 1;
}

int InputManager::OnMouseRButton(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (ObjPool->System.GetScene()) //���� ����
	{
	case SCENE_TITLE:
		Title::OnMouseRButton(hWnd, LOWORD(lParam), HIWORD(lParam));
		break;
	case SCENE_INGAME:
		Ingame::OnMouseRButton(hWnd, LOWORD(lParam), HIWORD(lParam));
		break;
	}
	return 1;
}

int InputManager::OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (ObjPool->System.GetScene()) //���� ����
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
void InputManager::InputUpdate()		//�޼����� �ƴ� �ٸ� ��ǲ�� ó�� (ex. Ű����)
{
	if (GetAsyncKeyState(VK_ESCAPE))	//Ű���� �Է��� VK_ESCAPE(=ESC)��� ���α׷� ����
	{
		exit(0);
	}


	switch (ObjPool->System.GetScene()) //���� ����
	{
	case SCENE_TITLE:
		Title::OnKeyborad();
		break;
	case SCENE_INGAME:
		Ingame::OnKeyborad();
		break;
	}
}

// Proc
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)	//�ݹ鿡�� �޼��� ������ ���� �Լ��� ����
{
	switch (message)
	{
	case WM_CREATE:
		return InputManager::OnCreate(hWnd, wParam, lParam);
	case WM_TIMER:
		return InputManager::OnTimer(hWnd, wParam, lParam);
	case WM_LBUTTONUP:
		return InputManager::OnMouseLButton(hWnd, wParam, lParam);
	case WM_RBUTTONUP:
		return InputManager::OnMouseRButton(hWnd, wParam, lParam);
	case WM_MOUSEMOVE:
		return InputManager::OnMouseMove(hWnd, wParam, lParam);
	case WM_DESTROY:
		return InputManager::OnDestroy(hWnd, wParam, lParam);
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}