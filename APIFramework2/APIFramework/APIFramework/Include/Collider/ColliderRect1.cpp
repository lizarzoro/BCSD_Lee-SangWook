#include "ColliderRect1.h"



CColliderRect1::CColliderRect1()
{
	m_eCollType = CT_RECT;
}

CColliderRect1::CColliderRect1(const CColliderRect1 & coll) :
	CCollider1(coll)
{
	//m_tInfo = coll.m_tInfo;
}


CColliderRect1::~CColliderRect1()
{
}

void CColliderRect1::SetRect(float l, float t, float r, float b)
{
	m_tInfo.l = l;
	m_tInfo.t = t;
	m_tInfo.r = r;
	m_tInfo.b = b;
}

bool CColliderRect1::Init()
{
	return true;
}

void CColliderRect1::Input(float fDeltaTime)
{
	CCollider1::Input(fDeltaTime);
}

int CColliderRect1::Update(float fDeltaTime)
{
	CCollider1::Update(fDeltaTime);
	return 0;
}

int CColliderRect1::LateUpdate(float fDeltaTime)
{
	CCollider1::LateUpdate(fDeltaTime);

	POSITION tPos = m_pObj->GetPos();
	m_tWorldInfo.l = tPos.x + m_tInfo.l;
	m_tWorldInfo.t = tPos.y + m_tInfo.t;
	m_tWorldInfo.r = tPos.x + m_tInfo.r;
	m_tWorldInfo.b = tPos.y + m_tInfo.b;

	return 0;
}

bool CColliderRect1::Collision(CCollider1* pDest)
{
	switch (pDest->GetColliderType())
	{
	case CT_RECT:
		return CollisionRectToRect(m_tWorldInfo, ((CColliderRect1*)pDest)->GetWorldInfo());
	/*case CT_SPHERE:
		return CollisionRectToSphere(m_tWorldInfo, ((CColliderSphere*)pDest)->GetWorldInfo());
	case CT_PIXEL:
		return CollisionRectToPixel(m_tWorldInfo, ((CColliderPixel*)pDest)->GetPixel(),
			((CColliderPixel*)pDest)->GetWidth(), ((CColliderPixel*)pDest)->GetHeight());
	case CT_POINT:
		return CollisionRectToPoint(m_tWorldInfo, ((CColliderPoint*)pDest)->GetPoint());*/
	}
	return false;
}

void CColliderRect1::Render(HDC hDC, float fDeltaTime)
{
#ifdef _DEBUG
	CCollider1::Render(hDC, fDeltaTime);

	POSITION tCamPos = GET_SINGLE(CCamera)->GetPos();

	RECTANGLE tRC = m_tWorldInfo;
	tRC.l -= tCamPos.x;
	tRC.r -= tCamPos.x;
	tRC.t -= tCamPos.y;
	tRC.b -= tCamPos.y;

	MoveToEx(hDC, tRC.l, tRC.t, NULL);
	LineTo(hDC, tRC.r, tRC.t);
	LineTo(hDC, tRC.r, tRC.b);
	LineTo(hDC, tRC.l, tRC.b);
	LineTo(hDC, tRC.l, tRC.t);
#endif // _DEBUG
}

CColliderRect1 * CColliderRect1::Clone()
{
	return new CColliderRect1(*this);
}
