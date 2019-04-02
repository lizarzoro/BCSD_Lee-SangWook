#pragma once
#include "Scene.h"
class CInGameScene :
	public CScene
{
private:
	friend class CSceneManager; // 접근 가능

private:
	CInGameScene();
	~CInGameScene();

public:
	virtual bool Init();
};

