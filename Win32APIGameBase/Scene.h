#include "stdafx.h"

//namespace 는 같은 함수 이름이지만 성씨를 다르게 하여 구별할 수 있도록 구분
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