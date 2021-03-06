// Win32APIGameBase.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "System.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	//Api System
	ApiSystem* System = new ApiSystem;

	System->Initialize();	//초기화
	System->Run();			//실행
	System->Terminate();	//종료

	delete System;

	return 0;
}
