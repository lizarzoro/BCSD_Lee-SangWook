#include "Layer.h"
#include "../Object/Obj.h"

CLayer::CLayer()	:
	m_iZOrder(0),
	m_strTag(""),
	m_pScene(NULL)
	//m_bLife(true),
	//m_bEnable(true)
{
}

CLayer::~CLayer()
{
	Safe_Release_VecList(m_ObjList);
}
