#pragma once
#include "Collider1.h"
class CColliderRect1 :
	public CCollider1
{
public:
	CColliderRect1();
	CColliderRect1(const CColliderRect1& coll);
	virtual ~CColliderRect1();

private:
	RECTANGLE	m_tInfo;
	RECTANGLE	m_tWorldInfo;

protected:
	friend class CObj;

public:
	RECTANGLE GetInfo() const { return m_tInfo; }
	RECTANGLE GetWorldInfo() const { return m_tWorldInfo; }

	void SetRect(float l, float t, float r, float b);

	//rect충돌할때 필요한 정보 : 왼위 오아래
	virtual bool	Init();
	virtual void	Input(float fDeltaTime);
	virtual int		Update(float fDeltaTime);
	virtual int		LateUpdate(float fDeltaTime); 
	virtual bool	Collision(CCollider1* pDest);
	virtual void	Render(HDC hDC, float fDeltaTime);
	virtual CColliderRect1*	Clone();
};

