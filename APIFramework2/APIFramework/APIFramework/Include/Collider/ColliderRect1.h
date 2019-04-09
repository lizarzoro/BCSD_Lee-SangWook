#pragma once
#include "Collider1.h"
class CColliderRect1 :
	public CCollider1
{
public:
	CColliderRect1();
	CColliderRect1(const CColliderRect1& coll);
	virtual ~CColliderRect1();

	virtual bool	Init();
	virtual void	Input(float fDeltaTime);
	virtual int		Update(float fDeltaTime);
	virtual int		LateUpdate(float fDeltaTime);
	virtual bool	Collision(CCollider1* pDest);
	virtual void	Render(HDC hDC, float fDeltaTime);
	virtual CColliderRect1*	Clone();
};

