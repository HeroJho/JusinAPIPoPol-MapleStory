#include "stdafx.h"
#include "EventMgr.h"

#include "SceneMgr.h"

CEventMgr* CEventMgr::m_pInstance = nullptr;

CEventMgr::CEventMgr()
	:m_eID(SC_END)
{
}

CEventMgr::~CEventMgr()
{
}

void CEventMgr::ExeEvent()
{
	if (m_eID == SC_END)
		return;

	CSceneMgr::Get_Instance()->Scene_Change(m_eID);
	m_eID == SC_END;
}

void CEventMgr::AddSceneChangeEvent(SCENEID _eId)
{
	m_eID = _eId;
}

int CEventMgr::GetRandomNum_Int(int iLeft, int iRight)
{
	// 시드값을 얻기 위한 random_device 생성.
	std::random_device rd;

	// random_device 를 통해 난수 생성 엔진을 초기화 한다.
	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> dis(iLeft, iRight);

	return dis(gen);
}
