#pragma once

#include "../Game.h"

class CTimer
{
private:
	HWND			m_hWnd;
	LARGE_INTEGER	m_tSecond;
	LARGE_INTEGER	m_tTime;
	float			m_fDeltaTime;
	float			m_fTimeScale;
	float			m_fFPS;
	float			m_fFPSTime;
	int				m_iFrame;

public:
	bool Init(HWND hWnd);
	void Update();

	float GetDeltaTime() const noexcept
	{
		return m_fDeltaTime * m_fTimeScale;
	}

	float GetFPS() const noexcept
	{
		return m_fFPS;
	}

	float GetTimeScale() const noexcept
	{
		return m_fTimeScale;
	}

	void SetTimeScale(float fTimeScale)
	{
		m_fTimeScale = fTimeScale;
	}

	DECLARE_SINGLE(CTimer)
};

