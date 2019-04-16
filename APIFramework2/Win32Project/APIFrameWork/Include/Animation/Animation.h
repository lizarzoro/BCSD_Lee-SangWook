#pragma once
#include "../Ref.h"
class CAnimation :
	public CRef
{
private:
	friend class CObj;

private:
	CAnimation();
	CAnimation(const CAnimation& ani);
	~CAnimation();

private:
	unordered_map<string, PANIMATIONCLIP> m_mapClip;
	PANIMATIONCLIP m_pCurClip;
	string m_strCurClip;
	string m_strDefaultClip;
	class CObj* m_pObj;
	bool m_bMotionEnd;

public:
	bool GetMotionEnd() const {
		return m_bMotionEnd;
	}

	PANIMATIONCLIP GetCurrentClip() const {
		return m_pCurClip;
	}

	void SetObj(class CObj* pObj) {
		m_pObj = pObj;
	}
	bool AddClip(const string& strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption,
		float fAnimationLimitTime, int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY,
		int iLengthX, int iLengthY, float fOptionLimitTime, const string& strTexKey, const wchar_t* pFileName,
		const string& strPathKey = TEXTURE_PATH);

	void SetClipColorKey(const string& strClip,
		unsigned char r, unsigned char g, unsigned char b);
	void SetCurrentClip(const string& strCurClip);
	void SetDefaultClip(const string& strDefaultClip);
	void ChangeClip(const string& strClip);
	void ReturnClip();

private:
	PANIMATIONCLIP FindClip(const string& strName);

public:
	bool Init();
	void Update(float fTime);
	CAnimation* Clone();
};

