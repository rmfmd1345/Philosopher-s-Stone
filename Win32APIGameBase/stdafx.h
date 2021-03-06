// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#define SCREEN_WIDTH	1280	//윈도우 너비
#define SCREEN_HEIGHT	720		//윈도우 높이
#define FONT			L"궁서"	//폰트 (컴퓨터에 저장되어 있는 폰트를 사용함)

#define MAX_TILE_X 36
#define MAX_TILE_Y 22

#define MAX_LOADSTRING	128

#include "targetver.h"
#include "resource.h"

#define WIN32_LEAN_AND_MEAN
// Windows 헤더 파일:
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#pragma comment (lib, "Msimg32.lib") //이거 있어야 비트맵 마젠타처리 되는 함수 사용가능함 이거때문에 밤샜음 개짜증

// C 런타임 헤더 파일입니다.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <iostream>
#include <functional>

#include "ObjectPool.h"

#define ObjPool ObjectPool::getInstance() //싱글톤의 귀찮은부분 매크로처리
