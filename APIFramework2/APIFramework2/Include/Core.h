#pragma once

#include "Game.h"

class CCore
{
private:
	static CCore*	m_pInst; // 스테틱 맴버변수

public:
	static CCore*	GetInst()
	{
		if (!m_pInst) // 처음에 null이면 동적할당
			m_pInst = new CCore;
		return m_pInst; // 객체가 하나만 만들어지는 비결
	}

	static void DestroyInst() 
	{
		SAFE_DELETE(m_pInst);
	}

private:
	CCore();
	~CCore();

private:
	static bool		m_bLoop;
	  
private:
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	HDC			m_hDC;
	RESOLUTION	m_tRS;

public:
	bool Init(HINSTANCE hInst);
	int Run();

private:
	void Logic();
	void Input(float fDeltaTime);
	int Update(float fDeltaTime);
	int LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(float fDeltaTime);

private:
	ATOM	MyRegisterClass();
	BOOL	Create();

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

