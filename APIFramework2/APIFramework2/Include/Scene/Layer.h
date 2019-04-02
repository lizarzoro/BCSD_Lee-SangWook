#pragma once
#include "../Game.h"

class CLayer
{
private:
	CLayer();
	friend class CScene;

public:
	//CLayer();
	~CLayer();

private:
	class CScene*	m_pScene;
	string			m_strTag;
	int				m_iZOrder;
	list<class CObj*> m_ObjList;
	bool			m_bEnable;
	bool			m_bLife;

public:
	void SetTag(const string& strTag)
	{
		m_strTag = strTag;
	}

	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}

	void SetZOrder(int iZOrder)
	{
		m_iZOrder = iZOrder;
	}

	string GetTag() const noexcept
	{
		return m_strTag;
	}

	int GetZOrder() const noexcept
	{
		return m_iZOrder;
	}

	CScene* GetScene() const noexcept
	{
		return m_pScene;
	}

public:
	void Input(float fDeltaTime);
	int Update(float fDeltaTime);
	int LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDC, float fDeltaTime);
};

