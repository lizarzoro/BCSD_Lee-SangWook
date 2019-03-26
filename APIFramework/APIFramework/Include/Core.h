#pragma once

#include "Game.h"

class CCore
{
private:
	static bool		m_bLoop;
	static CCore*	m_pInst;
	HINSTANCE		m_hInst;
	HWND			m_hWnd;
	HDC				m_hDC;
	RESOLUTION		m_tRS;

private:
	CCore();
	~CCore();

	ATOM	MyRegisterClass();
	BOOL	Create();
	void	Logic();
	void	Input(float fDeltaTime);
	int		Update(float fDeltaTime);
	int		LateUpdate(float fDeltaTime);
	void	Collision(float fDeltaTime);
	void	Render(float fDeltaTime);

public:
	RESOLUTION GetResolution() const { return m_tRS; }
	HWND GetWindowHandle() const { return m_hWnd; }

	void DestroyGame()
	{
		DestroyWindow(m_hWnd);
	}

	static CCore* GetInst()
	{
		if (!m_pInst)
			m_pInst = new CCore;
		return m_pInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	bool	Init(HINSTANCE hInst);
	int		Run();
};

