#include "stdafx.h"
#include "SceneMgr.h"

#include "ScrollMgr.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage_Boss.h"

CSceneMgr*	CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_eCurScene(SC_END), m_ePreScene(SC_END)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

// FSM(finite state machine) : ���� ���� ���, �ڽ��� ���� �� �ִ� ������ ������ ����

void CSceneMgr::Scene_Change(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case SC_LOGO:
			m_pScene = new CLogo;
			break;
		case SC_MENU:
			m_pScene = new CMyMenu;
			break;
		case SC_EDIT:
			break;
		case SC_STAGE_1:
			m_pScene = new CStage1;
			break;
		case SC_STAGE_2:
			m_pScene = new CStage2;
			break;
		case SC_STAGE_BOSS:
			m_pScene = new CStage_Boss;
			break;
		}

	 m_pScene->Initialize();
	 m_ePreScene = m_eCurScene;
	}

}

void CSceneMgr::Update(void)
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update(void)
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);


	// TEST: ���콺 ��ǥ ǥ��
	POINT	pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	pt.x = (float)pt.x - iScrollX;
	pt.y = (float)pt.y - iScrollY;

	TCHAR lpOut[1024];
	wsprintf(lpOut, TEXT("lX: %d \nY: %d"), pt.x, pt.y);
	TextOut(hDC, 35, 15, lpOut, lstrlen(lpOut));

}

void CSceneMgr::Release(void)
{
	Safe_Delete(m_pScene);
}
