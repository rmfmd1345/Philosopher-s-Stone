#include "stdafx.h"

//namespace �� ���� �Լ� �̸������� ������ �ٸ��� �Ͽ� ������ �� �ֵ��� ����
namespace Ingame {
	void Draw(HDC hMemDC);
	void OnTimer(HWND hWnd, int timer);
	void Update();
	void OnMouseLButtonDown(HWND hWnd, int x, int y);
	void OnMouseLButtonUp(HWND hWnd, int x, int y);
	void OnMouseRButtonDown(HWND hWnd, int x, int y);
	void OnMouseRButtonUp(HWND hWnd, int x, int y);
	void OnMouseMove(HWND hWnd, int x, int y);
	void OnKeyborad();
}

namespace Title {
	void Draw(HDC hMemDC);
	void OnTimer(HWND hWnd, int timer);
	void Update();
	void OnMouseLButtonDown(HWND hWnd, int x, int y);
	void OnMouseLButtonUp(HWND hWnd, int x, int y);
	void OnMouseRButtonDown(HWND hWnd, int x, int y);
	void OnMouseRButtonUp(HWND hWnd, int x, int y);
	void OnMouseMove(HWND hWnd, int x, int y);
	void OnKeyborad();
}

namespace Credit {
	void Draw(HDC hMemDC);
	void OnTimer(HWND hWnd, int timer);
	void Update();
	void OnMouseLButtonDown(HWND hWnd, int x, int y);
	void OnMouseLButtonUp(HWND hWnd, int x, int y);
	void OnMouseRButtonDown(HWND hWnd, int x, int y);
	void OnMouseRButtonUp(HWND hWnd, int x, int y);
	void OnMouseMove(HWND hWnd, int x, int y);
	void OnKeyborad();
}