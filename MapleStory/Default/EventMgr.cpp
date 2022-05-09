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
