#pragma once

#include "../Game.h"

class CObj
{
protected:
	CObj();
	virtual ~CObj();

protected:
	int		m_iRef;

public:
	void AddRef()
	{
		++m_iRef;
	}

	int Release()
	{
		--m_iRef;
		if (m_iRef == 0) 
		{
			delete this;
			return 0;
		}
		return m_iRef;
	}

protected:
	POSITION	m_tPos;
	_SIZE		m_tSize;
	string		m_strTag;
	POSITION	m_tPivot;

public:
	string GetTag() const { return m_strTag; }
	POSITION GetPos() const { return m_tPos; }
	_SIZE GetSize() const { return m_tSize; }
	POSITION GetPivot() const { return m_tPivot; }

public:
	void setTag(const string& strTag)
	{
		m_strTag = strTag;
	}

	void SetPos(const POSITION& tPos)
	{
		m_tPos = tPos;
	}

	void SetPos(const POINT& tPos)
	{
		m_tPos = tPos;
	}

	void SetPos(float x, float y)
	{
		m_tPos.x = x;
		m_tPos.y = y;
	}

	void SetSize(const _SIZE& tSize)
	{
		m_tSize = tSize;
	}

	void SetSize(float x, float y)
	{
		m_tSize.x = x;
		m_tSize.y = y;
	}

	void SetPivot(const _SIZE& tPivot)
	{
		m_tPivot = tPivot;
	}

	void SetPivot(float x, float y)
	{
		m_tPivot.x = x;
		m_tPivot.y = y;
	}
	
public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

