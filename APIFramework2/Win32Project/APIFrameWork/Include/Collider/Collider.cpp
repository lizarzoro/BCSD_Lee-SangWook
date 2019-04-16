#include "Collider.h"
#include "../Object/Obj.h"
#include "../Math.h"

CCollider::CCollider() {
}

CCollider::CCollider(const CCollider & coll) {
	*this = coll;
}

CCollider::~CCollider() {
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_CollisionList.end();

	for (iter = m_CollisionList.begin(); iter != iterEnd; iter++) {
		(*iter)->EraseCollisionList(this);		
	}
}

void CCollider::Input(float fDeltaTime) {
}

int CCollider::Update(float fDeltaTime) {
	return 0;
}

int CCollider::LateUpdate(float fDeltaTime) {
	return 0;
}

bool CCollider::Collision(CCollider* pDest) {
	return false;
}

void CCollider::Render(HDC hDC, float fDeltaTime) {
}

bool CCollider::CollisionRectToRect(const RECTANGLE & src, const RECTANGLE & dest) {
	if (src.l > dest.r)
		return false;
	else if (src.r < dest.l)
		return false;
	else if (src.t > dest.b)
		return false;
	else if (src.b < dest.t)
		return false;

	return true;
}

bool CCollider::CollisionRectToSphere(const RECTANGLE & src, const SPHERE & dest) {
	// ���� ������ x��ǥ�� �簢���� ���ο��� �ȿ� �ִ���,
	// ���� ������ y��ǥ�� �簢���� ���� ���� �ȿ� �ִ��� üũ.
	// ���� �ϳ��� �´ٸ� �簢���� �����¿� �ȿ� ��ġ.
	if ((src.l <= dest.tCenter.x && dest.tCenter.x <= src.r) ||
		(src.t <= dest.tCenter.y && dest.tCenter.y <= src.b)) {
		RECTANGLE tRC = src;

		tRC.l -= dest.fRadius;
		tRC.t -= dest.fRadius;
		tRC.r += dest.fRadius;
		tRC.b += dest.fRadius;

		if (dest.tCenter.x < tRC.l) {
			return false;
		}
		else if (dest.tCenter.x > tRC.r) {
			return false;
		}
		else if (dest.tCenter.y < tRC.t) {
			return false;
		}
		else if (dest.tCenter.y > tRC.b) {
			return false;
		}

		return true;
	}
	// �簢���� 4���� ���� �ϳ��� �� �ȿ� ���� ��� �浹�̴�.
	POSITION tPos[4];
	tPos[0] = POSITION(src.l, src.t);
	tPos[1] = POSITION(src.r, src.t);
	tPos[2] = POSITION(src.l, src.b);
	tPos[3] = POSITION(src.r, src.b);

	for (int i = 0; i < 4; i++) {
		float fDist = CMath::Distance(tPos[i], dest.tCenter);

		if (fDist <= dest.fRadius)
			return true;
	}

	return false;
}

bool CCollider::CollisionSphereToSphere(const SPHERE & src, const SPHERE & dest) {
	float fDist = CMath::Distance(src.tCenter, dest.tCenter);

	return fDist<=src.fRadius + dest.fRadius;
}

bool CCollider::CollisionRectToPixel(const RECTANGLE & src, const vector<PIXEL> vecPixel, int iWidth, int iHeight) {
	m_tHitPoint.x = -1;
	m_tHitPoint.y = -1;

	int iStartX, iEndX;
	int iStartY, iEndY;

	iStartX = src.l < 0 ? 0 : src.l;
	iEndX = src.r >= iWidth ? iWidth - 1 : src.r;

	iStartY = src.t < 0 ? 0 : src.t;
	iEndY = src.b >= iHeight ? iHeight - 1 : src.b;

	for (int i = iStartY; i <= iEndY; i++) {
		for (int j = iStartX; j <= iStartX; j++) {
			int idx = i * iWidth + j;
			const PIXEL&  pixel = vecPixel[idx];

			if (pixel.r == 255 && pixel.g == 0 & pixel.b == 255) {
				m_tHitPoint.x = j;
				m_tHitPoint.y = i;
				return true;
			}
		}
	}

	return false;
}
