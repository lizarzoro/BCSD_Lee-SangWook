#include "Scene.h"
#include "Layer.h"

CScene::CScene()
{
	CLayer* pLayer = CreateLayer("UI", INT_MAX);
	pLayer = CreateLayer("HUD", INT_MAX - 1);
	pLayer = CreateLayer("Default", 1);
	pLayer = CreateLayer("Stage");
	//m_eSceneType = SC_CURRENT;
}


CScene::~CScene()
{
	Safe_Delete_VecList(m_LayerList);
}

CLayer * CScene::CreateLayer(const string & strTag, int iZOrder)
{
	CLayer* pLayer = new CLayer;

	pLayer->SetTag(strTag);
	pLayer->SetZOrder(iZOrder);
	pLayer->SetScene(this);

	m_LayerList.push_back(pLayer);

	if (m_LayerList.size() >= 2)
		m_LayerList.sort(CScene::LayerSort);

	return pLayer;
}

bool CScene::Init()
{
	return true;
}

void CScene::Input(float fDeltaTime)
{
}

int CScene::Update(float fDeltaTime)
{
	return 0;
}

int CScene::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CScene::Collision(float fDeltaTime)
{
}

void CScene::Render(float fDeltaTime)
{
}

bool CScene::LayerSort(CLayer * pL1, CLayer * pL2)
{
	return pL1->GetZOrder() < pL2->GetZOrder();
}
