#pragma once
#include "../Ref.h"
class CCollider1 :
	public CRef
{
protected:
	friend class CObj;
	COLLLIDER_TYPE		m_eCollType;

protected:
	CCollider1();
	CCollider1(const CCollider1 & coll);
	virtual ~CCollider1() = 0;

public:
	virtual bool	Init() = 0;
	virtual void	Input(float fDeltaTime);
	virtual int		Update(float fDeltaTime);
	virtual int		LateUpdate(float fDeltaTime);
	virtual void	Collision(float fDeltaTime);
	virtual void	Render(HDC hDC, float fDeltaTime);
	virtual CCollider1*	Clone() = 0;
	
};

