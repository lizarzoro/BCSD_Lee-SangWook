// 180313_BCSD.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "180313_BCSD.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//���콺 ������ ����ü
struct _tagArea
{
	bool bStart;
	POINT ptStart;
	POINT ptEnd;	
};

_tagArea g_tArea;

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
    LoadStringW(hInstance, IDC_MY180313_BCSD, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY180313_BCSD));

    MSG msg;

    // �⺻ �޽��� �����Դϴ�.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY180313_BCSD));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;;//MAKEINTRESOURCEW(IDC_MY180313_BCSD);
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

	//���콺 ���ʹ�ư ������ ��
	case WM_LBUTTONDOWN:
		//���콺��ġ lParamdp 32��Ʈ�� x, y�� �پ ��. LOWORD, HIWORD ����ؼ� �и�
		if (!g_tArea.bStart)
		{
			g_tArea.bStart = true;
			g_tArea.ptStart.x = lParam & 0x0000ffff;
			g_tArea.ptStart.y = lParam >> 16;
			g_tArea.ptEnd = g_tArea.ptStart;
			//LOWORD �ᵵ ��

			//������ WM_PAINT �޼��� ȣ�����ִ� �Լ�
			//(�������ڵ�, �ʱ�ȭ����(NULL������ ��ü����), ����ȭ������� ���ſ���)
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;

		//���콺�� �����϶� ������ �޼���
	case WM_MOUSEMOVE:
		if (g_tArea.bStart)
		{
			g_tArea.ptEnd.x = lParam & 0x0000ffff;
			g_tArea.ptEnd.y = lParam >> 16;
		}
		break;

		//���콺 ���� ��ư �����ٰ� ������
	case WM_LBUTTONUP:
		if (g_tArea.bStart)
		{
			g_tArea.bStart = false;
			g_tArea.ptEnd.x = lParam & 0x0000ffff;
			g_tArea.ptEnd.y = lParam >> 16;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;

	//Ű ��������
	case WM_KEYDOWN:
		//�� �޼����� ���� ��� wParam�� � Ű�� �������� ����
		switch (wParam)
		{
		case VK_ESCAPE: //ESC ������ ���:
			DestroyWindow(hWnd);
			break;
		}
		break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�. (�߰���..)

			//���� ��� (�����ġ, ��ǥx, ��ǥy, �����ڵ幮�ڿ�, ���� ����)
			TextOut(hdc, 50, 50, L"win32", 5);
			TextOut(hdc, 150, 50, TEXT("win32"), 5);
			TextOut(hdc, 250, 50, L"win32", 5);
				// �����ڵ� ���ڿ��� ""�տ� L�� ���δ�.
				// �ƴϸ� TEXT ��ũ�� �̿�. TEXT(" ")

			TCHAR strMouse[64] = {};
			
			//�����ڵ� ���ڿ� ������ִ� �Լ�
			wsprintf(strMouse, TEXT("x : %d y : %d"), g_tArea.ptStart.x,
				g_tArea.ptStart.y);
			TextOut(hdc, 600, 30, strMouse, lstrlen(strMouse)); //�����ڵ� ���ڿ� ����

			//�簢�� ��� (��ġ, ������, �����Ʒ�)
			Rectangle(hdc, 100, 100, 200, 200);

			//�� �׸���(��ġ, ������, ����) - �簢�� ��
			Ellipse(hdc, 100, 100, 200, 200);

			//�� �׸���(��ġ, ������, ����)
			MoveToEx(hdc, 300, 100, NULL);
			LineTo(hdc, 400, 150);
			LineTo(hdc, 500, 100);

			MoveToEx(hdc, 300, 200, NULL);
			LineTo(hdc, 400, 250);


			if (g_tArea.bStart)
			{
				Rectangle(hdc, g_tArea.ptStart.x, g_tArea.ptStart.y,
					g_tArea.ptEnd.x, g_tArea.ptEnd.y);
				//MoveToEx(hdc, g_tArea.ptStart.x, g_tArea.ptStart.y, NULL);
				//LineTo(hdc, g_tArea.ptEnd.x, g_tArea.ptEnd.y);
			}

			EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
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
