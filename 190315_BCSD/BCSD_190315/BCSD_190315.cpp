// BCSD_190315.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "BCSD_190315.h"
#include <list>

using namespace std;

#define MAX_LOADSTRING 100

typedef struct _tagRectangle
{
	float l, t, r, b;
} RECTANGLE, *PRECTANGLE;

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

HWND	g_hWnd;
HDC		g_hDC;
bool	g_bLoop = true;
RECTANGLE	g_tPlayerRC = { 100, 100, 200, 200 };

typedef struct _tagBullet
{
	RECTANGLE rc;
	float fDist;
	float fLimitDist;
}BULLET, *PBULLET;

// �÷��̾� �Ѿ�
list<BULLET> g_PlayerBulletList;

// �ð� ���ϱ� ���� ������
LARGE_INTEGER	g_tSecond;
LARGE_INTEGER	g_tTime;
float			g_fDeltaTime;

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
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

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_BCSD_190315, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

	// ȭ�� DC����!
	g_hDC = GetDC(g_hWnd);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BCSD_190315));

    MSG msg;

	QueryPerformanceFrequency(&g_tSecond);
	QueryPerformanceCounter(&g_tTime);

    // �⺻ �޽��� �����Դϴ�.
    while (g_bLoop)
    {
		// PeekMessage�� �޼����� ť�� ��� �ٷ� ����
		// �޼����� ������ true, ������ false
		// �������� ���� �ð��� �������� ����Ÿ���̴�.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

		// ������ ����Ÿ�� (���⿡ ���� �������� ��)
		else
		{

			Run();
		
		}
    }

	ReleaseDC(g_hWnd, g_hDC);

    return (int) msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
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
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	g_hWnd = hWnd;

	// Ŭ���̾�Ʈ ���� ũ��
	RECT rc = { 0, 0, 800, 600 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	// ������ â�� ��ġ, ũ��
	SetWindowPos(hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left,
		rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �޴� ������ ���� �м��մϴ�.
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
            // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.
            EndPaint(hWnd, &ps);
        }
        break;
		//������ ���ᶧ ����
    case WM_DESTROY:
		//���⼭ ������ f
		g_bLoop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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
	// DeltaTime�� �����ش�. 
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

	// �÷��̾� �ʴ� �̵��ӵ� : 
	//static float fMoveUpTime = 3.f;
	float	fSpeed = 400.f * g_fDeltaTime;
	if (GetAsyncKeyState('D') & 0x8000)
	{
		g_tPlayerRC.l += fSpeed;
		g_tPlayerRC.r += fSpeed;
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		g_tPlayerRC.l -= fSpeed;
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

		tBullet.rc.l = g_tPlayerRC.r;
		tBullet.rc.r = g_tPlayerRC.r + 50.f;
		tBullet.rc.t = (g_tPlayerRC.t + g_tPlayerRC.b) / 2.f - 25.f;
		tBullet.rc.b = tBullet.rc.t + 50.f;
		tBullet.fDist = 0.f;
		tBullet.fLimitDist = 500.f;

		g_PlayerBulletList.push_back(tBullet);
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
	
	// �÷��̾� �Ѿ� �̵�
	list<BULLET>::iterator	iter;
	list<BULLET>::iterator	iterEnd = g_PlayerBulletList.end();

	fSpeed = 600.f * g_fDeltaTime * fTimeScale;

	for (iter = g_PlayerBulletList.begin(); iter != iterEnd;)
	{
		(*iter).rc.r += fSpeed;
		(*iter).rc.l += fSpeed;

		(*iter).fDist += fSpeed;

		if ((*iter).fDist >= (*iter).fLimitDist)
		{
			iter = g_PlayerBulletList.erase(iter);
			iterEnd = g_PlayerBulletList.end();
		}

		else if (800 <= (*iter).rc.l)
		{
			iter = g_PlayerBulletList.erase(iter);
			iterEnd = g_PlayerBulletList.end();
		}

		else
			++iter;
	}
	
	// �Ѿ� ���
	Rectangle(g_hDC, 0, 0, 800, 600);
	Rectangle(g_hDC, g_tPlayerRC.l, g_tPlayerRC.t,
		g_tPlayerRC.r, g_tPlayerRC.b);

	for (iter = g_PlayerBulletList.begin(); iter != iterEnd; ++iter)
	{
		Rectangle(g_hDC, (*iter).rc.l, (*iter).rc.t, (*iter).rc.r, (*iter).rc.b);
	}
}