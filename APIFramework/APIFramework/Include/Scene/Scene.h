#pragma once

#include "../Game.h"

class CScene
{
private:
	static unordered_map<string, class CObj*> m_mapPrototype[SC_END];
	
protected:
	CScene();
	virtual ~CScene() = 0;

	friend class CSceneManager;

	list<class CLayer*> m_LayerList;
	SCENE_CREATE	m_eSceneType; 

public:
	virtual bool	Init();
	virtual void	Input(float fDeltaTime);
	virtual int		Update(float fDeltaTime);
	virtual int		LateUpdate(float fDeltaTime);
	virtual void	Collision(float fDeltaTime);
	virtual void	Render(HDC hDC, float fDeltaTime);

	void SetSceneType(SCENE_CREATE eType) { m_eSceneType = eType; }
	SCENE_CREATE GetSceneType() { return m_eSceneType; }

	class CLayer* CreateLayer(const string& strTag, int iZOrder = 0);
	class CLayer* FindLayer(const string& strTag);

	static bool LayerSort(class CLayer* pL1, class CLayer* pL2);
	static void ErasePrototype(const string& strTag, SCENE_CREATE sc);
	static void ErasePrototype(SCENE_CREATE sc);

	template <typename T>
	static T* CreatePrototype(const string& strTag, SCENE_CREATE sc)
	{
		T* pObj = new T;

		pObj->setTag(strTag);

		if (!pObj->Init())
		{
			SAFE_RELEASE(pObj);
			return NULL;
		}

		pObj->AddRef();
		m_mapPrototype[sc].insert(make_pair(strTag, pObj));

		return pObj;
	}
	static CObj* FindPrototype(const string& strKey, SCENE_CREATE sc);
	static void ChangePrototype();
};

