#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "Monster.h"
#include "Mouse.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "EventMgr.h"
#include "SpawnMgr.h"
#include "UIMgr.h"
#include "InvenMgr.h"
#include "SkillMgr.h"
#include "MouseMgr.h"
#include "SlotMgr.h"
#include "QuestMgr.h"
#include "CutMgr.h"
#include "SoundMgr.h"
#include "StatMgr.h"


CMainGame::CMainGame()
	: m_dwTime((DWORD)GetTickCount64())
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 64);
	m_iFPS = 0;
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");

	CSoundMgr::Get_Instance()->Initialize();
	CQuestMgr::Get_Instance()->Initialize();
	CMouseMgr::Get_Instance()->Initialize();
	CSlotMgr::Get_Instance()->Initialize();
	CSceneMgr::Get_Instance()->Scene_Change(SC_LOGO);
}

void CMainGame::Update(void)
{
	CSceneMgr::Get_Instance()->Update();

	if (CSceneMgr::Get_Instance()->Get_CurSceneId() != SC_LOGO && CSceneMgr::Get_Instance()->Get_CurSceneId() != SC_STAGE_COO)
	{
		CMouseMgr::Get_Instance()->Update();
		CSlotMgr::Get_Instance()->Update();
		CQuestMgr::Get_Instance()->Update();
		CCutMgr::Get_Instance()->Update();
	}
}

void CMainGame::Late_Update(void)
{
	CSceneMgr::Get_Instance()->Late_Update();

	if (CSceneMgr::Get_Instance()->Get_CurSceneId() != SC_LOGO && CSceneMgr::Get_Instance()->Get_CurSceneId() != SC_STAGE_COO)
		CMouseMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render(void)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);


	CSceneMgr::Get_Instance()->Render(hMemDC);
	if (CSceneMgr::Get_Instance()->Get_CurSceneId() != SC_LOGO && CSceneMgr::Get_Instance()->Get_CurSceneId() != SC_STAGE_COO)
		CMouseMgr::Get_Instance()->Render(hMemDC);
	
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount64())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = (DWORD)GetTickCount64();
	}


	// 이벤트 처리(씬 전환)
	CEventMgr::Get_Instance()->ExeEvent();
}

void CMainGame::Release(void)
{
	CStatMgr::Get_Instance()->Destroy_Instance();
	CSoundMgr::Get_Instance()->Destroy_Instance();
	CCutMgr::Get_Instance()->Destroy_Instance();
	CQuestMgr::Get_Instance()->Destroy_Instance();
	CSlotMgr::Get_Instance()->Destroy_Instance();
	CMouseMgr::Get_Instance()->Destroy_Instance();
	CSkillMgr::Get_Instance()->Destroy_Instance();
	CInvenMgr::Get_Instance()->Destroy_Instance();
	CUIMgr::Get_Instance()->Destroy_Instance();
	CSpawnMgr::Get_Instance()->Destroy_Instance();
	CEventMgr::Get_Instance()->Destroy_Instance();
	CSceneMgr::Get_Instance()->Destroy_Instance();
	CBmpMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CLineMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
}