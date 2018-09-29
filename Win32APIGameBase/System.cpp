#include "stdafx.h"
#include "System.h"

void ApiSystem::Initialize()	//�ʱ�ȭ
{
	DrawManager::Initialize();
	FrameManager::Initilaize();

	SetFramePerSec(60.0f);		//������ 60���� ����

	ApiSystem::CreateApiWindow();	//������ ���� (=�������� BaseWindow�� ����)

	ObjPool->CreateObject(m_hWnd);	//������ƮǮ�� ������Ʈ �ʱ�ȭ

	m_bIsActive = true;	
}

void ApiSystem::Run()
{
	MSG msg;
	PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

	//���� ���� ����
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (GetMessage(&msg, NULL, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else return;
		}
		else if (m_bIsActive)	//�޼����� ������ �ʾ��� �� ������ �������̸� ����
		{
			Update();
		}
		else
		{
			WaitMessage();
		}
	}
}

void ApiSystem::Terminate()		//����
{
	DrawManager::Terminate();
	FrameManager::Terminate();

	ObjPool->DeleteObject();
}

void ApiSystem::Update()	//����
{
	InputManager::InputUpdate();	//�޼����� �ƴ� ��ǲ�� ���� (ex. Ű����)

	if (FrameManager::Update())		//�������� 60�� ���� �ʰ� false�� true�� ��ȯ�ؼ� �׸��� ������ ��ŵ
	{
		DrawManager::Drawing(m_hWnd);
		InputManager::OnUpdate();
	}

}

void ApiSystem::CreateApiWindow()	//������ ����.. ����
{

	HINSTANCE hInst = GetModuleHandle(NULL);

	TCHAR szTitle[MAX_LOADSTRING];
	TCHAR szWindowClass[MAX_LOADSTRING];

	LoadStringW(hInst, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInst, IDC_WIN32APIGAMEBASE, szWindowClass, MAX_LOADSTRING);


	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)MainWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInst;
	wcex.hIcon = LoadIcon(hInst, (LPCTSTR)IDI_WIN32APIGAMEBASE);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szTitle;
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	RegisterClassEx(&wcex);

	m_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr, nullptr, hInst, nullptr);

	RECT rt = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRect(&rt, WS_BORDER | WS_CAPTION | WS_SYSMENU, false);
	SetWindowPos(m_hWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, SWP_SHOWWINDOW);

	if (!m_hWnd)
	{
		return;
	}
	ShowWindow(m_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(m_hWnd);

	return;
}
