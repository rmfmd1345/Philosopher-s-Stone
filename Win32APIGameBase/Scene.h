#include "stdafx.h"

//namespace �� ���� �Լ� �̸������� ������ �ٸ��� �Ͽ� ������ �� �ֵ��� ����
namespace Ingame {
	void Draw(HDC hMemDC);
	void OnTimer(HWND hWnd, int timer);
	void OnMouseLButton(HWND hWnd, int x, int y);
	void OnMouseRButton(HWND hWnd, int x, int y);
	void OnMouseMove(HWND hWnd, int x, int y);
	void OnKeyborad();
}

namespace Title {
	void Draw(HDC hMemDC);
	void OnTimer(HWND hWnd, int timer);
	void OnMouseLButton(HWND hWnd, int x, int y);
	void OnMouseRButton(HWND hWnd, int x, int y);
	void OnMouseMove(HWND hWnd, int x, int y);
	void OnKeyborad();
}