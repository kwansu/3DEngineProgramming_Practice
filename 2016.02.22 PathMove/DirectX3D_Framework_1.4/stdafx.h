// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <d3dx9.h>
#include <assert.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <string>
#include "Resource.h"
using namespace std;


#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(linker,"/entry:wWinMainCRTStartup /subsystem:console")


// 외부 전역 변수
extern HWND			g_hWnd;
extern HINSTANCE	g_hInst;


// 전역 매크로
#define EPSILON	0.0001f


// 구조체 헤더
#include "stVertex.h"
#include "stRange.h"
#include "stPlane.h"
#include "stPathNode.h"
#include "cRay.h"


// 후입 추가 헤더
#include "Utility.h"
#include "cDeviceManager.h"
#include "cTimeManager.h"
#include "cInputManager.h"
#include "cTextrueManager.h"
#include "cGameObjectManager.h"
#include "cSpriteManager.h"
#include "cUIManager.h"
#include "cFontManager.h"
#include "cMeshManager.h"
#include "cPathManager.h"
#include "cWallCreator.h"
#include "cObj_Camera.h"

#include "iCollider.h"
