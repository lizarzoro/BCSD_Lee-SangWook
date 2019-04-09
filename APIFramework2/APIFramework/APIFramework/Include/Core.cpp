#include "Core.h"
#include "Scene\SceneManager.h"
#include "Core\Timer.h"
#include "Core\PathManager.h"
#include "Resources\ResourcesManager.h"
#include "Resources\Texture.h"
#include "Core\Camera.h"
#include "Core\Input.h"
#include "Collider\CollisionManager.h"
#include "Object\Mouse.h"

CCore*	CCore::m_pInst = NULL;
bool	CCore::m_bLoop = true;

CCore::CCore()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// _CrtSetBreakAlloc(313);

#ifdef _DEBUG
	// �ܼ� â ����
	AllocConsole();
#endif // _DEBUG
}


CCore::~CCore()
{
	DESTROY_SINGLE(CSceneManager);
	DESTROY_SINGLE(CCollisionManager);
	DESTROY_SINGLE(CInput);
	DESTROY_SINGLE(CCamera);
	DESTROY_SINGLE(CResourcesManager);
	DESTROY_SINGLE(CPathManager);
	DESTROY_SINGLE(CTimer);

	ReleaseDC(m_hWnd, m_hDC);

#ifdef _DEBUG
	FreeConsole();
#endif // _DEBUG
}

ATOM CCore::MyRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = CCore::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL; //MAKEINTRESOURCEW(IDC_FREEWIN32PROJECT00);
	wcex.lpszClassName = L"AR13API";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassExW(&wcex);
}

BOOL CCore::Create()
{
	m_hWnd = CreateWindowW(L"AR13API", L"AR13API", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

	if (!m_hWnd) { return FALSE; }

	RECT rc = { 0, 0, m_tRS.iW, m_tRS.iH};
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left,
		rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return TRUE;
}

void CCore::Logic()
{
	// Ÿ�̸� ����
	GET_SINGLE(CTimer)->Update();

	float fDeltaTime = GET_SINGLE(CTimer)->GetDeltaTime();

	Input(fDeltaTime);

	if (Update(fDeltaTime) == SC_CHANGE)
		return;
	if (LateUpdate(fDeltaTime) == SC_CHANGE)
		return;

	Collision(fDeltaTime);
	Render(fDeltaTime);
}

void CCore::Input(float fDeltaTime)
{
	GET_SINGLE(CInput)->Update(fDeltaTime);

	GET_SINGLE(CSceneManager)->Input(fDeltaTime);
	GET_SINGLE(CCamera)->Input(fDeltaTime);
}

int CCore::Update(float fDeltaTime)
{
	SCENE_CHANGE sc;
	sc = GET_SINGLE(CSceneManager)->Update(fDeltaTime);
	GET_SINGLE(CCamera)->Update(fDeltaTime);
	return sc;
}

int CCore::LateUpdate(float fDeltaTime)
{
	SCENE_CHANGE sc;
	sc = GET_SINGLE(CSceneManager)->LateUpdate(fDeltaTime);
	return sc;
}

void CCore::Collision(float fDeltaTime)
{
	GET_SINGLE(CSceneManager)->Collision(fDeltaTime);

	GET_SINGLE(CCollisionManager)->Collision(fDeltaTime);
}

void CCore::Render(float fDeltaTime)
{
	// ���� ���۸�
	CTexture* pBackBuffer = GET_SINGLE(CResourcesManager)->GetBackBuffer();

	GET_SINGLE(CSceneManager)->Render(pBackBuffer->GetDC(), fDeltaTime);

	// �������� ���콺�� �׸���.
	CMouse* pMouse = GET_SINGLE(CInput)->GetMouse();

	pMouse->Render(pBackBuffer->GetDC(), fDeltaTime);

	BitBlt(m_hDC, 0, 0, m_tRS.iW, m_tRS.iH, pBackBuffer->GetDC(), 0, 0, SRCCOPY);

	SAFE_RELEASE(pBackBuffer);
}

LRESULT CCore::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		m_bLoop = false;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

bool CCore::Init(HINSTANCE hInst)
{
	m_hInst = hInst;

	MyRegisterClass();

	// �ػ� ����
	m_tRS.iW = 1280;
	m_tRS.iH = 720;

	Create();

	// ȭ�� DC�� ������ش�.
	m_hDC = GetDC(m_hWnd);

	// Ÿ�̸� �ʱ�ȭ
	if (!GET_SINGLE(CTimer)->Init(m_hWnd))
		return false;

	// ��ΰ����� �ʱ�ȭ
	if (!GET_SINGLE(CPathManager)->Init())
		return false;

	// �Է°����� �ʱ�ȭ
	if (!GET_SINGLE(CInput)->Init(m_hWnd))
		return false;

	// ���ҽ� ������ �ʱ�ȭ
	if (!GET_SINGLE(CResourcesManager)->Init(hInst, m_hDC))
		return false;

	// ī�޶� ������ �ʱ�ȭ
	if (!GET_SINGLE(CCamera)->Init(POSITION(0.f, 0.f), m_tRS, RESOLUTION(1500, 1200)))
		return false;

	// Initiate Scene Manager
	if (!GET_SINGLE(CSceneManager)->Init())
		return false;

	return true;
}

int CCore::Run()
{
	MSG msg;
	
	// �⺻ �޽��� �����Դϴ�.
	while (m_bLoop)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// When Window's DeadTime
		else
		{
			Logic();
		}
	}

	return (int)msg.wParam;
}
