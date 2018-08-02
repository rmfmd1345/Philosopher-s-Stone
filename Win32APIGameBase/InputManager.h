#pragma once

namespace InputManager {

	int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int OnMouseLButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int OnMouseLButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int OnMouseRButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int OnMouseRButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam);

	void InputUpdate();

}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);