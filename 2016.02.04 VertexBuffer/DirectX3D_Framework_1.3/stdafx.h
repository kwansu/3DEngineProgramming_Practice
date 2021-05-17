// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <d3dx9.h>
#include <assert.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <math.h>
#include <fstream>
#include <iostream>
#include "Resource.h"
using namespace std;


#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")



// �ܺ� ���� ����:
extern HWND			g_hWnd;
extern HINSTANCE	g_hInst;


// ���� �߰� ���:
#include "stVertex.h"
#include "InlineUtility.h"
#include "cReferenceCounter.h"
#include "cReferrers.h"
#include "cDeviceManager.h"
#include "cTimeManager.h"
#include "cInputManager.h"
#include "cObjectManager.h"
#include "iCollider.h"
#include "cCollider_Terrain.h"
#include "cResourceManager.h"
