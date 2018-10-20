#pragma once
#include "InputManager.h"
#include "DrawManager.h"
#include "FrameManager.h"

class ApiSystem		:	protected DrawManager,	//�׸��� ������
						protected FrameManager	//�����Ӱ��� ������
{
public:
	ApiSystem(void) { }
	~ApiSystem(void) { }

private:
	HWND m_hWnd;		
	BOOL m_bIsActive;	//���� �� ����
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