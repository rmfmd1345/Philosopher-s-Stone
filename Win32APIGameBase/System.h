#pragma once
#include "InputManager.h"
#include "DrawManager.h"
#include "FrameManager.h"

class ApiSystem		:	protected DrawManager,	//그리기 관리자
						protected FrameManager	//프레임고정 관리자
{
public:
	ApiSystem(void) { }
	~ApiSystem(void) { }

private:
	HWND m_hWnd;		
	BOOL m_bIsActive;	//실행 중 여부
	DEVMODE dmSaved;
	DEVMODE dmSelected;

public:
	void Initialize();
	void Run();
	void Terminate();
	
private:
	void Update();

private:
	void CreateApiWindow();

};