#pragma once
#include "../Game.h"

class CScene
{
protected:
	friend class CSceneManager;

protected: 
	CScene();
	virtual ~CScene() = 0; // 추상클래스 - 객체생성 불가

public:
	virtual bool Init();
};

