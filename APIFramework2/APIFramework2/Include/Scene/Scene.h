#pragma once
#include "../Game.h"

class CScene
{
protected:
	friend class CSceneManager;

protected: 
	CScene();
	virtual ~CScene() = 0; // �߻�Ŭ���� - ��ü���� �Ұ�

protected:
	list<class CLayer*> m_LayerList;

public:
	class CLayer* CreateLayer(const string& strTag, int iZOrder = 0);

public:
	virtual bool Init();

public:
	static bool LayerSort(class CLayer* pL1, class CLayer* pL2);
};

