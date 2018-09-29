#include "stdafx.h"
#include "System.h"

void ApiSystem::Initialize()	//초기화
{
	DrawManager::Initialize();
	FrameManager::Initilaize();

	SetFramePerSec(60.0f);		//프레임 60으로 고정

	ApiSystem::CreateApiWindow();	//윈도우 생성 (=대진쌤의 BaseWindow와 같음)

	ObjPool->CreateObject(m_hWnd);	//오브젝트풀의 오브젝트 초기화

	m_bIsActive = true;	
}

void ApiSystem::Run()
{
	MSG msg;
	PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

	//게임 루프 공간
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
		else if (m_bIsActive)	//메세지가 들어오지 않았을 때 게임이 실행중이면 갱신
		{
			Update();
		}
		else
		{
			WaitMessage();
		}
	}
}

void ApiSystem::Terminate()		//종료
{
	DrawManager::Terminate();
	FrameManager::Terminate();

	ObjPool->DeleteObject();
}

void ApiSystem::Update()	//갱신
{
	InputManager::InputUpdate();	//메세지가 아닌 인풋을 갱신 (ex. 키보드)

	if (FrameManager::Update())		//프레임이 60이 넘지 않게 false와 true를 반환해서 그리기 프레임 스킵
	{
		DrawManager::Drawing(m_hWnd);
		InputManager::OnUpdate();
	}

}

void ApiSystem::CreateApiWindow()	//윈도우 생성.. 생략
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
