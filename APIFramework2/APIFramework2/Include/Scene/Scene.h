#pragma once
#include "../Game.h"

class CScene
{
protected:
	friend class CSceneManager;

protected: 
	CScene();
	virtual ~CScene() = 0; // �߻�Ŭ���� - ��ü���� �Ұ�

public:
	virtual bool Init();
};

