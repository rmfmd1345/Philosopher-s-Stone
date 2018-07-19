#include "stdafx.h"

//namespace 는 같은 함수 이름이지만 성씨를 다르게 하여 구별할 수 있도록 구분
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