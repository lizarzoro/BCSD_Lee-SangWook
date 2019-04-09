#pragma once

#include "Game.h"

class CRef
{
public:
	CRef();
	virtual ~CRef() = 0;

	void AddRef() { ++m_iRef; }
	int Release() {
		--m_iRef;

		if (m_iRef == 0) { delete this; return 0; }

		return m_iRef;
	}

	bool GetEnable() const { return m_bEnable; }
	bool GetLife() const { return m_bLife; }
	string GetTag() const { return m_strTag; }
	void SetTag(const string& strTag) { m_strTag = strTag; }
	void SetEnable(bool bEnable) { m_bEnable = bEnable; }
	void Die() { m_bLife = false; }

protected:
	string	m_strTag;
	int		m_iRef;
	bool	m_bEnable;
	bool	m_bLife;
};

