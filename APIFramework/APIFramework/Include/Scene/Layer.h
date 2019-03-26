#pragma once

#include "../Game.h"

class CLayer
{
private:
	CLayer();

	friend class CScene;

	class CScene*	m_pScene;
	string			m_strTag;
	int				m_iZOrder;
	list<class CObj*> m_ObjList;
	bool			m_bEnable;
	bool			m_bLife;

public:
	~CLayer();

	void	Input(float fDeltaTime);
	int		Update(float fDeltaTime);
	int		LateUpdate(float fDeltaTime);
	void	Collision(float fDeltaTime);
	void	Render(HDC hDC, float fDeltaTime);

	void SetTag(const string& strTag)
	{
		m_strTag = strTag;
	}

	void SetZOrder(int iZOrder)
	{
		m_iZOrder = iZOrder;
	}

	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
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

	void AddObject(class CObj* pObj);
	bool GetEnable() const noexcept { return m_bEnable; }
	bool GetLife() const noexcept { return m_bLife; }
	void SetEnable(bool bEnable) { m_bEnable = bEnable; }
	void Die() { m_bLife = false; }
};

