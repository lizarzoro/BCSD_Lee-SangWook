// BCSD_190315.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "BCSD_190315.h"
#include <list>
#include <math.h>

using namespace std;

#define MAX_LOADSTRING 100

enum MOVE_DIR
{
	MD_BACK = -1,
	MD_NONE,
	MD_FRONT
};
typedef struct _tagRectangle
{
	float l, t, r, b;
} RECTANGLE, *PRECTANGLE;

typedef struct _tagSphere
{
	float x, y;
	float r;
}SPHERE, *PSPHERE;

typedef struct _tagMonster
{
	SPHERE	tSphere;
	float	fSpeed;
	float	fTime;
	float	fLimitTime;
	int		iDir;
}MONSTER, *PMONSTER;



// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

HWND	g_hWnd;
HDC		g_hDC;
bool	g_bLoop = true;
SPHERE	g_tPlayer = { 50.f, 50.f, 50.f };
POINT		g_tGunPos;
float		g_fGunLength = 70.f;
float		g_fPlayerAngle;
MONSTER		g_tMonster;

typedef struct _tagBullet
{
	SPHERE tSphere;
	float fDist;
	float fLimitDist;
}BULLET, *PBULLET;

// 플레이어 총알
list<BULLET> g_PlayerBulletList;

// 몬스터 총알
list<BULLET> g_MonsterBulletList;

// 시간 구하기 위한 변수들
LARGE_INTEGER	g_tSecond;
LARGE_INTEGER	g_tTime;
float			g_fDeltaTime;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void Run();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_BCSD_190315, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

	// 화면 DC생성!
	g_hDC = GetDC(g_hWnd);

	// 몬스터 초기화
	g_tMonster.tSphere.x = 800.f - 50.f;
	g_tMonster.tSphere.y = 50.f;
	g_tMonster.tSphere.r = 50.f;
	g_tMonster.fSpeed = 300.f;
	g_tMonster.fTime = 0.f;
	g_tMonster.fLimitTime = 2.f;
	g_tMonster.iDir = MD_FRONT;

	// 총구 위치
	g_tGunPos.x = g_tPlayer.x + cosf(g_fPlayerAngle)
		* g_fGunLength;

	g_tGunPos.y = g_tPlayer.y + sinf(g_fPlayerAngle)
		* g_fGunLength;

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BCSD_190315));

    MSG msg;

	QueryPerformanceFrequency(&g_tSecond);
	QueryPerformanceCounter(&g_tTime);

    // 기본 메시지 루프입니다.
    while (g_bLoop)
    {
		// PeekMessage는 메세지가 큐에 없어도 바로 나옴
		// 메세지가 있으면 true, 없으면 false
		// ㅁ세지가 없는 시간이 윈도우의 데드타임이다.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

		// 윈도우 데드타임 (여기에 게임 만들어나가야 함)
		else
		{

			Run();
		
		}
    }

	ReleaseDC(g_hWnd, g_hDC);

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BCSD_190315));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL; //MAKEINTRESOURCEW(IDC_BCSD_190315);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	g_hWnd = hWnd;

	// 클라이언트 영역 크기
	RECT rc = { 0, 0, 800, 600 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	// 윈도우 창의 위치, 크기
	SetWindowPos(hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left,
		rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
            EndPaint(hWnd, &ps);
        }
        break;
		//윈도우 종료때 들어옴
    case WM_DESTROY:
		//여기서 루프를 f
		g_bLoop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void Run()
{
	// DeltaTime을 구해준다. 
	LARGE_INTEGER	tTime;
	QueryPerformanceCounter(&tTime);

	g_fDeltaTime = (tTime.QuadPart - g_tTime.QuadPart) /
		(float)g_tSecond.QuadPart;

	g_tTime = tTime;

	static float fTimeScale = 1.f;

	if (GetAsyncKeyState(VK_F1) & 0x8000)
	{
		fTimeScale -= g_fDeltaTime;
		if (fTimeScale < 0.f)
			fTimeScale = 0.f;
	}

	if (GetAsyncKeyState(VK_F2) & 0x8000)
	{
		fTimeScale += g_fDeltaTime;
		if (fTimeScale > 1.f)
			fTimeScale = 1.f;
	}

	// 플레이어 초당 이동속도 : 
	//static float fMoveUpTime = 3.f;
	float	fSpeed = 400.f * g_fDeltaTime;
	if (GetAsyncKeyState('D') & 0x8000)
	{
		g_tPlayerRC.x += fSpeed;
		g_tPlayerRC.r += fSpeed;
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		g_tPlayerRC.x -= fSpeed;
		g_tPlayerRC.r -= fSpeed;
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		g_tPlayerRC.t += fSpeed;
		g_tPlayerRC.b += fSpeed;
	}

	if (GetAsyncKeyState('W') & 0x8000)
	{
		g_tPlayerRC.t -= fSpeed;
		g_tPlayerRC.b -= fSpeed;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		BULLET tBullet;

		tBullet.tSphere.x = g_tPlayerRC.r + 50.f;
		tBullet.tSphere.y = g_tPlayerRC.t + 50.f;
		tBullet.tSphere.r = 25.f;
		tBullet.fDist = 0.f;
		tBullet.fLimitDist = 500.f;

		g_PlayerBulletList.push_back(tBullet);
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		// 마우스 위치를 얻어온다
		POINT ptMouse;
		// 아래 함수는 마우스 위치를 얻어온다.
		// 마우스 위치는 스크린 좌표 기준으로 받아온다.
		GetCursorPos(&ptMouse);

		// 스크린 좌표 -> 클라이언트 좌표
		ScreenToClient(g_hWnd, &ptMouse);

		// 플레이어와 충돌처리
		if (g_tPlayerRC.l <= ptMouse.x && ptMouse.x <= g_tPlayerRC.r &&
			g_tPlayerRC.t <= ptMouse.y && ptMouse.y <= g_tPlayerRC.b)
			MessageBox(NULL, L"플레이어 클릭", L"마우스 클릭", MB_OK);
	}

	RECT rcWindow;  
	GetClientRect(g_hWnd, &rcWindow);
	SetRect(&rcWindow, 0, 0, 800, 600);

	if (g_tPlayerRC.l < 0)
	{
		g_tPlayerRC.l = 0;
		g_tPlayerRC.r = 100;
	}

  	else if (g_tPlayerRC.r > rcWindow.right)
	{
		g_tPlayerRC.r = rcWindow.right;
		g_tPlayerRC.l = rcWindow.right - 100;
	}

	if (g_tPlayerRC.t < 0)
	{
		g_tPlayerRC.t = 0;
		g_tPlayerRC.b = 100;
	}

	else if (g_tPlayerRC.b > rcWindow.bottom)
	{
		g_tPlayerRC.b = rcWindow.bottom;
		g_tPlayerRC.t = rcWindow.bottom - 100;
	}
	// 몬스터 이동
	g_tMonster.tSphere.y += g_tMonster.fSpeed * g_fDeltaTime * fTimeScale * g_tMonster.iDir;
	//g_tMonster.tRC.b += g_tMonster.fSpeed * g_fDeltaTime * fTimeScale * g_tMonster.iDir;

	if (g_tMonster.tSphere.y + g_tMonster.tSphere.r >= 600)
	{
		g_tMonster.iDir = MD_BACK;
		g_tMonster.tSphere.y = 550;
	}

	else if (g_tMonster.tSphere.y -g_tMonster.tSphere.r <= 0)
	{
		g_tMonster.iDir = MD_FRONT;
		g_tMonster.tSphere.y = 50;
	}

	// 몬스터 총알 발사 로직
	g_tMonster.fTime += g_fDeltaTime * fTimeScale;

	if (g_tMonster.fTime >= g_tMonster.fLimitTime)
	{
		g_tMonster.fTime -= g_tMonster.fLimitTime;
		
		BULLET tBullet = {};

		tBullet.tSphere.x = g_tMonster.tSphere.x - g_tMonster.tSphere.r - 25.f;
		tBullet.tSphere.y = g_tMonster.tSphere.y;
		tBullet.tSphere.r = 25.f;
		tBullet.fDist = 0.f;
		tBullet.fLimitDist = 800.f;

		g_MonsterBulletList.push_back(tBullet);
	}
	
	// 플레이어 총알 이동
	list<BULLET>::iterator	iter;
	list<BULLET>::iterator	iterEnd = g_PlayerBulletList.end();

	fSpeed = 600.f * g_fDeltaTime * fTimeScale;

	for (iter = g_PlayerBulletList.begin(); iter != iterEnd;)
	{
		(*iter).tSphere.x += fSpeed;

		(*iter).fDist += fSpeed;

		float fX = (*iter).tSphere.x - g_tMonster.tSphere.x;
		float fY = (*iter).tSphere.y - g_tMonster.tSphere.y;
		float fDist = sqrtf(fX * fX + fY * fY);

		if (fDist <= (*iter).tSphere.r + g_tMonster.tSphere.r)
		{
			iter = g_PlayerBulletList.erase(iter);
			iterEnd = g_PlayerBulletList.end();
		}

		else if ((*iter).fDist >= (*iter).fLimitDist)
		{
			iter = g_PlayerBulletList.erase(iter);
			iterEnd = g_PlayerBulletList.end();
		}

		else if (800 <= (*iter).tSphere.x - (*iter).tSphere.r)
		{
			iter = g_PlayerBulletList.erase(iter);
			iterEnd = g_PlayerBulletList.end();
		}



		else
			++iter;
	}

	// 몬스터 총알 이동
	iterEnd = g_MonsterBulletList.end();
	for (iter = g_MonsterBulletList.begin(); iter != iterEnd;)
	{
		(*iter).tSphere.x -= fSpeed;
	
		(*iter).fDist += fSpeed;

		if ((*iter).fDist >= (*iter).fLimitDist)
		{
			iter = g_MonsterBulletList.erase(iter);
			iterEnd = g_MonsterBulletList.end();
		}

		else if (0 >= (*iter).tSphere.x + (*iter).tSphere.r)
		{
			iter = g_MonsterBulletList.erase(iter);
			iterEnd = g_MonsterBulletList.end();
		}
		/*
		//rect 충돌
		else if (g_tPlayerRC.l <= (*iter).rc.r && (*iter).rc.l <= g_tPlayerRC.r &&
			g_tPlayerRC.t <= (*iter).rc.b && (*iter).rc.t <= g_tPlayerRC.b)
		{
			iter = g_MonsterBulletList.erase(iter);
			iterEnd = g_MonsterBulletList.end();
		}*/

		else
			++iter;
	}

	// 총알 출력
	//Rectangle(g_hDC, 0, 0, 800, 600);
	
	Ellipse(g_hDC, g_tMonster.tSphere.x - g_tMonster.tSphere.r,
		g_tMonster.tSphere.y - g_tMonster.tSphere.r,
		g_tMonster.tSphere.x + g_tMonster.tSphere.r, 
		g_tMonster.tSphere.y + g_tMonster.tSphere.r);

	Ellipse(g_hDC, g_tPlayerRC.l, g_tPlayerRC.t,
		g_tPlayerRC.r, g_tPlayerRC.b);

	iterEnd = g_PlayerBulletList.end();
	for (iter = g_PlayerBulletList.begin(); iter != iterEnd; ++iter)
	{
		Ellipse(g_hDC, (*iter).tSphere.x - (*iter).tSphere.r,
			(*iter).tSphere.y - (*iter).tSphere.r,
			(*iter).tSphere.x + (*iter).tSphere.r,
			(*iter).tSphere.y + (*iter).tSphere.r);
	}

	// 몬스터 총알 출력
	iterEnd = g_MonsterBulletList.end();
	for (iter = g_MonsterBulletList.begin(); iter != iterEnd; ++iter)
	{
		Ellipse(g_hDC, (*iter).tSphere.x - (*iter).tSphere.r,
			(*iter).tSphere.y - (*iter).tSphere.r,
			(*iter).tSphere.x + (*iter).tSphere.r,
			(*iter).tSphere.y + (*iter).tSphere.r);
	}
}