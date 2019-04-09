#pragma once

#include "../Game.h"

class CSceneManager
{
private:
	class CScene* m_pScene;
	class CScene* m_pNextScene;

	SCENE_CHANGE	ChangeScene();

public:
	class CScene* GetScene() const { return m_pScene; }

	bool	Init();
	void	Input(float fDeltaTime);
	SCENE_CHANGE	Update(float fDeltaTime);
	SCENE_CHANGE	LateUpdate(float fDeltaTime);
	void	Collision(float fDeltaTime);
	void	Render(HDC hDC, float fDeltaTime);

	template <typename T>
	T* CreateScene(SCENE_CREATE sc = SC_CURRENT)
	{
		T* pScene = new T;

		pScene->SetSceneType(sc);

		if (!pScene->Init())
		{
			SAFE_DELETE(pScene);
			return NULL;
		}

		switch (sc)
		{
		case SC_CURRENT:
			SAFE_DELETE(m_pScene);
			m_pScene = pScene;
			break;
		case SC_NEXT:
			SAFE_DELETE(m_pNextScene);
			m_pNextScene = pScene;
			break;
		}

		return pScene;
	}

	DECLARE_SINGLE(CSceneManager)
};

