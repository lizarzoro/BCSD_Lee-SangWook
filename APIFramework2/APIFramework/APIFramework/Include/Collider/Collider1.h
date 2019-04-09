#pragma once
#include "../Ref.h"
class CCollider1 :
	public CRef
{
protected:
	friend class CObj;

	list<function<void(CCollider1*, CCollider1*, float)>>	m_FuncList[CS_END];
	list<CCollider1*>	m_CollisionList;
	COLLLIDER_TYPE		m_eCollType;
	POSITION			m_tHitPoint;
	class CObj*			m_pObj;

	

	POSITION		m_tPrevPos;
	POSITION		m_tMove;

protected:
	CCollider1();
	CCollider1(const CCollider1 & coll);
	virtual ~CCollider1() = 0;

	bool CollisionRectToRect(const RECTANGLE& src,
		const RECTANGLE& dest);
	bool CollisionRectToSphere(const RECTANGLE& src,
		const SPHERE& dest);
	bool CollisionSphereToSphere(const SPHERE& src,
		const SPHERE& dest);
	bool CollisionRectToPixel(const RECTANGLE& src,
		const vector<PIXEL>& vecPixel, int iWidth, int iHeight);
	bool CollisionSphereToPixel(const SPHERE& src,
		const vector<PIXEL>& vecPixel, int iWidth, int iHeight);
	bool CollisionRectToPoint(const RECTANGLE& src,
		const POSITION& dest);
	bool CollisionSphereToPoint(const SPHERE& src,
		const POSITION& dest);
	bool CollisionPixelToPoint(const vector<PIXEL> vecPixel,
		int iWidth, int iHeight, const POSITION& dest);


public:
	COLLLIDER_TYPE GetCollider1Type() const
	{
		return m_eCollType;
	}

	class CObj* GetObj() const
	{
		return m_pObj;
	}


	void SetHitPoint(const POSITION& tPos) { m_tHitPoint = tPos; }
	void AddCollider1(CCollider1* pCollider1) { m_CollisionList.push_back(pCollider1); }
	void SetObj(class CObj* pObj) { m_pObj = pObj; }

	void AddCollisionFunction(COLLISION_STATE eState,
		void(*pFunc)(CCollider1*, CCollider1*, float))
	{
		function<void(CCollider1*, CCollider1*, float)> func;

		func = bind(pFunc, placeholders::_1, placeholders::_2,
			placeholders::_3);

		m_FuncList[eState].push_back(func);
	}

	template <typename T>
	void AddCollisionFunction(COLLISION_STATE eState, T* pObj,
		void(T::*pFunc)(CCollider1*, CCollider1*, float))
	{
		function<void(CCollider1*, CCollider1*, float)> func;

		func = bind(pFunc, pObj, placeholders::_1, placeholders::_2,
			placeholders::_3);

		m_FuncList[eState].push_back(func);
	}

	void CallFunction(COLLISION_STATE eState,
		CCollider1* pDest, float fDeltaTime)
	{
		list<function<void(CCollider1*, CCollider1*, float)>>::iterator iter;
		list<function<void(CCollider1*, CCollider1*, float)>>::iterator iterEnd = m_FuncList[eState].end();

		for (iter = m_FuncList[eState].begin(); iter != iterEnd; ++iter)
		{
			(*iter)(this, pDest, fDeltaTime);
		}
	}

	bool CheckCollisionList(CCollider1* pCollider1)
	{
		list<CCollider1*>::iterator iter;
		list<CCollider1*>::iterator iterEnd = m_CollisionList.end();

		for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter)
		{
			if (*iter == pCollider1)
				return true;
		}

		return false;
	}

	void EraseCollisionList(CCollider1* pCollider1)
	{
		list<CCollider1*>::iterator iter;
		list<CCollider1*>::iterator iterEnd = m_CollisionList.end();

		for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter)
		{
			if (*iter == pCollider1)
			{
				m_CollisionList.erase(iter);
				break;
			}
		}
	}

	virtual bool	Init() = 0;
	virtual void	Input(float fDeltaTime);
	virtual int		Update(float fDeltaTime);
	virtual int		LateUpdate(float fDeltaTime);
	virtual bool	Collision(CCollider1* pDest);
	virtual void	Render(HDC hDC, float fDeltaTime);
	virtual CCollider1*	Clone() = 0;
};

