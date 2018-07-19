#pragma once

namespace InputManager {

	int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int OnMouseLButton(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int OnMouseRButton(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam);

	void InputUpdate();

}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);